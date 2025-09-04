package br.ufc.compiladores.tree;

import br.ufc.compiladores.jouette.Codegen;
import br.ufc.compiladores.temp.Temp;


public class TEMP extends Exp1 {
    public Temp temp;
    public TEMP(Temp t) {temp=t;}
    public ExpList kids() {return null;}
    public Exp1 build(ExpList kids) {return this;}
    public Temp accept(Codegen codegen) {
        return codegen.visit(this);
    }
}
  