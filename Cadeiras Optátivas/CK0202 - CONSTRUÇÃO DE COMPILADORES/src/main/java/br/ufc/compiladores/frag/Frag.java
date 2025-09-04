package br.ufc.compiladores.frag;

public abstract class Frag {
    public Frag next;

    public void addNext(Frag f) {
        if (next == null)
            next = f;
        else
            next.addNext(f);
    }

    public Frag getNext() {
        return next;
    }
}