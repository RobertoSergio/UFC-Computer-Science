package br.ufc.compiladores.exception;

public class UndefinedTypeException extends BaseException {
    public UndefinedTypeException(String typeName) {
        super("Tipo não declarado: '" + typeName + "'");
    }
}