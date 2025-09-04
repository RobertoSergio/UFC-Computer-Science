package br.ufc.compiladores.exception;

public class MethodUndefinedReturnTypeException extends BaseException {
    public MethodUndefinedReturnTypeException(String methodName) {
        super("Método '" + methodName + "' possui tipo de retorno indefinido.");
    }
}