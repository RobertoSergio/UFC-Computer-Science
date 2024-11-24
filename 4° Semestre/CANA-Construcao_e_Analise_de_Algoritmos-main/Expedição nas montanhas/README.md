# Explicação da Questão:
Uma expedição precisa atravessar uma cadeia de montanhas e, para maximizar a sua chance de sucesso, eles decidem utilizar um mapa topogr´afico como guia.
A ideia é que o mapa indica a altitude das diferentes partes do terreno.


De maneira simplificada, nós podemos imaginar que a região é um retãngulo, e que o mapa fornece estimativas aproximadas para a altitude em cada quadradinho.


Quer dizer, nós podemos pensar no mapa como uma matriz A[n, m] de números positivos.


Para simplificar ainda mais a situação, os expedicionários decidiram que só vão considerar
trajetórias que fazem algum progresso a cada passo:

## Problema da Questão:
E o objetivo é minimizar o deslocamento vertical (subidas e descidas) ao longo do caminho.
Por outro lado, a trajetória pode começar em qualquer ponto na parte de baixo do mapa, e pode terminar em qualquer ponto na parte de cima.


a) Apresente um algoritmo de programação dinâmica que encontra uma trajetória para atravessar a cadeia de montanhas, com o menor deslocamente vertical total possível.


b) Estime a complexidade do seu algoritmo.


A complexidade é O(n*m), n e m sendo o tamanho A[n, m] do mapa
