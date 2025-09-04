package br.ufc.compiladores.semant;

import java.util.HashMap;

public class Symbol {
    private String name;

    private Symbol(String n) {
        name = n;
    }

    private static HashMap<String, Symbol> table = new HashMap<>();

    public static Symbol symbol(String n) {
        Symbol s = table.get(n);
        if (s == null) {
            s = new Symbol(n);
            table.put(n, s);
        }
        return s;
    }

    public String toString() {
        return name;
    }

    // Opcional: getter
    public String getName() {
        return name;
    }
}
