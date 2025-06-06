# Explicação da Questão:
Considere uma operação de multiplicação envolvendo os termos a, b, c, definida pela seguinte matriz


| Matriz      | a | b | c |
|-------------|---------|---------|---------|
| a    | b       | b       | a       |
| b    | c       | b       | a       |
| c    | a       | c       | c       |

  
Quer dizer, a · b = b, b · a = c, e assim por diante.


Note que a multiplicação definida por essa matriz não é comutativa nem associativa.


Isso significa que, ao trocar a ordem dos termos em uma expressão, ou a posição dos parênteses, nós podemos mudar o resultado da expressão.


Por exemplo,


((b(bb))(ba))c = a e (b(b(bb)))(ac) = c

## Problema da Questão: 

O nosso problema consiste em, dada uma sequência de multiplicações de termos a, b, c, determinar se existe alguma maneira de colocar parênteses nessa expressão de modo que o seu resultado seja igual a a.


Apresente um algoritmo de programa¸c˜ao dinˆamica para esse problema, e estime a sua complexidade.


Complexidade é O(n^2)
