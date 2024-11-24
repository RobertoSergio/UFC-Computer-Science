# Explicação da Questão:
Nós vimos na aula 02 que o algoritmo Mergesort requer o uso de uma memória auxiliar do mesmo tamanho da lista que está sendo ordenada.
Mas, isso só vale para a implementação padrão do procedimento de intercalação


Fazendo as coisas de maneira inteligente, é possível eliminar o uso da memória auxiliar.


## Problema da Questão:
Vejamos. A primeira observação é que a primeira metade da lista pode ser ordenada (via mergesort) utilizando a segunda metade (ainda desordenada) como memória auxiliar.


De maneira análoga, o terceiro quarto da lista pode ser ordenado (via mergesort) utilizando o último quarto como memória auxiliar.
E a ideia agora é fazer a intercalação das duas partes ordenadas A e B, utilizando a parte desordenada C como memória auxiliar.


E você conseguir fazer isso, então o problema está basicamente resolvido.


Isto é, em seguida nós ordenamos o sétimos oitavo da lista (via mergesort) utilizando o último oitavo como memória auxiliar e depois repetimos o novo procedimento de intercalação para aumentar a porção ordenada da lista.


Continuando dessa maneira, a lista inteira ficará completamente ordenada.


a) Descreva em detalhe o funcionamento do procedimento de intercalação mencionado acima.


b) Analise o tempo de execução do algoritmo Mergesort quando esse novo procedimento de intercalação é utilizado.


A complexidade do algoritmo é O(n*logn), pois lista é dividida pela metade a cada chamada recursiva, resultando em um total de log n chamadas. Além disso, a intercalação in-place para mesclar as partes ordenadas requer tempo linear O(n) para cada nível de recursão.
