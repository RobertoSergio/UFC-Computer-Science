# A função particao realiza a partição do array V utilizando dois pivôs, pivot e pivot2
def particao(V, pivot, pivot2):
    # Inicialização dos índices j e k para percorrer o array V
    j = 1
    k = len(V) - 1

    # Loop para rearranjar elementos menores e maiores que o pivô
    while j <= k:
        if V[j] > pivot and V[k] <= pivot:
            V[j], V[k] = V[k], V[j]

        if V[j] <= pivot:
            j += 1
        if V[k] > pivot:
            k -= 1

    # Coloca o pivô na posição correta
    V[0], V[k] = V[k], V[0]
    p1 = k
    j = k
    k = len(V) - 1

    # Segundo Loop para rearranjar elementos usando o segundo pivô (pivot2)
    while j <= k:
        if V[j] > pivot2 and V[k] <= pivot2:
            V[j], V[k] = V[k], V[j]

        if V[j] <= pivot2:
            j += 1
        if V[k] > pivot2:
            k -= 1

    # Coloca o segundo pivô na posição correta
    V[p1 + 1], V[k] = V[k], V[p1 + 1]
    return p1, k


# A função tres_particao divide o array V em três partes utilizando dois pivôs, p1 e p2
def tres_particao(V, l1, l2, l3):
    # Inicialização do índice i
    i = 0

    # Garante que os dois primeiros elementos estão ordenados
    if V[0] > V[1]:
        V[1], V[0] = V[0], V[1]
    p1 = V[0]
    p2 = V[1]

    # Chama a função de partição para obter as posições dos pivôs
    pos_pivot1, pos_pivot2 = particao(V, p1, p2)

    # Preenche as três listas com base nas posições dos pivôs
    while i < pos_pivot1:
        l1.append(V[i])
        i += 1
    j = pos_pivot1
    while j < pos_pivot2:
        l2.append(V[j])
        j += 1
    k = pos_pivot2
    while k < len(V):
        l3.append(V[k])
        k += 1
    return pos_pivot1, pos_pivot2


# Exemplo de uso
lista_desordenada = [23, 15, 37, 10, 14, 33, 13, 29, 16, 22, 24, 8]
lista1 = []
lista2 = []
lista3 = []

# Imprime a lista original
print("Original:", lista_desordenada)

# Chama a função de três partições e imprime os resultados
pos_pivot1, pos_pivot2 = tres_particao(lista_desordenada, lista1, lista2, lista3)
print("Ordenada:", lista_desordenada)
print("Menor que P1:", lista1)
print("Entre P1 e P2:", lista2)
print("Maior que P2:", lista3)
