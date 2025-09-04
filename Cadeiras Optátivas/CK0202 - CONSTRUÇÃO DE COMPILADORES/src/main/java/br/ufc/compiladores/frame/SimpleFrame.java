package br.ufc.compiladores.frame;

import java.util.ArrayList;
import java.util.List;

import br.ufc.compiladores.temp.*;
import br.ufc.compiladores.tree.*;
import br.ufc.compiladores.assem.Instr;
import br.ufc.compiladores.semant.Symbol;
import br.ufc.compiladores.mips.InFrame;

public class SimpleFrame extends Frame {
    private Temp rv = new Temp();
    private Temp fp = new Temp();
    private Temp[] regs = new Temp[0];

    public SimpleFrame(Symbol name, List<Boolean> formals) {
        this.name = new Label(name.getName());
        this.formals = new ArrayList<>();
        for (boolean escape : formals) {
            this.formals.add(allocLocal(escape));
        }
    }

    @Override
    public Frame newFrame(Symbol name, List<Boolean> formals) {
        return new SimpleFrame(name, formals);
    }

    @Override
    public Access allocLocal(boolean escape) {
        return new InFrame(0); // substitua por lógica real
    }

    @Override
    public Temp FP() { return fp; }

    @Override
    public int wordSize() { return 4; }

    @Override
    public Exp1 externalCall(String func, ExpList args) {
        return new CALL(new NAME(new Label(func)), args);
    }

    @Override
    public Temp RV() { return rv; }

    @Override
    public String string(Label label, String value) { return ""; }

    @Override
    public Label badPtr() { return new Label("badPtr"); }

    @Override
    public Label badSub() { return new Label("badSub"); }

    @Override
    public String tempMap(Temp temp) { return temp.toString(); }

    //@Override
    //public List<Instr> codegen(List<Stm> stms) { return new ArrayList<>(); }

    @Override
    public void procEntryExit1(List<Stm> body) { }

    @Override
    public void procEntryExit2(List<Instr> body) { }

    @Override
    public void procEntryExit3(List<Instr> body) { }

    @Override
    public Temp[] registers() { return regs; }

    //@Override
    //public void spill(List<Instr> insns, Temp[] spills) { }

    @Override
    public String programTail() { return ""; }

    @Override
    public List<Access> formals() {
        return formals;
    }
}
