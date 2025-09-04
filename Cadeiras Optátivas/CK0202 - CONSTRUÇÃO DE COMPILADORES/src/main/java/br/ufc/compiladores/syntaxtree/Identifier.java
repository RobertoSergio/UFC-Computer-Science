package br.ufc.compiladores.syntaxtree;
import br.ufc.compiladores.visitor.Visitor;
import br.ufc.compiladores.semant.Symbol;
import br.ufc.compiladores.translate.TranslatedExp;
import br.ufc.compiladores.visitor.IRTreeVisitor;
import br.ufc.compiladores.visitor.TypeVisitor;

public class Identifier {
  public Symbol s;

  public Identifier(Symbol as) { 
    s = as;
  }

  public void accept(Visitor v) {
    v.visit(this);
  }

  public Type accept(TypeVisitor v) {
    return v.visit(this);
  }

  @Override
  public String toString() {
    return s.toString();
  }
  
  public TranslatedExp accept(IRTreeVisitor v) {
    return v.visit(this);
  }
}
