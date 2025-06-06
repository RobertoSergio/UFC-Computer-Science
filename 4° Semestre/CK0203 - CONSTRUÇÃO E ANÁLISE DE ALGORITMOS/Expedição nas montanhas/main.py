def Vertical_minimo(A):
    n = len(A)
    m = len(A[0])

    # Criação de uma lista de memória
    lista_memoria = [[float('inf')] * m for _ in range(n)]

    # Inicializa a primeira linha da lista_memoria com os valores da primeira linha da matriz A
    for j in range(m):
        lista_memoria[0][j] = A[0][j]

    # Preenche a lista_memoria usando programação dinâmica para calcular os menores deslocamentos verticais
    for i in range(1, n):
        for j in range(m):
            # Itera sobre os possíveis deslocamentos na linha anterior
            for k in range(max(0, j - 1), min(m, j + 2)):
                # Atualiza o valor mínimo considerando o deslocamento atual
                lista_memoria[i][j] = min(lista_memoria[i][j], lista_memoria[i - 1][k] + A[i][j])

    # Encontra o valor mínimo na última linha da lista_memoria
    Min = min(lista_memoria[-1])

    return Min

# Exemplo de uso:
mapa = [
    [4, 3, 2],
    [2, 3, 5],
    [4, 1, 1]
]

# Chama a função e imprime o resultado
resultado = Vertical_minimo(mapa)
print("Menor deslocamento vertical total:", resultado)
