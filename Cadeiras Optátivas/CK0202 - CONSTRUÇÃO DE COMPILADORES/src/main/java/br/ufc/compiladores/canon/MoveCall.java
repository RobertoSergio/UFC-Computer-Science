package br.ufc.compiladores.canon;

import br.ufc.compiladores.tree.*;
import br.ufc.compiladores.jouette.Codegen;


public class MoveCall extends Stm {
    public TEMP dst;
    public CALL src;
    MoveCall(TEMP d, CALL s) {dst=d; src=s;}
    public ExpList kids() {return src.kids();}
    public Stm build(ExpList kids) {
      return new MOVE(dst, src.build(kids));
    } 
    public void accept(Codegen codegen) {
      codegen.visit(this);
    }
  }   
    