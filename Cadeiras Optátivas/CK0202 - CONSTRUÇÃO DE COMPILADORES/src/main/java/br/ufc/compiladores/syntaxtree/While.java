package br.ufc.compiladores.syntaxtree;
import br.ufc.compiladores.visitor.Visitor;
import br.ufc.compiladores.translate.TranslatedExp;
import br.ufc.compiladores.visitor.IRTreeVisitor;
import br.ufc.compiladores.visitor.TypeVisitor;

public class While extends Statement {
  public Exp e;
  public Statement s;

  public While(Exp ae, Statement as) {
    e=ae; s=as; 
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

