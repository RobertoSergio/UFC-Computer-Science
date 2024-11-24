# Explicação da Questão:
Um gerente atribui uma coleção de tarefas aos seus funcionários, mas ele precisa supervisionar se a coisa está sendo feita direito. O problema é que as tarefas não acontecem todas na mesma hora.


Quer dizer, cada tarefa Tj é realizada durante um intervalo [ij , fj ], onde ij é o instante de início e fj é o instante de final da tarefa.
E para supervisionar a tarefa Tj o gerente deve passar pelo local em algum momento dentro do intervalo [ij , fj ].


A questão é que o gerente, digamos assim, não é uma pessoa muito chegada ao trabalho ...


Quer dizer, ele queria de levantar da cadeira o menor de vezes possível para fazer a ronda.

## Problema da Questão:

O problema então consiste em encontrar uma coleção de instantes de tempo t1,t2, . . . ,tk tal que o intervalo de duração de todas as tarefas contenha ao menos um instante da coleção.


E o objetivo, é claro, consiste em encontrar a menor coleção possível.
Apresente um algoritmo que resolve esse problema.


E analise o tempo de execução do seu algoritmo.
