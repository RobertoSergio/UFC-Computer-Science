package br.ufc.compiladores.mips;

import br.ufc.compiladores.frame.Access;
import br.ufc.compiladores.tree.*;

public class InFrame extends Access {
    int offset;

    public InFrame(int o) {
        offset = o;
    }

    public Exp1 exp(Exp1 fp) {
        return new MEM(new BINOP(BINOP.PLUS, fp, new CONST(offset)));
    }

    public String toString() {
        return Integer.toString(this.offset);
    }
}
