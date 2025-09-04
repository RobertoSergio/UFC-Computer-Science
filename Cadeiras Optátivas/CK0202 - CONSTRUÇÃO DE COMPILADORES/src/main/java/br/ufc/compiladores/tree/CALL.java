package br.ufc.compiladores.tree;

import br.ufc.compiladores.jouette.Codegen;
import br.ufc.compiladores.temp.Temp;

public class CALL extends Exp1 {
  public Exp1 func;
  public ExpList args;
  public CALL(Exp1 f, ExpList a) {func=f; args=a;}
  public ExpList kids() {return new ExpList(func,args);}
  public Exp1 build(ExpList kids) {
    return new CALL(kids.head,kids.tail);
  }
  public Temp accept(Codegen codegen) {
    return codegen.visit(this);
  }
}
