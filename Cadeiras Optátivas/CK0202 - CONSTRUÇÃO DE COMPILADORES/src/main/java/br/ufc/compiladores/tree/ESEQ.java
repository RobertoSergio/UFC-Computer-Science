package br.ufc.compiladores.tree;

import br.ufc.compiladores.jouette.Codegen;
import br.ufc.compiladores.temp.Temp;

public class ESEQ extends Exp1 {
  public Stm stm;
  public Exp1 exp;
  public ESEQ(Stm s, Exp1 e) {stm=s; exp=e;}
  public ExpList kids() {throw new Error("kids() not applicable to ESEQ");}
  public Exp1 build(ExpList kids) {throw new Error("build() not applicable to ESEQ");}
  
  public Temp accept(Codegen codegen) {
    return codegen.visit(this);
  }
}
