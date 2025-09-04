package br.ufc.compiladores.translate;

import br.ufc.compiladores.tree.*;
import br.ufc.compiladores.temp.Label;

public class TranslatedExp {
    private Exp1 exp1, exp2;
    private Stm stm;

    public TranslatedExp(Exp1 e) {
        exp1 = e;
    }

    public TranslatedExp(Exp1 e1, Exp1 e2) {
        exp1 = e1;
        exp2 = e2;
    }

    public TranslatedExp(Stm s, Exp1 e) {
        this.stm = s;
        this.exp1 = e;
    }

    public TranslatedExp(Stm s1) {
        stm = s1;
    }

    // Expressão que retorna valor
    public Exp1 unEx() {
        return exp1;
    }

    // Statement sem valor
    public Stm unNx() {
        return stm;
    }

    // Condicional com desvio
    public Stm unCx(Label t, Label f) {
        if (exp2 == null)
            return new CJUMP(CJUMP.NE, exp1, new CONST(0), t, f);
        return new CJUMP(CJUMP.LT, exp1, exp2, t, f);
    }
}
