import numpy as np

MAX_ITER = 1000


def metodo_da_potencia_regular(A, v0, eps=1e-9, max_iter=1000):
    """
    Método da Potência Regular para encontrar o autovalor dominante e o autovetor correspondente.

    Parâmetros:
    A : np.array
        Matriz quadrada para a qual o autovalor dominante será encontrado.
    v0 : np.array
        Vetor inicial (chute inicial).
    eps : float
        Tolerância para a convergência.
    max_iter : int
        Número máximo de iterações.

    Retorna:
    lambda_1 : float
        Autovalor dominante estimado.
    v : np.array
        Autovetor correspondente ao autovalor dominante.
    """
    v = v0
    lambda_antigo = 0.0

    for _ in range(max_iter):
        # Passo 4: Copiar lambda antigo para o novo
        lambda_novo = lambda_antigo

        # Passo 5: Copiar v antigo para v novo (antes de normalizar)
        v_velho = v

        # Passo 6: Normalizar o vetor v_velho
        x1_velho = v_velho / np.linalg.norm(v_velho)

        # Passo 7: Calcular o vetor não normalizado v_novo = A * x1_velho
        v_novo = np.dot(A, x1_velho)

        # Passo 8: Calcular a nova estimativa de lambda
        lambda_novo = np.dot(x1_velho.T, v_novo)

        # Verificar a convergência
        if np.abs((lambda_novo - lambda_antigo) / lambda_novo) < eps:
            break

        # Preparar para a próxima iteração
        lambda_antigo = lambda_novo
        v = v_novo

    return lambda_novo, x1_velho


if __name__ == "__main__":

    A1 = np.array(
        [
            [5, 2, 1],
            [2, 3, 1],
            [1, 1, 2],
        ],
    )

    A2 = np.array(
        [
            [40, 8, 4, 2, 1],
            [8, 30, 12, 6, 2],
            [4, 12, 20, 1, 2],
            [2, 6, 1, 25, 4],
            [1, 2, 2, 4, 5],
        ]
    )

    print("METODO DA POTENCIA REGULAR")
    print("--------------------------\n")
    print("Matrizes disponíveis:\n")
    print("Matriz [1]: \n", A1, "\n")
    print("Matriz [2]: \n", A2, "\n")

    while True:
        escolha = int(
            input("Digite 1 para escolher a matriz 1, e 2 para a segunda matriz: ")
        )

        if escolha != 1 and escolha != 2:
            print("Escolha inválida")
            continue

        break

    # eps = float(input("Digite a tolerancia para convergencia: "))

    matriz_escolhida = A1 if escolha == 1 else A2

    # Vetor inicial arbitrário (chute inicial)
    v0 = np.ones(matriz_escolhida.shape[0])

    # Resolvendo para A1
    lambda_A, v_A = metodo_da_potencia_regular(
        A=matriz_escolhida,
        v0=v0,
        # eps=eps,
        max_iter=MAX_ITER,
    )

    print("-------------------------\n")

    print(f"Matriz A1:")
    print(f"Autovalor dominante: {lambda_A}")
    print(f"Autovetor correspondente: {v_A}")
