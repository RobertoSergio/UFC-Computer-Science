package br.ufc.compiladores.frag;

import br.ufc.compiladores.tree.Stm;
import br.ufc.compiladores.frame.Frame;

public class ProcFrag extends Frag {
    public Stm body;
    public Frame frame;

    public ProcFrag(Stm b, Frame f) {
        this.body = b;
        this.frame = f;
    }
}