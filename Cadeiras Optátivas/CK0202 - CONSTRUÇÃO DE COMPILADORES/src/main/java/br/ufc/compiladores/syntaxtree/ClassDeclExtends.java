package br.ufc.compiladores.syntaxtree;
import br.ufc.compiladores.visitor.Visitor;
import br.ufc.compiladores.translate.TranslatedExp;
import br.ufc.compiladores.visitor.IRTreeVisitor;
import br.ufc.compiladores.visitor.TypeVisitor;

public class ClassDeclExtends extends ClassDecl {
  public Identifier i;
  public Identifier j;
  public VarDeclList vl;  
  public MethodDeclList ml;
 
  public ClassDeclExtends(Identifier ai, Identifier aj, 
                  VarDeclList avl, MethodDeclList aml) {
    i=ai; j=aj; vl=avl; ml=aml;
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
