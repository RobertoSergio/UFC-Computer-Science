package br.ufc.compiladores.tree;

import br.ufc.compiladores.jouette.Codegen;
import br.ufc.compiladores.temp.Temp;

public class BINOP extends Exp1 {
  public int binop;
  public Exp1 left, right;
  public BINOP(int b, Exp1 l, Exp1 r) {
    binop=b; left=l; right=r; 
  }
  public final static int PLUS=0, MINUS=1, MUL=2, DIV=3, 
		   AND=4,OR=5,LSHIFT=6,RSHIFT=7,ARSHIFT=8,XOR=9;
  public ExpList kids() {return new ExpList(left, new ExpList(right,null));}
  public Exp1 build(ExpList kids) {
    return new BINOP(binop,kids.head,kids.tail.head);
  }
  public Temp accept(Codegen codegen) {
    return codegen.visit(this);
  }
}
