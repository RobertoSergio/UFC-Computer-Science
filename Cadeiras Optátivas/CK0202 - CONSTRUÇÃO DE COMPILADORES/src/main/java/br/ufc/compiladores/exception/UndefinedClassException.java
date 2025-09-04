package br.ufc.compiladores.exception;

import br.ufc.compiladores.semant.Symbol;

public class UndefinedClassException extends BaseException {
    public UndefinedClassException(Symbol className) {
        super("Classe não declarada: '" + className.getName() + "'");
    }
}