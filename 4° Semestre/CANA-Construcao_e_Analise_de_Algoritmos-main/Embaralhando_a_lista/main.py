def embaralhar(L, P):
    n = len(L)

    # Itera sobre os elementos de L
    for i in range(n):
        # Verifica se o elemento ainda não foi movido
        if L[i] >= 0:
            # Encontra o destino do elemento na permutação P
            for j in range(n):
                if P[j] == i:
                    destino = j
            origem = i
            # Realiza a troca de elementos entre as posições origem e destino
            troca(L, P, origem, destino)
            # Marca o elemento na posição origem como movido
            L[origem] = -L[origem]

    # Inverte o sinal dos elementos para restaurar seus valores originais
    for i in range(n):
        L[i] = -L[i]

def troca(L, P, i, j):
    # Troca os elementos nas posições i e j em L e atualiza a permutação P
    L[i], L[j] = L[j], L[i]
    P[i], P[j] = P[j], P[i]

# Exemplo de uso:
L = [9, 3, 5, 8, 0, 7, 1, 6, 2, 4]
P = [5, 7, 0, 8, 1, 4, 3, 9, 2, 6]
embaralhar(L, P)
print("Lista embaralhada:", L)  # Exibe a lista após o embaralhamento
print("Permutação utilizada:", P)  # Exibe a permutação utilizada no embaralhamento
