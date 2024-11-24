# Explicação da Questão:
Note que um heap pode ser decomposto em dois heaps menores mais um elemento onde o elemento isolado é V[1], o heap H1 consiste no elemento V[2] e todos os seus desecendentes, e o heap H2 consiste no elemento V[3] e todos os seus desecendentes.


Essa observação nos dá uma estratégia alternativa para construir o heap:
- construa o heap H1
- construa o heap H2
- coloque o elemento em V[1] na sua posição correta (propagando ele para baixo)

## Problema da Questão:
A ideia, é claro, é aplicar essa estratégia recursivamente na construção dos heaps H1 e H2.


a) Apresente o pseudo-código de um algoritmo recursivo que constrói um heapMax como indicado acima.


b) Analise o tempo de execução do seu algoritmo


A complexidade do algoritmo é o(n^2)
