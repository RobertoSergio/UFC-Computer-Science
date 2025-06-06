def multABC(operacao, resultado, matriz, lista_memoria):
    n = len(operacao)

    # Mapeie 'a', 'b', 'c' para os índices 0, 1, 2
    index_map = {'a': 0, 'b': 1, 'c': 2}

    # Preenche a diagonal principal da matriz lista_memoria com True para os casos base
    for i in range(n):
        lista_memoria[i][i][index_map[operacao[i]]] = True

    # Preenche a matriz lista_memoria usando programação dinâmica para calcular as possíveis avaliações
    for l in range(2, n + 1):
        for i in range(n - l + 1):
            j = i + l - 1
            for k in range(i, j):
                for x in range(3):
                    for y in range(3):
                        # Verifica se é possível obter o resultado 'res' a partir das subcadeias
                        if lista_memoria[i][k][x] and lista_memoria[k + 1][j][y]:
                            res = matriz[x][y]
                            lista_memoria[i][j][index_map[res]] = True

    # Retorna True se a subcadeia completa pode avaliar para o resultado desejado
    return lista_memoria[0][n - 1][0]

# Exemplo de uso
operacao = "cccccccc"
resultado_desejado = 'a'
matriz_multiplicacao = [['b', 'a', 'a'],
                        ['c', 'b', 'a'],
                        ['a', 'c', 'c']]
n = len(operacao)

# Inicializa a matriz lista_memoria com False para todos os elementos
lista_memoria = [[[False for _ in range(3)] for _ in range(n)] for _ in range(n)]

# Chama a função e imprime o resultado
resultado = multABC(operacao, resultado_desejado, matriz_multiplicacao, lista_memoria)
print(resultado)
