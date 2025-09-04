package br.ufc.compiladores;

import br.ufc.compiladores.parser.MiniJavaParser;
import br.ufc.compiladores.parser.ParseException;
import br.ufc.compiladores.parser.Token;
import br.ufc.compiladores.parser.TokenMgrError;
import br.ufc.compiladores.semant.ClassInfo;
import br.ufc.compiladores.semant.MethodInfo;
import br.ufc.compiladores.semant.Symbol;
import br.ufc.compiladores.semant.SymbolTable;
import br.ufc.compiladores.syntaxtree.Program;
import br.ufc.compiladores.visitor.BuildSymbolTableVisitor;
import br.ufc.compiladores.visitor.PrettyPrintVisitor;
import br.ufc.compiladores.visitor.TypeCheckVisitor;
import br.ufc.compiladores.visitor.IRTreeVisitorImpl;
import br.ufc.compiladores.assem.Instr;
import br.ufc.compiladores.canon.Canon;
import br.ufc.compiladores.frag.Frag;
import br.ufc.compiladores.frag.ProcFrag;
import br.ufc.compiladores.frame.Frame;
import br.ufc.compiladores.mips.MipsFrame;
import br.ufc.compiladores.jouette.Codegen;
import br.ufc.compiladores.tree.Print;
import br.ufc.compiladores.tree.Stm;
import br.ufc.compiladores.tree.StmList;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        try {
            
            // Recebe caminho do arquivo pelo terminal
            byte[] codeBytes = Files.readAllBytes(Paths.get(args[0]));
            String texto = new String(codeBytes, java.nio.charset.StandardCharsets.UTF_8);
            System.out.println(texto);

            // Análise léxica
            System.out.println("Iniciando análise léxica...");
            MiniJavaParser parser = new MiniJavaParser(new ByteArrayInputStream(codeBytes));
            Token token;
            do {
                token = parser.getNextToken();
                System.out.println("<" + MiniJavaParser.tokenImage[token.kind] + ", " + token.image + ">");

            } while (token.kind != 0);
            System.out.println("Análise léxica concluída.");

            System.out.println("Iniciando análise sintática...");
            parser.ReInit(new ByteArrayInputStream(codeBytes));
            Program p = parser.Program();
            System.out.println("Análise sintática concluída com sucesso!");

            // Impressão da árvore (usando o visitor do livro)
            System.out.println("Imprimindo AST:");
            p.accept(new PrettyPrintVisitor());

            // Semântica
            System.out.println("Construindo tabela de símbolos...");
            BuildSymbolTableVisitor builder = new BuildSymbolTableVisitor();
            p.accept(builder);
            SymbolTable table = builder.getSymbolTable();

            // Impressão da tabela de símbolos
            System.out.println("Tabela de símbolos:");
            for (ClassInfo c : table.getClasses()) {
                System.out.println("Classe: " + c.name.getName() + (c.superClass != null ? " extends " + c.superClass.getName() : ""));
                
                for (Symbol field : c.fields.keySet()) {
                    System.out.println("  Campo: " + field.getName() + " : " + c.fields.get(field));
                }

                for (Symbol method : c.methods.keySet()) {
                    MethodInfo m = c.methods.get(method);
                    System.out.println("  Método: " + method.getName() + " : " + (m.returnType != null ? m.returnType : "void"));

                    for (Symbol param : m.parameters.keySet()) {
                        System.out.println("    Parâmetro: " + param.getName() + " : " + m.parameters.get(param));
                    }

                    for (Symbol local : m.locals.keySet()) {
                        System.out.println("    Local: " + local.getName() + " : " + m.locals.get(local));
                    }
                }
            }

            System.out.println("Verificando semântica...");
            TypeCheckVisitor checker = new TypeCheckVisitor(table);
            p.accept(checker);
            System.out.println("Análise semântica concluída com sucesso!");

            // Geração do IR
            System.out.println("Gerando código intermediário (IR)...");

            Frame initialFrame = new MipsFrame(Symbol.symbol("main"), Collections.singletonList(false));

            IRTreeVisitorImpl irVisitor = new IRTreeVisitorImpl(table, initialFrame);
            p.accept(irVisitor); 
            Frag frags = irVisitor.getFrags(); 

            // Imprimir os Frags (debug)
            // while (frag != null) {
            //     if (frag instanceof ProcFrag proc) {
            //         System.out.println("=== Proc: " + proc.frame.name + " ===");
            //         System.out.println("Formals: " + proc.frame.formals);
            //         System.out.println("Body IR:");
            //         new Print(System.out).prStm(proc.body);
            //         System.out.println();
            //     }
            //     frag = frag.getNext();
            // }

            while ((frags = frags.getNext()) != null) {
                if (frags instanceof ProcFrag procFrag) {
                    // 1. Canonização
                    StmList linearized = Canon.linearize(procFrag.body);

                    // 2. Seleção de instrução / Codegen
                    List<Instr> instrs = new LinkedList<>();
                    Codegen cg = new Codegen((MipsFrame) procFrag.frame, instrs.listIterator());
                    for (StmList l = linearized; l != null; l = l.tail) {
                        l.head.accept(cg);
                    }

                    // 3. Prólogo/Epílogo
                    procFrag.frame.procEntryExit2(instrs);
                    procFrag.frame.procEntryExit3(instrs);

                    // // 4. Emissão do assembly MIPS
                    MipsFrame mf = (MipsFrame)procFrag.frame;
                    for (Instr i : instrs) {
                        System.out.println(i.format(mf));
                    }

                    System.out.println(mf.programTail());

                }
            }
            
        } catch (TokenMgrError e) {
            System.out.println("Erro léxico:\n" + e.getMessage());
        } catch (ParseException e) {
            System.out.println("Erro sintático:\n" + e.getMessage());
        } catch (IOException e) {
            System.out.println("Erro de entrada:\n" + e.getMessage());
        }
    }
}