def Mediana_DC2(L1, L2, inicio, fim, n):
    # Caso base: se o índice de início for maior que o índice de fim
    if fim < inicio:
        # Verifica se estamos no lado direito da mediana
        if inicio < n:
            M = L2[n - inicio - 1]
        else:
            # Estamos no lado esquerdo da mediana
            M = L1[inicio - n - 1]
        return M

    # Encontra o índice da partição
    k = particao(L1, L2, inicio, fim, n)

    # Casos recursivos
    if k == n:
        # Encontrou a mediana
        M = L2[k - n]
    elif k > n:
        # Busca na sublista à esquerda da partição
        M = Mediana_DC2(L1, L2, inicio, k - 1, n)
    else:
        # Busca na sublista à direita da partição
        M = Mediana_DC2(L1, L2, k + 1, fim, n)

    return M

def particao(L1, L2, inicio, fim, n):
    # Escolhe o pivot da primeira lista
    pivot = L1[inicio]
    i = inicio + 1
    k = fim

    while i <= k:
        # Casos para comparar elementos das duas listas
        if i < n and k >= n:
            if L1[i] > pivot and L2[k - n] <= pivot:
                # Troca elementos para manter a ordem correta
                L1[i], L2[k - n] = L2[k - n], L1[i]
            if L1[i] <= pivot:
                i += 1
            if k >= n and L2[k - n] > pivot:
                k -= 1
        elif i < n and k < n:
            if L1[i] > pivot and L1[k] <= pivot:
                L1[i], L1[k] = L1[k], L1[i]
            if L1[i] <= pivot:
                i += 1
            if k < n and L1[k] > pivot:
                k -= 1
        elif i >= n and k >= n:
            if L2[i - n] > pivot and L2[k - n] <= pivot:
                L2[i - n], L2[k - n] = L2[k - n], L2[i - n]
            if L2[i - n] <= pivot:
                i += 1
            if L2[k - n] > pivot:
                k -= 1

    # Move o pivot para a posição correta na partição
    if k >= n:
        L1[inicio], L2[k - n] = L2[k - n], L1[inicio]
    elif k < n:
        L1[inicio], L1[k] = L1[k], L1[inicio]

    return k

# Exemplo de uso:
L1 = [1, 4, 5, 8, 9]
L2 = [2, 3, 6, 7, 10]
n = len(L1)
resultado = Mediana_DC2(L1, L2, 0, 2 * n - 2, n)
print(resultado)
