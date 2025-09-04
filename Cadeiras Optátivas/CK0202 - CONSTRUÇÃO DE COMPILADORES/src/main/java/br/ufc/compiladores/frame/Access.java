package br.ufc.compiladores.frame;
import br.ufc.compiladores.tree.*;

public abstract class Access {
  public abstract String toString();
  public abstract Exp1 exp(Exp1 e);
}
