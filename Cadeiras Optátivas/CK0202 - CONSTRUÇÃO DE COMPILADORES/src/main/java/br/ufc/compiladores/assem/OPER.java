package br.ufc.compiladores.assem;

import br.ufc.compiladores.temp.TempList;
import br.ufc.compiladores.temp.LabelList;
import br.ufc.compiladores.temp.Temp;

public class OPER extends Instr {
   public TempList dst;   
   public TempList src;
   public Targets jump;

   public OPER(String a, Temp[] d, Temp[] s, LabelList j) {
      assem=a; dst=toTempList(d); src=toTempList(s); jump=new Targets(j);
   }
   public OPER(String a, Temp[] d, Temp[] s) {
      assem=a; dst=toTempList(d); src=toTempList(s); jump=null;
   }

   public TempList use() {return src;}
   public TempList def() {return dst;}
   public Targets jumps() {return jump;}

   private static TempList toTempList(Temp[] temps) {
    TempList list = null;
    for (int i = temps.length - 1; i >= 0; i--) {
        list = new TempList(temps[i], list);
    }
    return list;
}
}
