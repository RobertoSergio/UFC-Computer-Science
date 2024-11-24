import numpy as np


def calcular_matriz_bar(A):
    m, n = A.shape
    if m < n:
        A_bar = np.dot(A, A.T)
        transposta = False
    else:
        A_bar = np.dot(A.T, A)
        transposta = True
    return A_bar, transposta


def calcular_valores_singulares(lambdas):
    sigmas = np.sqrt(lambdas)
    return sigmas


def montar_matrizes_usv(A, lambdas, autovetores, transposta):
    sigmas = calcular_valores_singulares(lambdas)

    # Ordenar os valores singulares e seus autovetores correspondentes
    idx = np.argsort(-sigmas)
    sigmas = sigmas[idx]
    autovetores = autovetores[:, idx]

    Sigma = np.diag(sigmas)
    if transposta:
        V = autovetores
        U = np.dot(A, V) / sigmas
    else:
        U = autovetores
        V = np.dot(A.T, U) / sigmas

    return U, Sigma, V


def calcular_posto(sigmas):
    rank = np.sum(sigmas > 1e-9)
    return rank


def verificar_fatoracao(U, Sigma, V, A):
    A_reconstruida = np.dot(U, np.dot(Sigma, V.T))
    return np.allclose(A, A_reconstruida, atol=1e-6)


def metodo_da_potencia_regular(A, v0, eps=1e-9, max_iter=1000):
    """
    Método da Potência Regular para encontrar o autovalor dominante e o autovetor correspondente.
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
