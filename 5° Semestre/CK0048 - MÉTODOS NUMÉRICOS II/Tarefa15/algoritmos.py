import numpy as np


def solucao_exata_pvc1(x):
    """
    Solução exata do PVC1.
    """
    return (np.exp(-x) - np.exp(x)) / (np.exp(-1) - np.exp(1))


def metodo_diferencas_finitas_pvc1(N):
    """
    Resolve o PVC1 usando o método das diferenças finitas com N divisões.
    """

    # Passo 1 - Divisão do domínio em N partes iguais
    delta_x = 1.0 / N
    borda = 1 / (delta_x**2)
    centro = -(2 / delta_x**2 + 1)

    A = np.zeros((N - 1, N - 1))
    b = np.zeros(N - 1)

    # Preencher a matriz A e o vetor b
    for i in range(N - 1):
        # Coeficiente da variável na posição X_i-1
        if i > 0:
            A[i, i - 1] = borda

        # Coeficiente da variável na posição X_i
        A[i, i] = centro

        # Coeficiente da variável na posição X_i-1
        if i < N - 2:
            A[i, i + 1] = borda

    # Condição de contorno y(1) = 1
    # Passa o a "borda" para o outro lado da equação
    b[-1] = -borda

    # Resolver o sistema A * y = b
    y_aprox = np.linalg.solve(A, b)

    # Adicionar as condições de contorno
    y_aprox = np.concatenate(([0], y_aprox, [1]))

    return y_aprox


def calcular_erros_pvc1(y_aprox, N):
    """
    Calcula os erros relativos entre a solução aproximada e a exata do PVC1.
    """

    delta_x = 1.0 / N
    pontos = [i * delta_x for i in range(1, N)]  # Gerar pontos internos

    y_exato = np.zeros(N - 1)
    for i in range(N - 1):
        x = pontos[i]
        y_exato[i] = solucao_exata_pvc1(x)

    erros_relativos = np.zeros(N - 1)
    for i in range(N - 1):
        erros_relativos[i] = np.abs(
            (y_aprox[i + 1] - y_exato[i]) / y_exato[i],
        )

    return pontos, y_exato, erros_relativos


def f_pvc2(x, y):
    """
    Função f(x, y) para o PVC2.
    """
    return 4


def indice(i, j, N):
    return i * N + j


def resolver_pvc2(N):
    delta_x = 1.0 / (N)
    delta_y = 1.0 / (N)
    borda_x = 1 / (delta_x**2)
    borda_y = 1 / (delta_y**2)
    centro = -2 * (borda_x + borda_y)

    tamanho = (N - 1) * (N - 1)
    A = np.zeros((tamanho, tamanho))
    b = np.zeros(tamanho)

    # Preencher a matriz A e o vetor b
    for i in range(N - 1):
        for j in range(N - 1):
            idx = indice(i, j, N - 1)
            if i > 0:
                A[idx, indice(i - 1, j, N - 1)] = borda_x
            if i < N - 2:
                A[idx, indice(i + 1, j, N - 1)] = borda_x
            if j > 0:
                A[idx, indice(i, j - 1, N - 1)] = borda_y
            if j < N - 2:
                A[idx, indice(i, j + 1, N - 1)] = borda_y
            A[idx, idx] = centro

            b[idx] = f_pvc2((i + 1) * delta_x, (j + 1) * delta_y)

    # Resolver o sistema A * u = b
    u_aprox = np.linalg.solve(A, b)

    return u_aprox
