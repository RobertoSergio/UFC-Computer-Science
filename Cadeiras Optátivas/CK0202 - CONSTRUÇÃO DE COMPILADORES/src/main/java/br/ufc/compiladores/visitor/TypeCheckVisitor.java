    package br.ufc.compiladores.visitor;

    import br.ufc.compiladores.exception.*;
    import br.ufc.compiladores.semant.*;
    import br.ufc.compiladores.syntaxtree.*;

    public class TypeCheckVisitor implements TypeVisitor {
        private final SymbolTable symbolTable;
        private Symbol currentClass;
        private Symbol currentMethod;

        public TypeCheckVisitor(SymbolTable st) {
            this.symbolTable = st;
        }

        // ======= Expressões Básicas =======

        @Override
        public Type visit(Plus n) {
            Type t1 = n.e1.accept(this);
            Type t2 = n.e2.accept(this);
            checkInt(t1); checkInt(t2);
            return new IntegerType();
        }

        @Override
        public Type visit(Minus n) {
            Type t1 = n.e1.accept(this);
            Type t2 = n.e2.accept(this);
            checkInt(t1); checkInt(t2);
            return new IntegerType();
        }

        @Override
        public Type visit(Times n) {
            Type t1 = n.e1.accept(this);
            Type t2 = n.e2.accept(this);
            checkInt(t1); checkInt(t2);
            return new IntegerType();
        }

        @Override
        public Type visit(And n) {
            Type t1 = n.e1.accept(this);
            Type t2 = n.e2.accept(this);
            checkBool(t1); checkBool(t2);
            return new BooleanType();
        }

        @Override
        public Type visit(LessThan n) {
            Type t1 = n.e1.accept(this);
            Type t2 = n.e2.accept(this);
            checkInt(t1); checkInt(t2);
            return new BooleanType();
        }

        @Override
        public Type visit(IntegerLiteral n) {
            return new IntegerType();
        }

        @Override
        public Type visit(True n) {
            return new BooleanType();
        }

        @Override
        public Type visit(False n) {
            return new BooleanType();
        }

        @Override
        public Type visit(Not n) {
            Type t = n.e.accept(this);
            checkBool(t);
            return new BooleanType();
        }

        @Override
        public Type visit(IdentifierExp n) {
            return lookupVar(n.s);
        }

        @Override
        public Type visit(This n) {
            return new IdentifierType(currentClass);
        }

        // ======= Controle de Fluxo =======

        @Override
        public Type visit(If n) {
            Type cond = n.e.accept(this);
            checkBool(cond);
            n.s1.accept(this);
            n.s2.accept(this);
            return null;
        }

        @Override
        public Type visit(While n) {
            Type cond = n.e.accept(this);
            checkBool(cond);
            n.s.accept(this);
            return null;
        }

        @Override
        public Type visit(Print n) {
            Type t = n.e.accept(this);
            checkInt(t); // MiniJava só imprime inteiros
            return null;
        }

        // ======= Variáveis e Atribuições =======

        @Override
        public Type visit(Assign n) {
            Type t1 = lookupVar(n.i.s);
            Type t2 = n.e.accept(this);
            if (!equalTypes(t1, t2)) {
                throw new IncompatibleAssignmentException(n.i.s, typeName(t1), typeName(t2));
            }
            return null;
        }

        @Override
        public Type visit(VarDecl n) {
            return null;
        }

        // ======= Chamadas de método =======

        @Override
        public Type visit(Call n) {
            Type objType = n.e.accept(this);
            if (!(objType instanceof IdentifierType)) {
                throw new UnexpectedTypeException("classe", typeName(objType));
            }

            Symbol className = ((IdentifierType) objType).s;
            ClassInfo cInfo = symbolTable.getClass(className);
            if (cInfo == null) {
                throw new UndefinedClassException(className);
            }

            MethodInfo mInfo = resolveMethod(className, n.i.s);

            if (mInfo == null) {
                throw new UndefinedMethodException(n.i.s, className);
            }

            if (n.el.size() != mInfo.parameters.size()) {
                throw new IncompatibleAssignmentException(
                    n.i.s, mInfo.parameters.size() + " argumento(s)", n.el.size() + " fornecido(s)"
                );
            } 

            int i = 0;
            for (java.util.Map.Entry<Symbol, Type> param : mInfo.parameters.entrySet()) {
                Type arg = n.el.elementAt(i).accept(this);
                if (!equalTypes(arg, param.getValue())) {
                    throw new IncompatibleAssignmentException(
                        param.getKey(),
                        typeName(param.getValue()),
                        typeName(arg)
                    );
                }
                i++;
            }

            return mInfo.returnType;
        }

        private MethodInfo resolveMethod(Symbol className, Symbol methodName) {
            while (className != null) {
                ClassInfo c = symbolTable.getClass(className);
                if (c == null) return null;
                MethodInfo m = c.getMethod(methodName);
                if (m != null) return m;
                className = c.superClass;
            }
            return null;
        }

        // ======= Outras expressões =======

        @Override
        public Type visit(NewObject n) {
            Symbol className = n.i.s;
            if (!symbolTable.containsClass(className)) {
                throw new UndefinedClassException(className);
            }
            return new IdentifierType(className);
        }

        @Override
        public Type visit(NewArray n) {
            Type t = n.e.accept(this);
            checkInt(t);
            return new IntArrayType();
        }

        @Override
        public Type visit(ArrayLookup n) {
            checkInt(n.e2.accept(this));
            Type arr = n.e1.accept(this);
            if (!(arr instanceof IntArrayType)) {
                throw new UnexpectedTypeException("int[]", typeName(arr));
            }
            return new IntegerType();
        }

        @Override
        public Type visit(ArrayLength n) {
            Type t = n.e.accept(this);
            if (!(t instanceof IntArrayType)) {
                throw new UnexpectedTypeException("int[]", typeName(t));
            }
            return new IntegerType();
        }

        // ======= Programa e Declarações =======

        @Override
        public Type visit(Program n) {
            n.m.accept(this);
            for (int i = 0; i < n.cl.size(); i++) {
                n.cl.elementAt(i).accept(this);
            }
            return null;
        }

        @Override
        public Type visit(MainClass n) {
            currentClass = n.i1.s;
            currentMethod = Symbol.symbol("main");
            n.s.accept(this);
            currentMethod = null;
            currentClass = null;
            return null;
        }

        @Override
        public Type visit(ClassDeclSimple n) {
            currentClass = n.i.s;
            for (int i = 0; i < n.ml.size(); i++) {
                n.ml.elementAt(i).accept(this);
            }
            currentClass = null;
            return null;
        }

        @Override
        public Type visit(ClassDeclExtends n) {
            currentClass = n.i.s;
            for (int i = 0; i < n.ml.size(); i++) {
                n.ml.elementAt(i).accept(this);
            }
            currentClass = null;
            return null;
        }

        @Override
        public Type visit(MethodDecl n) {
            currentMethod = n.i.s;
            for (int i = 0; i < n.sl.size(); i++) {
                n.sl.elementAt(i).accept(this);
            }

            Type expected = n.t;
            Type actual = n.e.accept(this);
            if (!equalTypes(expected, actual)) {
                throw new IncompatibleAssignmentException(
                    Symbol.symbol("return"), typeName(expected), typeName(actual)
                );        
            }
            currentMethod = null;
            return null;
        }

        // ======= Helpers =======

        private void checkInt(Type t) {
            if (!(t instanceof IntegerType)) {
                throw new UnexpectedTypeException("int", typeName(t));
            }
        }

        private void checkBool(Type t) {
            if (!(t instanceof BooleanType)) {
                throw new UnexpectedTypeException("boolean", typeName(t));
            }
        }

        private boolean equalTypes(Type t1, Type t2) {
            if (t1 == null || t2 == null) return false;
            return t1.getClass().equals(t2.getClass());
        }

        private Type lookupVar(Symbol sym) {
            ClassInfo cInfo = symbolTable.getClass(currentClass);
            MethodInfo mInfo = cInfo.getMethod(currentMethod);

            Type t = mInfo.getVarType(sym);
            if (t != null) return t;

            Symbol className = currentClass;
            while (className != null) {
                cInfo = symbolTable.getClass(className);
                if (cInfo == null) break;
                t = cInfo.fields.get(sym);
                if (t != null) return t;
                className = cInfo.superClass;
            }

            throw new UndefinedIdentifierException(sym);
        }

        @Override
        public Type visit(Identifier n) {
            return null; // Usado apenas como parte de outros nós (como IdentifierExp)
        }

        @Override
        public Type visit(ArrayAssign n) {
            Type t1 = lookupVar(n.i.s);
            
            if (!(t1 instanceof IntArrayType)) {
                throw new UnexpectedTypeException("int[]", typeName(t1));
            }

            checkInt(n.e1.accept(this));

            Type t2 = n.e2.accept(this);
            checkInt(t2);
            
            return null;
        }

        @Override
        public Type visit(Block n) {
            for (int i = 0; i < n.sl.size(); i++) {
                n.sl.elementAt(i).accept(this);
            }
            return null;
        }

        @Override
        public Type visit(IdentifierType n) {
            return n;
        }

        @Override
        public Type visit(IntegerType n) {
            return n;
        }

        @Override
        public Type visit(BooleanType n) {
            return n;
        }

        @Override
        public Type visit(IntArrayType n) {
            return n;
        }

        @Override
        public Type visit(Formal n) {
            return null; // Tipos já verificados em MethodDecl
        }

        private String typeName(Type t) {
            if (t == null) return "null";
            if (t instanceof IntegerType) return "int";
            if (t instanceof BooleanType) return "boolean";
            if (t instanceof IntArrayType) return "int[]";
            if (t instanceof IdentifierType) return ((IdentifierType) t).s.getName(); 
            return "desconhecido";
        }
    }
