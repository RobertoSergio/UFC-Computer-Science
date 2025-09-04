package br.ufc.compiladores.tree;

import br.ufc.compiladores.jouette.Codegen;
import br.ufc.compiladores.temp.Temp;

abstract public class Exp1 {
	abstract public ExpList kids();
	abstract public Exp1 build(ExpList kids);
  	public abstract Temp accept(Codegen cg);
}