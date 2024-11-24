def maior_salto_v2(lista, n):
    # Inicializa o menor elemento com o primeiro elemento da lista
    menor_elemento = lista[0]
    # Inicializa o maior salto com a diferença entre o segundo e o primeiro elemento
    maior_salto = lista[1] - lista[0]

    # Percorre a lista a partir do segundo elemento até o último
    for i in range(1, n):
        # Obtém o elemento atual da lista
        atual = lista[i]
        # Calcula o salto atual subtraindo o menor elemento do elemento atual
        salto_atual = atual - menor_elemento

        # Verifica se o salto atual é maior que o maior salto registrado até agora
        if salto_atual > maior_salto:
            # Atualiza o maior salto
            maior_salto = salto_atual

        # Verifica se o elemento atual é menor que o menor elemento registrado até agora
        if atual < menor_elemento:
            # Atualiza o menor elemento
            menor_elemento = atual

    # Retorna o maior salto encontrado
    return maior_salto

# main:
L = [4, 10, 0, 7]
n = len(L)
resultado = maior_salto_v2(L, n)
# Imprime o resultado
print(resultado)  # Saída: 7
