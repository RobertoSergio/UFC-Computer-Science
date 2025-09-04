package br.ufc.compiladores.semant;

import java.util.Collection;
import java.util.HashMap;

public class SymbolTable {
    private HashMap<Symbol, ClassInfo> classes = new HashMap<>();


    public boolean addClass(Symbol name, Symbol superClass) {
        return classes.putIfAbsent(name, new ClassInfo(name, superClass)) == null;
    }

    public boolean addClass(Symbol name) {
        return addClass(name, null);
    }

    public boolean containsClass(Symbol name) {
        return classes.containsKey(name);
    }

    public ClassInfo getClass(Symbol name) {
        return classes.get(name);
    }

    public Collection<ClassInfo> getClasses() {
        return classes.values();
    }
}
