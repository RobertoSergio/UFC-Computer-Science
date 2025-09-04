package br.ufc.compiladores.tree;

import br.ufc.compiladores.jouette.Codegen;
import br.ufc.compiladores.temp.Label;
import br.ufc.compiladores.temp.Temp;

public class NAME extends Exp1 {
  public Label label;
  public NAME(Label l) {label=l;}
  public ExpList kids() {return null;}
  public Exp1 build(ExpList kids) {return this;}
  public Temp accept(Codegen codegen) {
    return codegen.visit(this);
  }
}
