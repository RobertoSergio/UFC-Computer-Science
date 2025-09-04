package br.ufc.compiladores.exception;

import br.ufc.compiladores.semant.Symbol;

public class IncompatibleAssignmentException extends BaseException {
    public IncompatibleAssignmentException(Symbol varName, String expected, String found) {
        super("Atribuição incompatível para '" + varName.getName() + "': esperado " + expected + ", encontrado " + found);
    }
}