def encontrar_par_proximo(L, n):
    # Inicializa a menor diferença como infinito e o par encontrado como nulo
    menor_diferenca = float('inf')
    par_encontrado = None

    # Calcula a condição limite para considerar um par
    condicao = (L[0] + L[n - 1]) / (n - 1)

    # Percorre a lista até o penúltimo elemento
    for i in range(len(L) - 1):
        # Calcula a diferença absoluta entre elementos consecutivos
        diferenca = abs(L[i] - L[i + 1])

        # Verifica se a diferença atual é menor do que a menor diferença registrada
        if diferenca < menor_diferenca:
            menor_diferenca = diferenca
            par_encontrado = (L[i], L[i + 1])

            # Verifica se a menor diferença já está abaixo da condição limite
            if menor_diferenca < condicao:
                return par_encontrado, menor_diferenca

    # Retorna um par vazio e 0 se nenhum par atender à condição
    return [], 0

# Exemplo de uso:
L = [0, 3, 5, 6, 9]
n = 5
par, menor_diferenca = encontrar_par_proximo(L, n)
# Imprime o par encontrado e a menor diferença
print(par)
print(menor_diferenca)
