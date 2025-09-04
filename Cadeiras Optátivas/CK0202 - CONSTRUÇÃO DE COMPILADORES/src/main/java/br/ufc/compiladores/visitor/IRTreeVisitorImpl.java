package br.ufc.compiladores.visitor;

import java.util.*;
import br.ufc.compiladores.syntaxtree.*;    // Print, Assign, If, While…
import br.ufc.compiladores.frame.Frame;
import br.ufc.compiladores.frag.Frag;
import br.ufc.compiladores.frag.ProcFrag;
import br.ufc.compiladores.frame.Access;
import br.ufc.compiladores.semant.SymbolTable;
import br.ufc.compiladores.temp.Label;
import br.ufc.compiladores.temp.LabelList;
// só o que você usa do IR:
import br.ufc.compiladores.tree.BINOP;
import br.ufc.compiladores.tree.MOVE;
import br.ufc.compiladores.tree.CJUMP;
import br.ufc.compiladores.tree.LABEL;
import br.ufc.compiladores.tree.JUMP;
import br.ufc.compiladores.tree.EXP;
import br.ufc.compiladores.tree.NAME;
import br.ufc.compiladores.tree.TEMP;
import br.ufc.compiladores.tree.MEM;
import br.ufc.compiladores.tree.CONST;
import br.ufc.compiladores.tree.ExpList;
import br.ufc.compiladores.tree.CALL;
import br.ufc.compiladores.tree.Exp1;
import br.ufc.compiladores.tree.Stm;
import br.ufc.compiladores.tree.StmList;
import br.ufc.compiladores.tree.ESEQ;
import br.ufc.compiladores.tree.SEQ;
import br.ufc.compiladores.semant.ClassInfo;
import br.ufc.compiladores.semant.MethodInfo;
import br.ufc.compiladores.semant.Symbol;
import br.ufc.compiladores.temp.Temp;
import br.ufc.compiladores.translate.TranslatedExp;

public class IRTreeVisitorImpl implements IRTreeVisitor {

    private SymbolTable tableProgram;
    private ClassInfo currentClass;
    private MethodInfo currentMethod;
    private Frame currentFrame;

    private Frag fragHead;
    private Frag frags;

    private HashMap<Symbol, Access> varAccessMap;

    public IRTreeVisitorImpl(SymbolTable tableProgram, Frame initialFrame) {
        this.tableProgram = tableProgram;
        this.currentFrame = initialFrame;

        this.fragHead = new ProcFrag(null, null);
        this.frags = fragHead;

        this.varAccessMap = new HashMap<>();
    }

    // public List<Proc> getProcs() {
    //     return procs;
    // }

    @Override
    public TranslatedExp visit(Program n) {
        n.m.accept(this);
        for (int i = 0; i < n.cl.size(); i++) {
            n.cl.elementAt(i).accept(this);
        }
        return null;
    }

    @Override
    public TranslatedExp visit(MainClass n) {
        currentClass = tableProgram.getClass(n.i1.s);

        // Cria frame do método main (sem parâmetros)
        currentFrame = currentFrame.newFrame(
            Symbol.symbol("main"),
            Collections.singletonList(false) 
        );
        
        // Limpa mapa de variáveis (por segurança)
        varAccessMap.clear();

        // Gera corpo do main
        TranslatedExp bodyExp = n.s.accept(this);
        if (bodyExp == null || bodyExp.unNx() == null) {
            throw new RuntimeException("expressão principal do main retornou null.");
        }
        Stm body = bodyExp.unNx();

        // Envolve em procEntryExit1 (pode adicionar código de prólogo/epílogo)
        List<Stm> stms = new ArrayList<>();
        stms.add(body);
        currentFrame.procEntryExit1(stms);

        // Sequencia todos os Stm retornados em um único SEQ
        Stm root = stms.get(0);
        for (int i = 1; i < stms.size(); i++) {
            root = new SEQ(root, stms.get(i));
        }

        // Cria fragmento de procedimento com toda a sequência
        ProcFrag proc = new ProcFrag(root, currentFrame);
        frags.addNext(proc);
        frags = frags.getNext();

        return null;
    }

    @Override
    public TranslatedExp visit(ClassDeclSimple n) {
        // Define a classe atual
        Symbol className = n.i.s;
        currentClass = tableProgram.getClass(className);

        // Limpa o mapa de variáveis
        varAccessMap.clear();

        // Visita todos os métodos da classe
        for (int i = 0; i < n.ml.size(); i++) {
            n.ml.elementAt(i).accept(this);
        }

        // Limpa o estado após processar a classe
        currentClass = null;
        return null;
    }

    @Override
    public TranslatedExp visit(ClassDeclExtends n) {
        // Define a classe atual
        Symbol className = n.i.s;
        currentClass = tableProgram.getClass(className);

        // Limpa variáveis anteriores
        varAccessMap.clear();

        // Visita todos os métodos da classe
        for (int i = 0; i < n.ml.size(); i++) {
            n.ml.elementAt(i).accept(this);
        }

        // Limpa estado
        currentClass = null;
        return null;
    }

    @Override
    public TranslatedExp visit(MethodDecl n) {
        // Atualiza o método atual
        Symbol methodName = n.i.s;
        currentMethod = currentClass.getMethod(methodName);

        // Cria lista de escapes para parâmetros (assumindo que nenhum escapa)
        int paramCount = n.fl.size() + 1; // inclui "this"
        List<Boolean> escapes = Collections.nCopies(paramCount, false);

        // Cria novo frame
        Symbol label = Symbol.symbol(currentClass.name.toString() + "$" + methodName.getName());
        currentFrame = currentFrame.newFrame(label, escapes);

        // Limpa variáveis anteriores
        varAccessMap.clear();

        // Mapeia "this" (posição 0 em formals)
        varAccessMap.put(Symbol.symbol("this"), currentFrame.formals().get(0));

        // Mapeia os parâmetros formais
        List<Access> formals = currentFrame.formals();
        for (int i = 0; i < n.fl.size(); i++) {
            Symbol param = n.fl.elementAt(i).i.s;
            varAccessMap.put(param, formals.get(i + 1)); // +1 porque 0 é "this"
        }

        // Aloca variáveis locais
        for (int i = 0; i < n.vl.size(); i++) {
            Symbol local = n.vl.elementAt(i).i.s;
            Access access = currentFrame.allocLocal(false);
            varAccessMap.put(local, access);
        }

        // Gera os comandos
        Stm body = new EXP(new CONST(0)); // inicial neutro
        for (int i = 0; i < n.sl.size(); i++) {
            TranslatedExp stmt = n.sl.elementAt(i).accept(this);
            if (stmt != null && stmt.unNx() != null) {
                body = new SEQ(body, stmt.unNx());
            } else {
                System.out.println("⚠ WARNING: statement " + i + " retornou null.");
            }
        }

        // Gera expressão de retorno
        List<Stm> stms = new ArrayList<>();
        stms.add(body);
        currentFrame.procEntryExit1(stms);
    
        // Sequencia todos os Stm retornados
        Stm root = stms.get(0);
        for (int i = 1; i < stms.size(); i++) {
            root = new SEQ(root, stms.get(i));
        }
    
        // Cria fragmento
        ProcFrag proc = new ProcFrag(root, currentFrame);
        frags.addNext(proc);
        frags = frags.getNext();

        // Limpa estado
        currentMethod = null;
        return null;
    }

    @Override
    public TranslatedExp visit(Assign n) {
        Symbol varName = n.i.s;
        Access varAccess = varAccessMap.get(varName);

        // Tradução da expressão à direita
        TranslatedExp exp = n.e.accept(this);

        Exp1 dst;

        if (varAccess != null) {
            // Variável local ou parâmetro
            dst = varAccess.exp(new TEMP(currentFrame.FP()));
        } else if (currentClass != null && currentClass.fields.containsKey(varName)) {
            // Campo da classe (this.var)
            dst = new MEM(new BINOP(BINOP.PLUS, new TEMP(currentFrame.FP()), new CONST(0)));
        } else {
            throw new RuntimeException("Variável não encontrada no escopo: " + varName.getName());
        }

        return new TranslatedExp(new MOVE(dst, exp.unEx()));
    }

    @Override
    public TranslatedExp visit(Print n) {
        TranslatedExp exp = n.e.accept(this);
        if (exp == null || exp.unEx() == null) {
            System.out.println("⚠ ERRO: expressão dentro do Print retornou null.");
            return new TranslatedExp(new EXP(new CONST(0))); // evita propagação de null
        }

        List<Exp1> args = new LinkedList<>();
        args.add(exp.unEx());

        Exp1 call = currentFrame.externalCall("print", toExpList(args));
        return new TranslatedExp(new EXP(call));
    }

    @Override
    public TranslatedExp visit(If n) {
        // Traduz a condição como condicional
        TranslatedExp condExp = n.e.accept(this);
        Label trueLabel = new Label();
        Label falseLabel = new Label();
        Label endLabel = new Label();

        // Gera CJUMP (condicional)
        Stm cond = condExp.unCx(trueLabel, falseLabel);

        // Traduz os blocos then e else
        Stm thenStm = n.s1.accept(this).unNx();
        Stm elseStm = n.s2.accept(this).unNx();

        // Monta o código em sequência
        Stm ifStm = new SEQ(
            cond,
            new SEQ(
                new SEQ(
                    new LABEL(trueLabel),
                    new SEQ(thenStm, new JUMP(endLabel))
                ),
                new SEQ(
                    new LABEL(falseLabel),
                    new SEQ(elseStm, new JUMP(endLabel))
                )
            )
        );

        // Fecha com o label final
        ifStm = new SEQ(ifStm, new LABEL(endLabel));

        return new TranslatedExp(ifStm);
    }

    @Override
    public TranslatedExp visit(While n) {
        // Labels
        Label startLabel = new Label();
        Label bodyLabel = new Label();
        Label endLabel = new Label();

        // Condição
        TranslatedExp condExp = n.e.accept(this);
        Stm condStm = new SEQ(
            new LABEL(startLabel),
            condExp.unCx(bodyLabel, endLabel)
        );

        // Corpo
        Stm bodyStm = new SEQ(
            new LABEL(bodyLabel),
            new SEQ(n.s.accept(this).unNx(), new JUMP(startLabel))
        );

        // Montagem final
        Stm whileStm = new SEQ(
            condStm,
            new SEQ(bodyStm, new LABEL(endLabel))
        );

        return new TranslatedExp(whileStm);
    }

    @Override
    public TranslatedExp visit(Plus n) {
        Exp1 left = n.e1.accept(this).unEx();
        Exp1 right = n.e2.accept(this).unEx();
        return new TranslatedExp(new BINOP(BINOP.PLUS, left, right));
    }

    @Override
    public TranslatedExp visit(Minus n) {
        Exp1 left = n.e1.accept(this).unEx();
        Exp1 right = n.e2.accept(this).unEx();
        return new TranslatedExp(new BINOP(BINOP.MINUS, left, right));
    }

    @Override
    public TranslatedExp visit(Times n) {
        Exp1 left = n.e1.accept(this).unEx();
        Exp1 right = n.e2.accept(this).unEx();
        return new TranslatedExp(new BINOP(BINOP.MUL, left, right));
    }

    @Override
    public TranslatedExp visit(LessThan n) {
        Exp1 left = n.e1.accept(this).unEx();
        Exp1 right = n.e2.accept(this).unEx();

        // CJUMP com resultado convertido para valor (1 ou 0)
        Label trueLabel = new Label();
        Label falseLabel = new Label();
        Temp r = new Temp(); // temporário para guardar o resultado

        Stm cond = new CJUMP(CJUMP.LT, left, right, trueLabel, falseLabel);

        // Constrói a expressão como:
        // r = 1
        // if e1 < e2 goto trueLabel else falseLabel
        // falseLabel: r = 0
        // end

        Stm stm = new SEQ(
            new MOVE(new TEMP(r), new CONST(1)),
            new SEQ(
                cond,
                new SEQ(
                    new LABEL(falseLabel),
                    new SEQ(
                        new MOVE(new TEMP(r), new CONST(0)),
                        new LABEL(trueLabel)
                    )
                )
            )
        );

        return new TranslatedExp(stm, new TEMP(r));
    }

    @Override
    public TranslatedExp visit(And n) {
        // Labels
        Label trueLabel = new Label();
        Label falseLabel = new Label();
        Label endLabel = new Label();
        Temp r = new Temp(); // resultado final

        // Expressões booleanas
        TranslatedExp left = n.e1.accept(this);
        TranslatedExp right = n.e2.accept(this);

        // Estrutura:
        // if (!left) goto false
        // if (!right) goto false
        // r = 1; goto end
        // false: r = 0
        // end:

        Stm andStm = new SEQ(
            left.unCx(trueLabel, falseLabel),
            new SEQ(
                new LABEL(trueLabel),
                new SEQ(
                    right.unCx(endLabel, falseLabel),
                    new SEQ(
                        new LABEL(endLabel),
                        new MOVE(new TEMP(r), new CONST(1))
                    )
                )
            )
        );

        // final false case
        andStm = new SEQ(
            andStm,
            new SEQ(
                new LABEL(falseLabel),
                new SEQ(
                    new MOVE(new TEMP(r), new CONST(0)),
                    new LABEL(endLabel)
                )
            )
        );

        return new TranslatedExp(andStm, new TEMP(r));
    }

    @Override
    public TranslatedExp visit(ArrayAssign n) {
        // Traduz as partes
        Exp1 arr = n.i.accept(this).unEx();
        Exp1 index = n.e1.accept(this).unEx();
        Exp1 value = n.e2.accept(this).unEx();

        // offset = (index + 1) * wordSize
        Exp1 offset = new BINOP(BINOP.PLUS, index, new CONST(1));
        offset = new BINOP(BINOP.MUL, offset, new CONST(currentFrame.wordSize()));

        // addr = arr + offset
        Exp1 addr = new BINOP(BINOP.PLUS, arr, offset);

        // gera: MEM[addr] = value
        Stm move = new MOVE(new MEM(addr), value);

        return new TranslatedExp(move);
    }

    @Override
    public TranslatedExp visit(ArrayLookup n) {
        // Traduz os operandos
        Exp1 arr = n.e1.accept(this).unEx();
        Exp1 index = n.e2.accept(this).unEx();

        // offset = (index + 1) * wordSize
        Exp1 offset = new BINOP(BINOP.PLUS, index, new CONST(1));
        offset = new BINOP(BINOP.MUL, offset, new CONST(currentFrame.wordSize()));

        // addr = arr + offset
        Exp1 addr = new BINOP(BINOP.PLUS, arr, offset);

        // MEM[addr]
        return new TranslatedExp(new MEM(addr));
    }

    @Override
    public TranslatedExp visit(ArrayLength n) {
        Exp1 arr = n.e.accept(this).unEx();

        // O tamanho do array está no índice 0
        return new TranslatedExp(new MEM(arr));
    }

    @Override
    public TranslatedExp visit(Call n) {
        // Traduz a instância (objeto)
        Exp1 obj = n.e.accept(this).unEx();

        // Traduz os argumentos
        ExpList args = null;
        for (int i = n.el.size() - 1; i >= 0; i--) {
            Exp1 arg = n.el.elementAt(i).accept(this).unEx();
            args = new ExpList(arg, args);
        }

        // Adiciona o objeto como primeiro argumento ("this")
        args = new ExpList(obj, args);

        // Monta o label: ClassName$MethodName
        String className = currentClass.name.toString();
        String methodName = n.i.s.getName();
        Label methodLabel = new Label(className + "$" + methodName);

        // Cria a chamada
        Exp1 call = new CALL(new NAME(methodLabel), args);

        return new TranslatedExp(call);
    }

    @Override
    public TranslatedExp visit(IntegerLiteral n) {
        return new TranslatedExp(new CONST(n.i));
    }

    @Override
    public TranslatedExp visit(True n) {
        return new TranslatedExp(new CONST(1));
    }

    @Override
    public TranslatedExp visit(False n) {
        return new TranslatedExp(new CONST(0));
    }

    @Override
    public TranslatedExp visit(IdentifierExp n) {
        Symbol name = n.s;

        Access acc = varAccessMap.get(name);

        if (acc == null && currentClass != null) {
            // Verifica se é um campo da classe
            Type fieldType = currentClass.fields.get(name);
            if (fieldType != null) {
                // Acesso via MEM(this + offset)
                Exp1 thisTemp = new TEMP(currentFrame.FP());
                Exp1 fieldAccess = new MEM(new BINOP(BINOP.PLUS, thisTemp, new CONST(0)));
                return new TranslatedExp(fieldAccess);
            }
        }

        if (acc == null) {
            throw new RuntimeException("Variável não encontrada no escopo: " + name.getName());
        }

        Exp1 accessExp = acc.exp(new TEMP(currentFrame.FP()));
        return new TranslatedExp(accessExp);
    }

    @Override
    public TranslatedExp visit(This n) {
        return new TranslatedExp(new TEMP(currentFrame.FP()));
    }

    @Override
    public TranslatedExp visit(NewArray n) {
        // Tamanho do array
        Exp1 size = n.e.accept(this).unEx();

        // Soma 1 para guardar o tamanho na posição 0
        Exp1 totalSize = new BINOP(BINOP.PLUS, size, new CONST(1));

        // Converte para bytes
        Exp1 sizeBytes = new BINOP(BINOP.MUL, totalSize, new CONST(currentFrame.wordSize()));

        // Chamada externa: halloc(sizeBytes)
        List<Exp1> javaArgs = new LinkedList<>();
        javaArgs.add(sizeBytes);

        Exp1 call = currentFrame.externalCall("halloc", toExpList(javaArgs));

        return new TranslatedExp(call);
    }

    @Override
    public TranslatedExp visit(NewObject n) {
        // Descobrir a classe
        Symbol className = n.i.s;
        ClassInfo classInfo = tableProgram.getClass(className);

        // Tamanho: 1 + número de atributos
        int nFields = classInfo.fields.size();
        Exp1 size = new CONST(1 + nFields);
        Exp1 sizeInBytes = new BINOP(BINOP.MUL, size, new CONST(currentFrame.wordSize()));

        // Alocação com halloc
        Exp1 call = currentFrame.externalCall("halloc", new ExpList(sizeInBytes, null));

        return new TranslatedExp(call);
    }

    @Override
    public TranslatedExp visit(Not n) {
        Exp1 expr = n.e.accept(this).unEx();
        Exp1 negated = new BINOP(BINOP.MINUS, new CONST(1), expr);
        return new TranslatedExp(negated);
    }

    // nós sem tradução direta
    @Override
    public TranslatedExp visit(VarDecl n) {
        return null;
    }

    @Override
    public TranslatedExp visit(Formal n) {
        return null;
    }

    @Override
    public TranslatedExp visit(IntArrayType n) {
        return null;
    }

    @Override
    public TranslatedExp visit(BooleanType n) {
        return null;
    }

    @Override
    public TranslatedExp visit(IntegerType n) {
        return null;
    }

    @Override
    public TranslatedExp visit(IdentifierType n) {
        return null;
    }

    @Override
    public TranslatedExp visit(Identifier n) {
        Symbol name = n.s;

        // Tenta pegar acesso local (parâmetro ou variável local)
        Access acc = varAccessMap.get(name);
        if (acc != null) {
            return new TranslatedExp(acc.exp(new TEMP(currentFrame.FP())));
        }

        // Caso contrário, tenta buscar como campo da classe
        if (currentClass != null && currentClass.fields.containsKey(name)) {
            int offset = fieldOffset(currentClass, name);
            Exp1 addr = new BINOP(BINOP.PLUS, new TEMP(currentFrame.FP()), new CONST(offset));
            return new TranslatedExp(new MEM(addr));
        }

        throw new RuntimeException("Variável não encontrada (Identifier): " + name);
    }

    @Override
    public TranslatedExp visit(Block n) {
        Stm seq = new EXP(new CONST(0)); // inicia com algo neutro

        for (int i = 0; i < n.sl.size(); i++) {
            Stm s = n.sl.elementAt(i).accept(this).unNx();
            seq = new SEQ(seq, s);
        }

        return new TranslatedExp(seq);
    }

    private ExpList toExpList(List<Exp1> args) {
        if (args == null || args.isEmpty()) return null;
        ExpList list = new ExpList(args.get(0), null);
        ExpList head = list;
        for (int i = 1; i < args.size(); i++) {
            list.tail = new ExpList(args.get(i), null);
            list = list.tail;
        }
        return head;
    }

    public Frag getFrags() {
        return fragHead.getNext(); // pula o dummy inicial
    }

    private int fieldOffset(ClassInfo classInfo, Symbol fieldName) {
        int index = 0;
        for (Symbol field : classInfo.fields.keySet()) {
            if (field.equals(fieldName)) return index * currentFrame.wordSize();
            index++;
        }
        throw new RuntimeException("Campo não encontrado: " + fieldName);
    }
}
