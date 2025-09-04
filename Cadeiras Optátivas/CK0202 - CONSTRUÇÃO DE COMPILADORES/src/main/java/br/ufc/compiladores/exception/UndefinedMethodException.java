package br.ufc.compiladores.exception;

import br.ufc.compiladores.semant.Symbol;

public class UndefinedMethodException extends BaseException {
    public UndefinedMethodException(Symbol methodName, Symbol className) {
        super("Método '" + methodName.getName() + "' não encontrado na classe '" + className.getName() + "'");
    }
}