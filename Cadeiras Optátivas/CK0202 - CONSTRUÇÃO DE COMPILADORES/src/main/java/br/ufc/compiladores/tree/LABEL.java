package br.ufc.compiladores.tree;

import br.ufc.compiladores.jouette.Codegen;
import br.ufc.compiladores.temp.Label;

public class LABEL extends Stm { 
  public Label label;
  public LABEL(Label l) {label=l;}
  public ExpList kids() {return null;}
  public Stm build(ExpList kids) {
    return this;
  }
  public void accept(Codegen codegen) {
    codegen.visit(this);
  }
}
