# Trabalho de Métodos Numéricos I - Raízes de Equações

## Objetivos:

O objetivo desse trabalho é implementar os métodos numéricos estudados para encontrar raízes de equações. Além disso, pretende-se resolver vários problemas com os métodos numéricos a serem implementados.

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

Um fenômeno da natureza é regido pela função \( f(d) = a \cdot e^d - 4 \cdot d^2 \), onde \( a \) são amplitudes dadas devido à oscilação encontrada em cada fenômeno considerado e \( d \) é o deslocamento encontrado em cada fenômeno considerado, variando com o valor de \( a \). Caso esse deslocamento passe de 0,7 cm, esse fenômeno amplifica, causando sérios danos e um problema gigantesco. O método de Newton modificado é tal que a função de iteração \( j(x) \) é dada por \( j(x) = x - \frac{f(x)}{f'(x_0)} \), onde \( x_0 \) é uma aproximação inicial e é tal que \( f'(x_0) \neq 0 \).

Desenvolva um sistema para calcular o valor do deslocamento \( d \) que deve atender a todos os requisitos abaixo:

a) Implementar algoritmo para calcular \( d \) pelo método da Newton-Raphson.

b) Implementar algoritmo para calcular \( d \) pelo método de Newton modificado.

c) Implementar algoritmo para calcular \( d \) pelo método da Secante tradicional.

d) Testar os resultados para \( d \) usando como padrão \( a = 1 \), \( d_0 = 0,5 \) e \( \epsilon = 10^{-4} \).

e) Fornecer um quadro resposta, com \( d \) calculado para cada método dado.

f) Fornecer um quadro comparativo, com todos os dados para cada método.

g) Analisar o efeito da variação do valor de \( a \) para cada método considerado.

**Dados de entrada:** \( n \) (número de valores de \( a \)), \( a \) (para cada \( n \)) e \( \epsilon \) (precisão).

**Dados de saída:** quadros resposta (com \( d \) e erro para cada \( a \) e método) e comparativo.
