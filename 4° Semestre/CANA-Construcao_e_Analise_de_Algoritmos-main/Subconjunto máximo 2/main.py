def subconjunto_maximo_2(L):
    n = len(L)
    lista_memoria = [0] * n

    # Defina os casos base.
    lista_memoria[0] = max(0, L[0])
    lista_memoria[1] = max(lista_memoria[0], L[1])

    # Preencha a lista_memoria usando a lógica da programação dinâmica.
    for i in range(2, n):
        lista_memoria[i] = max(lista_memoria[i - 1], lista_memoria[i - 2] + L[i])

    # O resultado final será o valor máximo no final da lista_memoria.
    return lista_memoria[n - 1]

# Exemplo de uso:
L = [2, 11, 9, 3, -2, -1, 0]
resultado = subconjunto_maximo_2(L)
print("A maior soma de subconjunto sem elementos consecutivos é:", resultado)
