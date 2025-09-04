package br.ufc.compiladores.frame;
import java.util.List;

import br.ufc.compiladores.temp.Temp;
import br.ufc.compiladores.temp.TempMap;
import br.ufc.compiladores.temp.Label;
import br.ufc.compiladores.tree.Exp1;
import br.ufc.compiladores.tree.Stm;
import br.ufc.compiladores.assem.Instr;
import br.ufc.compiladores.semant.Symbol;
import br.ufc.compiladores.tree.ExpList;


public abstract class Frame implements TempMap {
    public Label name;
    public List<Access> formals;
    public abstract List<Access> formals();
    public abstract Frame newFrame(Symbol name, List<Boolean> formals);
    public abstract Access allocLocal(boolean escape);
    public abstract Temp FP();
    public abstract int wordSize();
    public abstract Exp1 externalCall(String func, ExpList args); // Changed List<Exp1> to ExpList
    public abstract Temp RV();
    public abstract String string(Label label, String value);
    public abstract Label badPtr();
    public abstract Label badSub();
    public abstract String tempMap(Temp temp);
    //public abstract List<Instr> codegen(List<Stm> stms);
    public abstract void procEntryExit1(List<Stm> body);
    public abstract void procEntryExit2(List<Instr> body);
    public abstract void procEntryExit3(List<Instr> body);
    public abstract Temp[] registers();
    //public abstract void spill(List<Instr> insns, Temp[] spills);
    public abstract String programTail(); //append to end of target code
}
