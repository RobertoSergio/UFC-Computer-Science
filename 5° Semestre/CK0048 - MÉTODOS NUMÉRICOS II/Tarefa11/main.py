from algoritmos import potencia_inverso, potencia_com_deslocamento
import numpy as np


def main():
    # Matrizes dadas na tarefa
    A1 = np.array(
        [
            [5, 2, 1],
            [2, 3, 1],
            [1, 1, 2],
        ],
    )
    A2 = np.array(
        [
            [-14, 1, -2],
            [1, -1, 1],
            [-2, 1, -11],
        ],
    )
    A3 = np.array(
        [
            [40, 8, 4, 2, 1],
            [8, 30, 12, 6, 2],
            [4, 12, 20, 1, 2],
            [2, 6, 1, 25, 4],
            [1, 2, 2, 4, 5],
        ]
    )

    # Vetor inicial
    v1 = np.ones(A1.shape[0])

    print("METODO DA POTENCIA INVERSA\n")
    print("--------------------------\n")

    print("Matriz A1:")
    lambda_A1, x_A1 = potencia_inverso(A1, v1)
    print(f"Autovalor: {lambda_A1}")
    print(f"Autovetor: {x_A1}\n")

    print("Matriz A2:")
    lambda_A2, x_A2 = potencia_inverso(A2, v1)
    print(f"Autovalor: {lambda_A2}")
    print(f"Autovetor: {x_A2}\n")

    print("Matriz A3:")
    v3 = np.ones(A3.shape[0])  # vetor inicial para A3 deve ter o tamanho correspondente
    lambda_A3, x_A3 = potencia_inverso(A3, v3)
    print(f"Autovalor: {lambda_A3}")
    print(f"Autovetor: {x_A3}\n")

    print("\n--------------------------\n")
    print("METODO DA POTENCIA COM DESLOCAMENTO\n")
    print("--------------------------\n")

    mu = int(input("Digite o fator de deslocamento: "))

    # Calcular autovalores e autovetores usando o método da potência com deslocamento
    print("Matriz A1:")
    lambda_A1, x_A1 = potencia_com_deslocamento(A1, v1, mu)
    print(f"Autovalor: {lambda_A1}")
    print(f"Autovetor: {x_A1}\n")

    print("Matriz A2:")
    lambda_A2, x_A2 = potencia_com_deslocamento(A2, v1, mu)
    print(f"Autovalor: {lambda_A2}")
    print(f"Autovetor: {x_A2}\n")

    print("Matriz A3:")
    v3 = np.ones(A3.shape[0])  # vetor inicial para A3 deve ter o tamanho correspondente
    lambda_A3, x_A3 = potencia_com_deslocamento(A3, v3, mu)
    print(f"Autovalor: {lambda_A3}")
    print(f"Autovetor: {x_A3}\n")


if __name__ == "__main__":
    main()
