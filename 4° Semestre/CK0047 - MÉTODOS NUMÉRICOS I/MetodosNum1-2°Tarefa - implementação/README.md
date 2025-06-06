# Tarefa 2 de Métodos Numéricos I – Raízes de Equações

## Objetivo:

O objetivo dessa tarefa é fazer alguns exercícios e implementações sobre raízes de equações aplicadas a métodos numéricos (correspondente à Unidade 2 do curso).

## Organização:

A tarefa é relativa somente a essa unidade. Cada aluno deve fazê-la individualmente e colocá-la em um local definido pelo professor. Os códigos devem ser feitos em C++ e Linux. Para alguns alunos, pode-se fazer em outras linguagens ou sistema operacional opcionalmente, desde que liberado pelo professor da cadeira. Os exercícios devem ser feitos em um editor de textos (tipo WORD ou outro) ou então em papel e escaneados. Depois, deve ser gerado um PDF que contenha as questões resolvidas, junto com os códigos desenvolvidos. Os códigos também devem ser entregues, assim como os executáveis. Os executáveis devem incluir todas as bibliotecas usadas. Todos os arquivos, incluindo fontes, executáveis e os exercícios, devem estar juntos em um único arquivo compactado, a ser entregue pelo aluno.

## O que entregar:

Um único arquivo compactado contendo:

a) Um PDF com todos os exercícios resolvidos.

b) Código fonte das implementações desenvolvidas.

c) Executável das implementações desenvolvidas.

**OBS:** Recomenda-se que o executável não tenha nada dinâmico, ou seja, que as LIBs sejam estáticas ou todas as DLLs estejam incluídas na distribuição do arquivo.

## Questões:

### Questão 1:

Em um determinado problema físico, o movimento angular de um pêndulo é regido por uma função dada por \( f(a) = - \left(\frac{e^a}{2}\right) + 2\cos(a) \), onde \( a \) é um ângulo medido em radianos. Considerando \( e = 10^{-4} \) e usando 4 casas decimais, pede-se:

a) Ache um intervalo para uma solução de \( f(a) = 0 \) através de um isolamento analítico.

b) Faça o refinamento para achar o ângulo \( a \) através do método da Bisseção.

c) Faça o refinamento para achar o ângulo \( a \) através do método da Posição Falsa.

d) Implemente os dois métodos e verifique se os resultados estão corretos.

### Questão 2:

Com relação ao problema anterior e usando um número máximo de iterações igual ao número máximo de iterações dado pelo método da Bisseção e 4 casas decimais, pede-se:

a) Ache o ângulo \( a \) pelo método de Newton-Raphson com \( a_0 \) apropriado.

b) Ache o ângulo \( a \) pelo método da Secante com \( a_0 = 0,5 \) e \( a_1 = 1,0 \).

c) Implemente os dois métodos e verifique se os resultados estão corretos.

d) O pêndulo rompe por algum método?

### Questão 3:

Ainda sobre o problema anterior, sabendo-se que o movimento pendular pode ser aproximado pelo polinômio dado por \( f(a) = a^3 - 9a + 3 \), usando 4 casas decimais pede-se:

a) Ache uma aproximação para \( a \) pelo método para Polinômios.

b) Ache uma aproximação para \( a \) pelo método do Ponto Fixo.

c) Implemente os dois métodos e verifique se os resultados estão corretos.

### Questão 4:

Seja a equação \( f(x) = x - x \ln(x) = 0 \). Considerando \( e = 10^{-5} \) e 6 casas decimais, pede-se:

a) Ache uma raiz de \( f(x) \) através do Método de Newton-Raphson.

b) Ache uma raiz de \( f(x) \) através do Método do Ponto-Fixo.

c) Implemente os dois métodos e verifique se os resultados estão corretos.
