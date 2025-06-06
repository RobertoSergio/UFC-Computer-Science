from algoritmo import (
    calcular_matriz_bar,
    calcular_posto,
    calcular_valores_singulares,
    montar_matrizes_usv,
    metodo_da_potencia_regular,
    verificar_fatoracao,
)
import numpy as np


def main():
    # 1) Ler o número de linhas (m) e o número de colunas (n) de uma matriz arbitrária
    m = int(input("Digite o número de linhas (m): "))
    n = int(input("Digite o número de colunas (n): "))

    # 2) Ler a matriz A mxn
    A = []
    print(f"Digite os elementos da matriz A ({m}x{n}). Digite uma linha por vez:")
    for i in range(m):
        linha = list(map(float, input().split()))
        A.append(linha)
    A = np.array(A)

    # 3) Calcular a matriz simétrica A_bar
    A_bar, transposta = calcular_matriz_bar(A)

    # 4) Achar os autovalores e autovetores de A_bar
    # TODO: Alterar para utilizar métodos implementados na cadeira
    lambdas, autovetores = np.linalg.eig(A_bar)

    # 5) Calcular os valores singulares sigma_i = sqrt(lambda_i)
    sigmas = calcular_valores_singulares(lambdas)

    # 6) Imprimir o posto da matriz A
    rank = calcular_posto(sigmas)
    print(f"O posto da matriz A é: {rank}")

    # 7) Montar as matrizes U, Sigma e V
    U, Sigma, V = montar_matrizes_usv(A, lambdas, autovetores, transposta)
    print("\nMatriz U:")
    print(U)
    print("\nMatriz Sigma:")
    print(Sigma)
    print("\nMatriz V:")
    print(V)

    # 8) Verificar se U . Sigma . V^T = A
    if verificar_fatoracao(U, Sigma, V, A):
        print("\nA fatoração U . Sigma . V^T é igual à matriz original A.")
    else:
        print("\nA fatoração U . Sigma . V^T não é igual à matriz original A.")


if __name__ == "__main__":
    main()
