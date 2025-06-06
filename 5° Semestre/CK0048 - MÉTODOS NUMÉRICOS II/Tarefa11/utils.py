import numpy as np


def decomposicao_lu(A):
    """
    Realiza a decomposição LU de uma matriz A.

    Parâmetros:
    A : np.array
        Matriz quadrada para ser decomposta.

    Retorna:
    L : np.array
        Matriz triangular inferior.
    U : np.array
        Matriz triangular superior.
    """
    n = A.shape[0]
    L = np.zeros_like(A)
    U = np.zeros_like(A)

    for i in range(n):
        # Matriz U
        for k in range(i, n):
            U[i, k] = A[i, k] - np.sum(L[i, :i] * U[:i, k])

        # Matriz L
        L[i, i] = 1  # Diagonal principal de L é 1
        for k in range(i + 1, n):
            L[k, i] = (A[k, i] - np.sum(L[k, :i] * U[:i, i])) / U[i, i]

    return L, U
