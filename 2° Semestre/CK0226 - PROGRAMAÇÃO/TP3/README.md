## **Universidade Federal do Ceará** | **Departamento de Computação**
### **Disciplina: Programação – CK226** | **Professor: Lincoln Souza Rocha**

**Tarefa de Programação 03**

As pilhas são estruturas de dados do tipo FILO (*first-in last-out*), onde o primeiro elemento a ser inserido, será o último a ser retirado, ou seja, adiciona-se itens no início e remove-se do início. Nessa tarefa de programação, você deverá implementar uma pilha de alunos. Cada aluno é um TAD (Tipo Abstrato de Dados) que possui os seguintes campos: `matricula` (que deve reber um valor inteiro maior ou igual a zero), `nome` (que deve receber uma string de tamanho máximo 50) e `curso` (que deve receber uma string de tamanho máximo 30). A `struct` do TAD `Pilha` deve possuir um campo vetor de ponteiros para o tipo `Aluno` (`pilha_alunos`), onde alunos serão armazenados. Os arquivos de cabeçalho `Aluno.h` e `Pilha.h` descrevem o contrato dos seus respectivos TADs (`Aluno` e `Pilha`) e o aquivo `TestaPilha.c` provê uma bateria de testes para avaliar a sua implementação desses TADs. 

**OBS1** *Os TADs* `Aluno` *e* `Pilha` *devem ser implementados em arquivos separados com os nomes* `Aluno.c` *e* `Pilha.c`.

**OBS2** *Lembre-se que vetores possuem tamanho fixo e, por esse motivo, pode haver a necessidade de realocação de memória caso o número de alunos exceda o tamanho inicial do vetor. Dica! use a função* `realloc()` *para isso.*.

**OBS3**: *Comandos para compilação em separado dos módulos do programa via linha de comando*:
```
$ gcc -c Aluno.c -o Aluno.o
$ gcc -c Pilha.c -o Pilha.o
$ gcc -c TestaPilha.c -o TestaPilha.o
$ gcc -o TestaPilha.bin Aluno.o Pilha.o TestaPilha.o
$ ./TestaPilha.bin
```
