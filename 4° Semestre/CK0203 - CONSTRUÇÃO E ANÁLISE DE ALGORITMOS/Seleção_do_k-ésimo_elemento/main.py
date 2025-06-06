def particao(V, left, right):
    # Escolhe o primeiro elemento como pivô
    pivot = V[left]  
    j = left + 1
    k = right
    
    # loop para encontrar a posição certa do pivô
    while j <= k:
        if V[j] > pivot and V[k] <= pivot:
            V[j], V[k] = V[k], V[j]

        if V[j] <= pivot:
            j += 1
        if V[k] > pivot:
            k -= 1

    # Coloca o pivô na posição correta
    V[left], V[k] = V[k], V[left]
    return k

def selecao_kesimo_menor(V, left, right, k):
    # Caso base: quando a sublista tem apenas um elemento
    if left == right:
        return V[left]

    # Encontra o índice do pivô após particionar a lista
    pivot_index = particao(V, left, right)

    # Verifica se o índice do pivô é igual à posição desejada
    if pivot_index == k:
        return V[pivot_index]
    # Se a posição desejada está à direita do pivô, busca na sublista à direita
    elif pivot_index < k:
        return selecao_kesimo_menor(V, pivot_index + 1, right, k)
    # Se a posição desejada está à esquerda do pivô, busca na sublista à esquerda
    else:
        return selecao_kesimo_menor(V, left, pivot_index - 1, k)

# Main
V = [8, 4, 2, 7, 5, 6, 11, 14, 23, 24, 31, 34]
k = 4  # Encontrar o 3º menor elemento
resultado = selecao_kesimo_menor(V, 0, len(V) - 1, k - 1)  # Ajustar para índice base 0
print("O", k, "º menor elemento é:", resultado)
