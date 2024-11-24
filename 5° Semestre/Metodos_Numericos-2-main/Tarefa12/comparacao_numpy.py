import numpy as np
from scipy.linalg import hessenberg

# Matriz A original
A = np.array(
    [
        [40, 8, 4, 2, 1],
        [8, 30, 12, 6, 2],
        [4, 12, 20, 1, 2],
        [2, 6, 1, 25, 4],
        [1, 2, 2, 4, 5],
    ]
)

# Calculando a matriz tridiagonal e a matriz de acumulação usando scipy
A_tridiag, H = hessenberg(A, calc_q=True)

# Exibindo os resultados
print("Matriz Tridiagonal A' usando SciPy:")
print(A_tridiag)
print("\nMatriz Acumulada H usando SciPy:")
print(H)
