def particao(L, inicio, fim, pivot):
    # Move o elemento pivot para a posição inicial
    L[inicio], L[pivot] = L[pivot], L[inicio]
    pivot = L[inicio]
    
    # Inicializa os índices i e k
    i = inicio + 1
    k = fim
    
    # Executa a partição
    while i <= k:
        # Troca os elementos se necessário
        if L[i] > pivot and L[k] <= pivot:
            L[i], L[k] = L[k], L[i]
        
        # Incrementa i se o elemento em L[i] é menor ou igual ao pivot
        if L[i] <= pivot:
            i += 1
        
        # Decrementa k se o elemento em L[k] é maior que o pivot
        if L[k] > pivot:
            k -= 1
    
    # Move o pivot para a posição correta na partição
    L[inicio], L[k] = L[k], L[inicio]
    return k


def encontrar_terciana(L, inicio, fim):
    # Caso base: se o intervalo tem apenas um elemento, retorna esse elemento
    if inicio == fim:
        return L[inicio]

    # Calcula o índice do pivot para a terciana
    terci = inicio + (fim - inicio) // 3
    
    # Obtém o índice após particionar a lista
    pivot_index = particao(L, inicio, fim, terci)
    
    # Verifica se o pivot está na posição correta para a terciana
    if pivot_index == (len(L) // 3):
        return L[pivot_index]
    elif pivot_index > (len(L) // 3):
        # Se o pivot está à direita da terciana, busca na sublista à esquerda
        return encontrar_terciana(L, inicio, pivot_index - 1)
    else:
        # Se o pivot está à esquerda da terciana, busca na sublista à direita
        return encontrar_terciana(L, pivot_index + 1, fim)


# Exemplo de uso:
L = [9, 3, 11, 7, 1, 6, 2, 8, 5]
n = len(L)
resultado = encontrar_terciana(L, 0, n - 1)
print(resultado)
