package br.ufc.compiladores.exception;

import br.ufc.compiladores.semant.Symbol;

public class ElementAlreadyDefinedException extends BaseException {
    public ElementAlreadyDefinedException(Symbol name, Symbol context) {
        super("Elemento já definido: '" + name.getName() + "' em " + context.getName());
    }
}