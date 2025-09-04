package br.ufc.compiladores.tree;

import br.ufc.compiladores.jouette.Codegen;

abstract public class Stm {
	abstract public ExpList kids();
	abstract public Stm build(ExpList kids);
	public abstract void accept(Codegen cg);
}
