package br.ufc.compiladores.canon;

import br.ufc.compiladores.tree.StmList;

public class StmListList {
  public StmList head;
  public StmListList tail;
  public StmListList(StmList h, StmListList t) {head=h; tail=t;}
}

