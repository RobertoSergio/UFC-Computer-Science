package br.ufc.compiladores.semant;

import java.util.HashMap;
import br.ufc.compiladores.syntaxtree.Type;

public class ClassInfo {
    public Symbol name;
    public Symbol superClass;
    public HashMap<Symbol, Type> fields = new HashMap<>();
    public HashMap<Symbol, MethodInfo> methods = new HashMap<>();

    public ClassInfo(Symbol name, Symbol superClass) {
        this.name = name;
        this.superClass = superClass;
    }

    public boolean addField(Symbol name, Type type) {
        return fields.putIfAbsent(name, type) == null;
    }

    public boolean addMethod(Symbol name, MethodInfo method) {
        return methods.putIfAbsent(name, method) == null;
    }

    public MethodInfo getMethod(Symbol name) {
        return methods.get(name);
    }
}
