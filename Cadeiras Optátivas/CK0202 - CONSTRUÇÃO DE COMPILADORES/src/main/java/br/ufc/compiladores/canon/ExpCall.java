package br.ufc.compiladores.canon;

import br.ufc.compiladores.tree.*;
import br.ufc.compiladores.jouette.Codegen;


public class ExpCall extends Stm {
    public CALL call;
    ExpCall(CALL c) {call=c;}
    public ExpList kids() {return call.kids();}
    public Stm build(ExpList kids) {
      return new EXP(call.build(kids));
    }
    public void accept(Codegen codegen) {
      codegen.visit(this);
    }
  }   