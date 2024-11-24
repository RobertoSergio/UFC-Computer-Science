import numpy as np
from utils import decomposicao_lu


def potencia_inverso(A, v0, epsilon=1e-9, max_iter=1000):
    """
    Implementação do Método da Potência Inversa seguindo o Algoritmo 2.1b.

    Parâmetros:
    A : np.array
        Matriz quadrada para a qual o autovalor inverso será encontrado.
    v0 : np.array
        Vetor inicial (chute inicial).
    epsilon : float
        Tolerância para a convergência.
    max_iter : int
        Número máximo de iterações.

    Retorna:
    lambda_inverso : float
        Autovalor inverso estimado.
    x_inverso : np.array
        Autovetor correspondente ao autovalor inverso.
    """

    # Passo 2: Calcular a decomposição LU de A
    L, U = decomposicao_lu(A)

    # Passo 3: Inicializar o autovalor, λ_novo = 0 (já inicializado como lambda_antigo)
    lambda_novo = 0.0

    # Passo 4: Copiar o vetor v0 para (v4)_antigo
    v_novo = v0

    for _ in range(max_iter):
        # Passo 5: Copiar λ_novo para λ_antigo
        lambda_antigo = lambda_novo

        # Passo 6: Copiar (v)_novo para (v)_antigo
        v_velho = v_novo

        # Passo 7: Normalizar (v)_velho
        x_velho = v_velho / np.linalg.norm(v_velho)

        # Passo 8: Calcular (v)_novo não normalizado
        # v_novo = np.linalg.inv(A).dot(x_velho)
        y = np.linalg.solve(L, x_velho)
        v_novo = np.linalg.solve(U, y)

        # Passo 9: Calcular a nova estimativa de λ
        lambda_novo = np.dot(x_velho.T, v_novo)

        # Passo 10: Verificar convergência de λ
        if np.abs((lambda_novo - lambda_antigo) / lambda_novo) < epsilon:
            break

    # Passo 11: Calcular λ_final: λ_final = 1 / λ_novo
    lambda_inverso = 1.0 / lambda_novo

    # Passo 12: Copiar (x)_novo em x_final
    x_n = x_velho

    # Passo 13: Retornar resposta
    return lambda_inverso, x_n


def potencia_com_deslocamento(A, v1, mu, epsilon=1e-9, max_iter=1000):
    """
    Implementação do Método da Potência com Deslocamento.

    Parâmetros:
    A : np.array
        Matriz quadrada para a qual o autovalor deslocado será encontrado.
    v1 : np.array
        Vetor inicial (chute inicial).
    mu : float
        Valor de deslocamento.
    epsilon : float
        Tolerância para a convergência.
    max_iter : int
        Número máximo de iterações.

    Retorna:
    lambda_deslocado : float
        Autovalor estimado próximo a mu.
    x_deslocado : np.array
        Autovetor correspondente ao autovalor deslocado.
    """
    # Passo 1: Calcular a matriz deslocada Ȧ = A - mu * I
    n = A.shape[0]
    I = np.eye(n)
    A_tilde = A - mu * I

    # Passo 2: Aplicar o Método da Potência Inversa na matriz deslocada
    lambda_deslocada, x_deslocada = potencia_inverso(A_tilde, v1, epsilon, max_iter)

    # Passo 3: Calcular o autovalor deslocado λi = λa + mu
    lambda_deslocado = lambda_deslocada + mu

    # Passo 4: Copiar o autovetor
    x_deslocado = x_deslocada

    # Passo 5: Retornar resultado
    return lambda_deslocado, x_deslocado
