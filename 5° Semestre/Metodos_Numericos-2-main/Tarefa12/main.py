from algoritmos import (
    metodo_de_householder,
    metodo_da_potencia_regular,
    metodo_qr,
    verificar_autovetores,
)
import numpy as np


if __name__ == "__main__":
    A = np.array(
        [
            [40, 8, 4, 2, 1],
            [8, 30, 12, 6, 2],
            [4, 12, 20, 1, 2],
            [2, 6, 1, 25, 4],
            [1, 2, 2, 4, 5],
        ]
    )
    print("\n-------------------------------------\n")

    print("ATIVIDADE - AULA 20")
    print("\n-------------------------------------\n")

    A_tridiag, H_acumulada = metodo_de_householder(A)

    # Item 1
    print("1)")
    print("Matriz Tridiagonal A':")
    print(A_tridiag)
    print("\nMatriz Acumulada H:")
    print(H_acumulada)
    print("\n-------------------------------------\n")

    # Item 3 - Método da Potência Regular
    v0 = np.ones(A_tridiag.shape[0])  # Vetor inicial (chute)
    eps = 1e-9  #
    max_iter = 1000

    lambda_dominante, autovetor_dominante = metodo_da_potencia_regular(
        A_tridiag, v0, eps, max_iter
    )

    print("3)")
    print("Autovalor dominante (lambda):", lambda_dominante)
    print("Autovetor correspondente (v):", autovetor_dominante)
    print("\n-------------------------------------\n")

    # Item 4 - Encontrar os autovetores da matriz A usando H e autovetores de A'
    # Fórmula: x_i = H * v_i
    autovetores_A = np.dot(H_acumulada, autovetor_dominante.reshape(-1, 1))

    print("4)")
    print("Autovetores da matriz A:")
    print(autovetores_A)
    print("\n-------------------------------------\n")

    # Item 5 - Encontrar todos os autovalores da matriz A
    autovalores_A = np.linalg.eigvals(A)

    print("5)")
    print("Autovalores da matriz A:")
    print(autovalores_A)
    print("\n-------------------------------------\n")

    input("Digite qualquer tecla para prosseguir para a atividade da aula 22:  ")

    print("ATIVIDADE - AULA 22")
    print("\n-------------------------------------\n")

    print("1) c) Matriz QR em cada iteracao:")
    P, Lamb, A_diagonal = metodo_qr(A)

    print("\n1) a) Matriz Diagonal A':")
    print(A_diagonal)
    print("\n1) b) Matriz Acumulada P:")
    print(P)
    print("\n1) d) Pares (Autovalor, Autovetor):")
    for i, autovalor in enumerate(Lamb):
        print(f"Autovalor: {autovalor}, Autovetor: {P[:, i]}")

    input("Digite qualquer tecla para prosseguir para o proximo item:  ")

    print("\n-------------------------------------\n")
    print("Item 2)")

    print("\n2) i) Matriz A_nova em cada iteração QR:")

    # Aplicar o método QR na matriz tridiagonal obtida com o método de Householder
    P_final, Lamb, A_diagonal = metodo_qr(A_tridiag)

    print("\n2) ii) Verificar se as colunas de P_final são autovetores de A:")
    autovetores_ok = verificar_autovetores(A, P_final, atol=1e-5)
    print("As colunas de P_final são autovetores de A?", autovetores_ok)

    print("\n2) iii) Verificação após multiplicar por H_acumulada (P = HP):")
    P_novo = np.dot(H_acumulada, P_final)
    print("Nova Matriz P (P = HP):")
    print(P_novo)

    print("\n2) iv) Verificar se as colunas da nova matriz P são autovetores de A:")
    autovetores_ok_novo = verificar_autovetores(A, P_novo, atol=1e-5)
    print("As colunas da nova matriz P são autovetores de A?", autovetores_ok_novo)

    print("\n-------------------------------------\n")
