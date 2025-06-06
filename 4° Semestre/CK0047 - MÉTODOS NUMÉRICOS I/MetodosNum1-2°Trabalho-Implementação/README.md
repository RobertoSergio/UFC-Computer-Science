# Trabalho de Métodos Numéricos I - Sistemas de Equações

## Objetivos:

O objetivo desse trabalho é implementar os métodos numéricos estudados para encontrar sistemas de equações. Além disso, pretende-se resolver vários problemas com os métodos numéricos a serem implementados.

## Organização:

Todas as equipes foram definidas em sala pelos alunos. O trabalho deve ser feito somente em C++ (alternativamente em C) e em Linux. Opcionalmente, pode-se fazer em outra linguagem e sistema operacional desde que autorizado pelo professor, mediante justificativa da equipe. Os trabalhos devem ser apresentados em sala de aula em datas a serem definidas pelo professor. A ordem das apresentações, bem como o tema de cada equipe, será definida por sorteio e cada equipe terá 15 minutos de tempo para apresentação com mais 5 minutos para perguntas do professor e dos colegas. Os membros das equipes que faltarem ao dia da apresentação automaticamente tiram 0 nos pontos relativos à sua apresentação.

## O que entregar:

Um único arquivo compactado contendo:

a) Apresentação (3,0 pontos) – obrigatória.

b) Código fonte (3,0 pontos) – obrigatório.

c) Executável (4,0 pontos) – obrigatório.

d) Documentação (0,0 pontos) – opcional.

**OBS1:** A apresentação deve conter (no mínimo):

- Introdução.
- Metodologia.
- Exemplos.
- Conclusão.

**OBS2:** Recomenda-se que o executável não tenha nada dinâmico, ou seja, que as LIBs sejam estáticas ou todas as DLLs estejam incluídas na distribuição do programa.

## Tema:

Em um fenômeno da natureza os deslocamentos \( d_1, d_2,..., d_n \) encontrados são dados pela solução do sistema de equações lineares \( Ad = b \), onde \( A \) é a matriz das propriedades, \( d \) é o vetor das incógnitas e \( b \) é o vetor dos termos independentes (vetor constante). Caso um desses deslocamentos passe de 0,4 cm, em módulo, podem ocorrer sérios danos e um problema gigantesco. Uma das soluções possíveis para achar o vetor \( d \) é através da inversa de \( A \) (\( d = A^{-1} b \)). Se \( A \) é uma matriz \( n \times n \) que possui como inversa uma matriz \( A^{-1} \) então \( A A^{-1} = I \), onde \( I \) é a matriz Identidade, e uma maneira de se achar \( A^{-1} \) é achar-se as colunas de \( A^{-1} \) uma por vez, através de \( A(A^{-1})_1 = \{1 0 ... 0\}^T \), \( A(A^{-1})_2 = \{0 1 ... 0\}^T \) ... \( A(A^{-1})_n = \{0 0 ... 1\}^T \), onde \( (A^{-1})_1 \), \( (A^{-1})_2 \) ... \( (A^{-1})_n \) são as \( n \) colunas de \( A^{-1} \).

Desenvolva um sistema para calcular deslocamentos \( d \) dessas partes com os requisitos abaixo:

a) Implementar algoritmo para calcular \( A^{-1} \) e depois \( \{d\} \) pelo método de Gauss-Jacobi. 

b) Implementar algoritmo para calcular \( A^{-1} \) e depois \( \{d\} \) pelo método de Gauss-Seidel. 

c) Calibrar o sistema feito usando como padrão matriz \([A]\) e vetor \({b}\) dados abaixo.

d) Fornecer um quadro resposta para cada método, variando os valores de \([A]\) e de \({b}\).

e) Analisar o que vai acontecer nesse fenômeno, para esse sistema mencionado abaixo.

**Dados de entrada:** \( n \) (número de deslocamentos), termos de \([A]\) \( n \times n \) e de \({b}\) \( n \times 1 \) e \( \epsilon \) (precisão).

**Dados de saída:** \( A^{-1} \) e os termos de \({d}\) \( n \times 1 \) que representam os \( n \) deslocamentos \( d_1, d_2,..., dn \)
