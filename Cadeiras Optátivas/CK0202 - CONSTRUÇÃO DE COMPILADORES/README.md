# Compilador – MiniJava

## Progresso do Projeto

- **Parser** (completo)  
  – Gerado com JavaCC a partir de `MiniJava.jj`. Scanner e parser funcionam sem restrições.

- **Pretty-Print AST** (completo)  
  – Visitor que imprime a árvore sintática.

- **Tabela de Símbolos** (completo)  
  – Constrói `ClassInfo` e `MethodInfo` para campos, parâmetros e variáveis locais.

- **Type Checker** (completo)  
  – Verifica tipos primitivos, chamadas de método, herança simples.

- **Geração de IR** (completo)  
  – Visitor traduz AST para IR canônico (`SEQ`, `ESEQ`, `MOVE`, `CALL`, etc.).

- **Canonização (IR→StmList)** (completo)  
  – Remove `SEQ`/`ESEQ`, lineariza chamadas e expressões.

- **Seleção de Instruções (Codegen MIPS)** (completo)  
  – Emite MIPS formatado usando `Instr.format(TempMap)`.

## Como Compilar (sem IDE)

1. **Gerar o parser** (já feito)

```sh
java -cp "/caminho/para/javacc.jar" javacc MiniJava.jj
mv parser/*.java ../java/br/ufc/compiladores/parser/
```

2. **Compilar tudo**

```bat
cd src\main\java
```

E depois execute:

```bat
for /R %f in (*.java) do javac -d ..\..\..\target\classes "%f"
```

```bat
cd ..\..\..\
```

## Executar testes:

```sh
java -cp target/classes br.ufc.compiladores.Main src/test/java/BinarySearch.java
java -cp target/classes br.ufc.compiladores.Main src/test/java/BinaryTree.java
java -cp target/classes br.ufc.compiladores.Main src/test/java/BubbleSort.java
java -cp target/classes br.ufc.compiladores.Main src/test/java/Factorial.java
java -cp target/classes br.ufc.compiladores.Main src/test/java/LinearSearch.java
java -cp target/classes br.ufc.compiladores.Main src/test/java/LinkedList.java
java -cp target/classes br.ufc.compiladores.Main src/test/java/QuickSort.java
java -cp target/classes br.ufc.compiladores.Main src/test/java/TreeVisitor.java
```
