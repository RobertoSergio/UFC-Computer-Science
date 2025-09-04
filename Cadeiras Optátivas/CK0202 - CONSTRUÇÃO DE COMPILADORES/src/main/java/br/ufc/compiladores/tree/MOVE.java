package br.ufc.compiladores.tree;

import br.ufc.compiladores.jouette.Codegen;

public class MOVE extends Stm {
  public Exp1 dst, src;
  public MOVE(Exp1 d, Exp1 s) {dst=d; src=s;}
  public ExpList kids() {
        if (dst instanceof MEM)
	   return new ExpList(((MEM)dst).exp, new ExpList(src,null));
	else return new ExpList(src,null);
  }
  public Stm build(ExpList kids) {
        if (dst instanceof MEM)
	   return new MOVE(new MEM(kids.head), kids.tail.head);
	else return new MOVE(dst, kids.head);
  }

  public void accept(Codegen codegen) {
    codegen.visit(this);
  }
}
