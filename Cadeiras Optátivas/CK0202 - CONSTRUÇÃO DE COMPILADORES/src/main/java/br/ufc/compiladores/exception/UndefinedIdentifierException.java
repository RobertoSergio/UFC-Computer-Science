package br.ufc.compiladores.exception;

import br.ufc.compiladores.semant.Symbol;

public class UndefinedIdentifierException extends BaseException {
    public UndefinedIdentifierException(Symbol identifier) {
        super("Variável não declarada: '" + identifier.getName() + "'");
    }
}