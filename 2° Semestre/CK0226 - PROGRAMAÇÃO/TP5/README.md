## **Universidade Federal do Ceará** | **Departamento de Computação**
### **Disciplina: Programação – CK226** | **Professor: Lincoln Souza Rocha**

**Tarefa de Programação 05**

Uma árvore binária é uma estrutura de dados caracterizada por (i) não ter elemento algum (árvore vazia); ou (ii) ter um elemento distinto, denominado raiz, com dois ponteiros para duas estruturas diferentes, denominadas sub-árvore esquerda e sub-árvore direita. Podemos implementar uma árvore binária de busca como um TAD, chamado `ABB` (*Árvore Binária de Busca*). A `struct` do TAD `ABB` que define o tipo `No` (`typedef struct node No`) deve possui os seguintes campos: `chave` (inteiro), `conteudo` (um caractere), `esq` (um ponteiro para o tipo `No`) e `dir` (um ponteiro para o tipo `No`). O arquivo de cabeçalho `ABB.h` descreve o contrato do TAD `ABB` e o aquivo `TestaABB.c` provê uma bateria de testes para avaliar a sua implementação. O arquivo `ABB.c` deve ser preenchido com a sua implementação do TAD `ABB`.

**OBS**: *Comandos para compilação em separado dos módulos do programa via linha de comando*:
```
$ gcc -c ABB.c -o ABB.o
$ gcc -c TestaABB.c -o TestaABB.o
$ gcc -o TestaABB.bin ABB.o TestaABB.o
$ ./TestaABB.bin
```
