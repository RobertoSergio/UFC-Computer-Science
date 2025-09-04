package br.ufc.compiladores.visitor;

import br.ufc.compiladores.jouette.Codegen;
import br.ufc.compiladores.syntaxtree.*;
import br.ufc.compiladores.translate.TranslatedExp;

public interface IRTreeVisitor {
    public TranslatedExp visit(Program n);

    public TranslatedExp visit(MainClass n);

    public TranslatedExp visit(ClassDeclSimple n);

    public TranslatedExp visit(ClassDeclExtends n);

    public TranslatedExp visit(VarDecl n);

    public TranslatedExp visit(MethodDecl n);

    public TranslatedExp visit(Formal n);

    public TranslatedExp visit(IntArrayType n);

    public TranslatedExp visit(BooleanType n);

    public TranslatedExp visit(IntegerType n);

    public TranslatedExp visit(IdentifierType n);

    public TranslatedExp visit(Block n);

    public TranslatedExp visit(If n);

    public TranslatedExp visit(While n);

    public TranslatedExp visit(Print n);

    public TranslatedExp visit(Assign n);

    public TranslatedExp visit(ArrayAssign n);

    public TranslatedExp visit(And n);

    public TranslatedExp visit(LessThan n);

    public TranslatedExp visit(Plus n);

    public TranslatedExp visit(Minus n);

    public TranslatedExp visit(Times n);

    public TranslatedExp visit(ArrayLookup n);

    public TranslatedExp visit(ArrayLength n);

    public TranslatedExp visit(Call n);

    public TranslatedExp visit(IntegerLiteral n);

    public TranslatedExp visit(True n);

    public TranslatedExp visit(False n);

    public TranslatedExp visit(IdentifierExp n);

    public TranslatedExp visit(This n);

    public TranslatedExp visit(NewArray n);

    public TranslatedExp visit(NewObject n);

    public TranslatedExp visit(Not n);

    public TranslatedExp visit(Identifier n);
}