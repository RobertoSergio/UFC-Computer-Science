import numpy as np


def resolver_metodo_da_potencia_regular_com_numpy():
    """
    Esta função resolve o problema dos autovalores e autovetores dominantes de duas matrizes
    (A1 e A2) usando o método da potência regular com o auxílio da função numpy.linalg.eig.
    Ela calcula e imprime os autovalores dominantes e os autovetores correspondentes para as duas matrizes.
    """

    A1 = np.array([[5, 2, 1], [2, 3, 1], [1, 1, 2]])

    A2 = np.array(
        [
            [40, 8, 4, 2, 1],
            [8, 30, 12, 6, 2],
            [4, 12, 20, 1, 2],
            [2, 6, 1, 25, 4],
            [1, 2, 2, 4, 5],
        ]
    )

    # Utiliza numpy para calcular os autovalores e autovetores
    eigenvalues_A1, eigenvectors_A1 = np.linalg.eig(A1)
    eigenvalues_A2, eigenvectors_A2 = np.linalg.eig(A2)

    dominant_eigenvalue_A1 = np.max(eigenvalues_A1)
    dominant_eigenvector_A1 = eigenvectors_A1[:, np.argmax(eigenvalues_A1)]

    dominant_eigenvalue_A2 = np.max(eigenvalues_A2)
    dominant_eigenvector_A2 = eigenvectors_A2[:, np.argmax(eigenvalues_A2)]

    print(f"Matriz A1:")
    print(f"Autovalor dominante: {dominant_eigenvalue_A1}")
    print(f"Autovetor correspondente: {dominant_eigenvector_A1}")

    print(f"\nMatriz A2:")
    print(f"Autovalor dominante: {dominant_eigenvalue_A2}")
    print(f"Autovetor correspondente: {dominant_eigenvector_A2}")


resolver_metodo_da_potencia_regular_com_numpy()
