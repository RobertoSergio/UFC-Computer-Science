package br.ufc.compiladores.visitor;

import br.ufc.compiladores.semant.*;
import br.ufc.compiladores.syntaxtree.*;

public class BuildSymbolTableVisitor extends DepthFirstVisitor {

    private final SymbolTable symbolTable = new SymbolTable();
    private Symbol currentClass = null;
    private Symbol currentMethod = null;

    public SymbolTable getSymbolTable() {
        return symbolTable;
    }

    @Override
    public void visit(MainClass n) {
        Symbol className = n.i1.s;
        Symbol argName = n.i2.s;

        symbolTable.addClass(className);
        currentClass = className;

        MethodInfo mainMethod = new MethodInfo(null); // void
        mainMethod.addParam(argName, new IdentifierType(Symbol.symbol("String[]"))); // TODO: review
        
        Symbol mainSym = Symbol.symbol("main");
        symbolTable.getClass(currentClass).addMethod(mainSym, mainMethod);
        currentMethod = mainSym;

        n.s.accept(this); // visita o corpo

        currentMethod = null;
        currentClass = null;
    }

    @Override
    public void visit(ClassDeclSimple n) {
        Symbol className = n.i.s;

        symbolTable.addClass(className);
        currentClass = className;

        for (int i = 0; i < n.vl.size(); i++) {
            n.vl.elementAt(i).accept(this);
        }

        for (int i = 0; i < n.ml.size(); i++) {
            n.ml.elementAt(i).accept(this);
        }

        currentClass = null;
    }

    @Override
    public void visit(ClassDeclExtends n) {
        Symbol className = n.i.s;
        Symbol superClassName = n.j.s;
        
        symbolTable.addClass(className, superClassName);
        currentClass = className;

        for (int i = 0; i < n.vl.size(); i++) {
            n.vl.elementAt(i).accept(this);
        }

        for (int i = 0; i < n.ml.size(); i++) {
            n.ml.elementAt(i).accept(this);
        }

        currentClass = null;
    }

    @Override
    public void visit(VarDecl n) {
        Type type = n.t;
        Symbol name = n.i.s;

        ClassInfo cInfo = symbolTable.getClass(currentClass);

        if (currentMethod == null) {
            cInfo.addField(name, type);
        } else {
            MethodInfo mInfo = cInfo.getMethod(currentMethod);
            if (!mInfo.parameters.containsKey(name)) {
                mInfo.addLocal(name, type);
            }
        }
    }

    @Override
    public void visit(MethodDecl n) {
        Symbol methodName = n.i.s;
        Type returnType = n.t;

        MethodInfo mInfo = new MethodInfo(returnType);
        ClassInfo cInfo = symbolTable.getClass(currentClass);

        for (int i = 0; i < n.fl.size(); i++) {
            Formal f = n.fl.elementAt(i);
            mInfo.addParam(f.i.s, f.t);
        }

        if (!cInfo.addMethod(methodName, mInfo)) {
            System.err.println("Método duplicado: " + methodName + " na classe " + currentClass);
        }

        currentMethod = methodName;

        for (int i = 0; i < n.vl.size(); i++) {
            n.vl.elementAt(i).accept(this);
        }

        currentMethod = null;
    }
}
