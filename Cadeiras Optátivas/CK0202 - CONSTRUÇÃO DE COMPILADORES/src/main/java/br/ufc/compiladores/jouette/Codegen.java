package br.ufc.compiladores.jouette;

import java.util.List;
import java.util.ListIterator;
import java.util.LinkedList;

import br.ufc.compiladores.mips.MipsFrame;
import br.ufc.compiladores.assem.Instr;
import br.ufc.compiladores.assem.OPER;
import br.ufc.compiladores.temp.Temp;
import br.ufc.compiladores.temp.LabelList;
import br.ufc.compiladores.tree.*;
import br.ufc.compiladores.canon.MoveCall;
import br.ufc.compiladores.canon.ExpCall;

/**
 * Gera instruções MIPS a partir do IR canônico.
*/
public class Codegen {
    private MipsFrame frame;
    private ListIterator<Instr> insns;

    public Codegen(MipsFrame frame, ListIterator<Instr> insns) {
        this.frame = frame;
        this.insns = insns;
    }

    private void emit(Instr inst) {
        insns.add(inst);
    }

    private Instr OPER(String fmt, Temp[] dst, Temp[] src) {
        return OPER(fmt, dst, src, null);
    }

    private Instr OPER(String fmt, Temp[] dst, Temp[] src, LabelList jumps) {
        dst = dst != null ? dst : new Temp[0];
        src = src != null ? src : new Temp[0];
        return new OPER("\t"+fmt, dst, src, jumps);
      }

    private Instr MOVE(Temp d, Temp s) {
        return new br.ufc.compiladores.assem.MOVE("\tmove `d0,`s0", d, s);
    }

    public void munchStmList(StmList list) {
        for (; list != null; list = list.tail)
            munchStm(list.head);
    }

    public void munchStm(Stm s) {
        s.accept(this);
    }

    public Temp munchExp(Exp1 e) {
        return e.accept(this);
    }

    // === EXPRESSÕES ===

    public Temp visit(CONST c) {
        Temp t = new Temp();
        emit(OPER("li `d0," + c.value, new Temp[]{t}, new Temp[0]));
        return t;
    }

    public Temp visit(NAME n) {
        Temp t = new Temp();
        emit(OPER("la `d0," + n.label, new Temp[]{t}, new Temp[0]));
        return t;
    }

    public Temp visit(TEMP tExp) {
        return tExp.temp;
    }

    public Temp visit(BINOP b) {
        Temp dst = new Temp();
        // addi imediato
        if (b.binop == BINOP.PLUS && b.right instanceof CONST) {
            CONST c = (CONST) b.right;
            Temp src = munchExp(b.left);
            emit(OPER("addi `d0,`s0," + c.value, new Temp[]{dst}, new Temp[]{src}));
            return dst;
        }
        // caso geral: add, sub, mul, and
        Temp l = munchExp(b.left), r = munchExp(b.right);
        String op = switch (b.binop) {
            case BINOP.PLUS  -> "add";
            case BINOP.MINUS -> "sub";
            case BINOP.MUL   -> "mul";
            case BINOP.AND   -> "and";
            default    -> throw new Error("BINOP não suportado: " + b.binop);
        };
        emit(OPER(op + " `d0,`s0,`s1", new Temp[]{dst}, new Temp[]{l, r}));
        return dst;
    }

    public Temp visit(MEM m) {
        Temp dst = new Temp();
        // MEM(BINOP(+,...))
        if (m.exp instanceof BINOP) {
            BINOP bin = (BINOP) m.exp;
            if (bin.binop == BINOP.PLUS && bin.right instanceof CONST) {
                CONST c = (CONST) bin.right;
                Temp base = munchExp(bin.left);
                emit(OPER("lw `d0," + c.value + "(`s0)", new Temp[]{dst}, new Temp[]{base}));
                return dst;
            }
            if (bin.binop == BINOP.PLUS && bin.left instanceof CONST) {
                CONST c = (CONST) bin.left;
                Temp base = munchExp(bin.right);
                emit(OPER("lw `d0," + c.value + "(`s0)", new Temp[]{dst}, new Temp[]{base}));
                return dst;
            }
        }
        // MEM(CONST)
        if (m.exp instanceof CONST) {
            CONST c = (CONST) m.exp;
            emit(OPER("lw `d0," + c.value + "(`s0)", new Temp[]{dst}, new Temp[]{MipsFrame.ZERO}));
            return dst;
        }
        // MEM(exp)
        Temp base = munchExp(m.exp);
        emit(OPER("lw `d0,0(`s0)", new Temp[]{dst}, new Temp[]{base}));
        return dst;
    }

    public Temp visit(ESEQ e) {
        // primeiro emite o stm
        munchStm(e.stm);
        // depois traduz a parte de expressão
        return munchExp(e.exp);
    }
    
    // para SEQ (sequência de stm’s)
    public void visit(SEQ s) {
        munchStm(s.left);
        munchStm(s.right);
    }

    public void visit(MoveCall mc) {
        // 1) gera a chamada (src é o CALL)
        Temp r = munchExp(mc.src);
    
        // 2) move o resultado para dst.temp (dst é um nó TEMP, cujo campo interno chama-se temp)
        emit(MOVE(mc.dst.temp, r));
    }

    public Temp visit(ExpCall ec) {
        // basta delegar ao visit(CALL) existente, se ec.call for um CALL
        return munchExp(ec.call);
    }

    // === INSTRUÇÕES ===

    public void visit(MOVE m) {
        // store
        if (m.dst instanceof MEM) {
            MEM mem = (MEM) m.dst;
            int off = 0;
            Temp base;
            if (mem.exp instanceof BINOP bin && bin.binop == BINOP.PLUS && bin.left instanceof CONST) {
                off = ((CONST)bin.left).value;
                base = munchExp(bin.right);
            } else if (mem.exp instanceof BINOP bin2 && bin2.binop == BINOP.PLUS && bin2.right instanceof CONST) {
                off = ((CONST)bin2.right).value;
                base = munchExp(bin2.left);
            } else if (mem.exp instanceof CONST c) {
                off = c.value;
                base = MipsFrame.ZERO;
            } else {
                base = munchExp(mem.exp);
            }
            Temp src = munchExp(m.src);
            emit(OPER("sw `s0," + off + "(`s1)", new Temp[0], new Temp[]{src, base}));
        }
        // register-register
        else if (m.dst instanceof TEMP tDst) {
            Temp d = tDst.temp;
            Temp s = munchExp(m.src);
            emit(MOVE(d, s));
        } else {
            throw new Error("MOVE.dst inválido: " + m.dst);
        }
    }

    public void visit(EXP s) {
        munchExp(s.exp);
    }

    public void visit(JUMP j) {
        // salto indireto ou direto
        if (j.exp instanceof NAME n) {
            emit(OPER("j " + n.label, new Temp[0], new Temp[0], j.targets));
        } else {
            Temp t = munchExp(j.exp);
            emit(OPER("jr `s0", new Temp[0], new Temp[]{t}, j.targets));
        }
    }

    public void visit(CJUMP j) {
        Temp l = munchExp(j.left), r = munchExp(j.right);
        String instr = (j.relop == CJUMP.NE) ? "bne" : "blt";
    
        // Monta diretamente um LabelList de dois elementos
        LabelList targets =
            new LabelList(j.iftrue,
                new LabelList(j.iffalse, null));
    
        emit(OPER(
            instr + " `s0,`s1 " + j.iftrue,
            new Temp[0],
            new Temp[]{l, r},
            targets            
        ));
    }

    public void visit(LABEL l) {
        emit(new br.ufc.compiladores.assem.LABEL(l.label.toString() + ":", l.label));
    }

    public Temp visit(CALL c) {
        // primeiro argumento: código de syscall (0 = normal)
        Temp code = munchExp(c.args.head);
        List<Temp> uses = new LinkedList<>();
        if (code != MipsFrame.ZERO) {
            emit(MOVE(frame.RV(), code));
            uses.add(frame.RV());
        }
        // A0–A3
        ExpList el = c.args.tail;
        Temp[] regs = { MipsFrame.A0, MipsFrame.A1, MipsFrame.A2, MipsFrame.A3 };
        int i = 0, off = 0;
        while (i < 4 && el != null) {
            Temp a = munchExp(el.head);
            emit(MOVE(regs[i], a));
            uses.add(regs[i]);
            off += frame.wordSize();
            i++;
            el = el.tail;
        }
        // resto na pilha
        while (el != null) {
            Temp a = munchExp(el.head);
            off += frame.wordSize();
            emit(OPER("sw `s0," + off + "(`s1)", new Temp[0], new Temp[]{a, frame.SP}));
            el = el.tail;
        }
        if (off > MipsFrame.maxArgOffset) MipsFrame.maxArgOffset = off;
        // chama
        if (c.func instanceof NAME n) {
            emit(OPER("jal " + n.label, new Temp[0], uses.toArray(new Temp[0])));
        } else {
            Temp f = munchExp(c.func);
            uses.add(0, f);
            emit(OPER("jal `s0", new Temp[0], uses.toArray(new Temp[0])));
        }
        return frame.RV();
    }
}
