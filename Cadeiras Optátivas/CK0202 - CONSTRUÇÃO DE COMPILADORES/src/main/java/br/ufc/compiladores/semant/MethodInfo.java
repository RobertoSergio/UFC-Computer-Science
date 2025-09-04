package br.ufc.compiladores.semant;

import java.util.LinkedHashMap;
import br.ufc.compiladores.syntaxtree.Type;

public class MethodInfo {
    public Type returnType;
    public LinkedHashMap<Symbol, Type> parameters = new LinkedHashMap<>();
    public LinkedHashMap<Symbol, Type> locals = new LinkedHashMap<>();

    public MethodInfo(Type returnType) {
        this.returnType = returnType;
    }

    public boolean addParam(Symbol name, Type type) {
        return parameters.putIfAbsent(name, type) == null;
    }

    public boolean addLocal(Symbol name, Type type) {
        return locals.putIfAbsent(name, type) == null;
    }

    public Type getVarType(Symbol name) {
        if (locals.containsKey(name)) return locals.get(name);
        return parameters.get(name);
    }
}