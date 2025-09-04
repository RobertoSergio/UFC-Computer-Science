package br.ufc.compiladores.exception;

public class UnexpectedTypeException extends BaseException {
    public UnexpectedTypeException(String expected, String found) {
        super("Tipo inesperado: esperado " + expected + ", mas encontrado " + found);
    }
}