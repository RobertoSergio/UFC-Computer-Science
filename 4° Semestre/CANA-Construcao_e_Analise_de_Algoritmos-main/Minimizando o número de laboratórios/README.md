# Explicação da Questão
Agora imagine que existe um grande número de laboratórios disponíveis no departamento.


E imagine que todas as atividades podem ser alocadas em algum laboratório.
## Problema da Questão 
A tarefa consiste em 2:


→ Alocar as atividades aos laboratórios de modo que o menor número possível de laboratórios seja utilizado
Apresente um algoritmo que resolve esse problema.


Analise o tempo de execução do seu algoritmo.


E se for o caso, argumente que o seu algoritmo encontra uma solução ótima para o problema.

## Resposta
A complexidade será de O(nlogn) , pois cada ordenação tem complexidade O(nlogn) e o código em cima tem dois loops de O(n), ou seja, O(nlogn) + O(nlogn) + O(n) + O(n) = O(nlogn)
