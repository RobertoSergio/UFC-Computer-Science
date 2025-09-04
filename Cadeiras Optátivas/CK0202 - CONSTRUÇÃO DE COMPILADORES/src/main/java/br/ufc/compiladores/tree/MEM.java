package br.ufc.compiladores.tree;

import br.ufc.compiladores.jouette.Codegen;
import br.ufc.compiladores.temp.Temp;

public class MEM extends Exp1 {
  public Exp1 exp;
  public MEM(Exp1 e) {exp=e;}
  public ExpList kids() {return new ExpList(exp,null);}
  public Exp1 build(ExpList kids) {
    return new MEM(kids.head);
  }
  public Temp accept(Codegen codegen) {
    return codegen.visit(this);
  }
}
