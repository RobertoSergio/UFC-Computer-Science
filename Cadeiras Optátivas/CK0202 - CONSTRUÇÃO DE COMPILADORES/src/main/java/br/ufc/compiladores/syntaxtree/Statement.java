package br.ufc.compiladores.syntaxtree;
import br.ufc.compiladores.visitor.Visitor;
import br.ufc.compiladores.translate.TranslatedExp;
import br.ufc.compiladores.visitor.IRTreeVisitor;
import br.ufc.compiladores.visitor.TypeVisitor;

public abstract class Statement {
  public abstract void accept(Visitor v);
  public abstract Type accept(TypeVisitor v);
  public abstract TranslatedExp accept(IRTreeVisitor v);
}
