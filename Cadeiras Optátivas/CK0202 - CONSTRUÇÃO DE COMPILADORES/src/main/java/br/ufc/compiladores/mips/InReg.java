package br.ufc.compiladores.mips;
import br.ufc.compiladores.temp.Temp;
import br.ufc.compiladores.frame.Access;
import br.ufc.compiladores.tree.Exp1;
import br.ufc.compiladores.tree.TEMP;

public class InReg extends Access {
    Temp temp;
    InReg(Temp t) {
	temp = t;
    }

    public Exp1 exp(Exp1 fp) {
        return new TEMP(temp);
    }

    public String toString() {
        return temp.toString();
    }
}
