def intercalar_in_place(V, inicio, meio, fim):
    i = inicio
    j = meio + 1

    # Itera enquanto há elementos em ambas as metades
    while i <= meio and j <= fim:
        # Compara os elementos e realiza a intercalação in-place
        if V[i] <= V[j]:
            i += 1
        else:
            temp = V[j]
            k = j
            # Move os elementos da segunda metade para a posição correta
            while k != i:
                V[k] = V[k - 1]
                k -= 1
            V[i] = temp
            i += 1
            meio += 1
            j += 1

def intercalacao_in_place(V, inicio, fim):
    if inicio < fim:
        meio = (inicio + fim) // 2
        # Chama recursivamente para ordenar as duas metades
        intercalar_in_place(V, inicio, meio, fim)
        intercalacao_in_place(V, inicio, meio)
        intercalacao_in_place(V, meio + 1, fim)
        # Realiza a intercalação final para mesclar as partes ordenadas

# Exemplo de uso:
V = [4, 7, 8, 1, 3, 6, 9, 2, 5]
intercalacao_in_place(V, 0, len(V) - 1)
print("Vetor Intercalado:", V)
