def maior_subfaixa(L):
    # Inicializa as variáveis para a subfaixa atual e a subfaixa global
    M = M_global = L[0]
    inicio = inicio_subfaixa = fim_subfaixa = 0
    subfaixa = []

    # Percorre a lista a partir do segundo elemento
    for i in range(1, len(L)):
        # Verifica se iniciar uma nova subfaixa é mais vantajoso do que continuar a subfaixa atual
        if L[i] > M + L[i]:
            M = L[i]
            inicio = i
        else:
            M += L[i]

        # Atualiza a subfaixa global se a subfaixa atual for maior
        if M > M_global:
            M_global = M
            inicio_subfaixa = inicio
            fim_subfaixa = i

    # Constroi a lista representando a subfaixa global
    for i in range(inicio_subfaixa, fim_subfaixa + 1):
        subfaixa.append(L[i])

    return subfaixa

# Exemplo de uso:
L = [7, -3, 3, -4, 12, -11, 6]
subfaixa = maior_subfaixa(L)
# Imprime a subfaixa global encontrada
print(subfaixa)
