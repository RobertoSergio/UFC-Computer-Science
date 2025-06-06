def Subsequencia_crescente_comum(A, B, m, n):
    # Inicializa uma matriz para armazenar as soluções parciais
    dp = [[0] * (n + 1) for _ in range(m + 1)]

    # Preenche a matriz usando a lógica da programação dinâmica
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if A[i - 1] == B[j - 1]:
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

    # Reconstrói a subsequência comum
    subsequencia = []
    i, j = m, n
    while i > 0 and j > 0:
        if A[i - 1] == B[j - 1]:
            # Adiciona o elemento à subsequência se for menor que o último elemento
            if len(subsequencia) == 0 or A[i - 1] < subsequencia[-1]:
                subsequencia.append(A[i - 1])
            i -= 1
            j -= 1
        elif dp[i - 1][j] > dp[i][j - 1]:
            i -= 1
        else:
            j -= 1

    # Inverte a subsequência para obter a ordem correta
    subsequencia.reverse()

    return subsequencia

# Exemplo de uso
A = [8, 3, 4, 14, 6, 11, 5, 9, 12]
B = [5, 3, 6, 8, 11, 9, 15, 12, 14]
m, n = len(A), len(B)
resultados = Subsequencia_crescente_comum(A, B, m, n)
print(resultados)
