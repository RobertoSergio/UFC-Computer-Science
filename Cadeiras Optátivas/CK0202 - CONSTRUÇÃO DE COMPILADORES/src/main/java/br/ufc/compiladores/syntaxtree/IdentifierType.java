package br.ufc.compiladores.syntaxtree;
import br.ufc.compiladores.visitor.Visitor;
import br.ufc.compiladores.visitor.IRTreeVisitor;
import br.ufc.compiladores.visitor.TypeVisitor;
import br.ufc.compiladores.semant.Symbol;
import br.ufc.compiladores.translate.TranslatedExp;

public class IdentifierType extends Type {
  public Symbol s;

  public IdentifierType(Symbol s) {
    this.s = s;
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public Type accept(TypeVisitor v) {
    return v.visit(this);
  }
  
  public TranslatedExp accept(IRTreeVisitor v) {
    return v.visit(this);
  }
}
