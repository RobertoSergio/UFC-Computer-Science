package br.ufc.compiladores.tree;

import br.ufc.compiladores.jouette.Codegen;
import br.ufc.compiladores.temp.Temp;

public class CONST extends Exp1 {
  public int value;
  public CONST(int v) {value=v;}
  public ExpList kids() {return null;}
  public Exp1 build(ExpList kids) {return this;}
  public Temp accept(Codegen codegen) {
    return codegen.visit(this);
  }
}
