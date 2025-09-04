package br.ufc.compiladores.translate;

import br.ufc.compiladores.frame.Frame;
import br.ufc.compiladores.frag.Frag;
import br.ufc.compiladores.semant.Symbol;

public class Translate {
    public Frame frame;
    public Frag frags;
    public Symbol className;
    public Symbol methodName;

    public Translate(Frame frame) {
        this.frame = frame;
    }

    public void addFrag(Frag frag) {
        frag.next = frags;
        frags = frag;
    }

    public Frag getFrags() {
        return frags;
    }
}
