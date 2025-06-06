import numpy as np


def metodo_de_householder(A):
    """
    Aplica o método de Householder para transformar a matriz A em uma matriz tridiagonal.

    Parâmetros:
    A : np.array
        Matriz simétrica a ser transformada.

    Retorna:
    A_tridiag : np.array
        Matriz tridiagonal resultante.
    H_acumulada : np.array
        Matriz acumulada das transformações de Householder.
    """
    n = A.shape[0]
    H_acumulada = np.eye(n)  # Inicia a matriz acumulada como identidade
    A_tridiag = A.copy()  # Cria uma cópia da matriz A para ser modificada

    for i in range(n - 2):
        # Inicializar vetores
        w = np.zeros(n)  # Vetor nulo com n elementos
        w_linha = np.zeros(n)  # Vetor nulo com n elementos

        # Copiar os elementos abaixo da diagonal da coluna i da matriz A_tridiag
        # para as respectivas posições no vetor w, isto é, da posição i+1 até o final
        w[i + 1 : n] = A_tridiag[i + 1 : n, i]

        # Calcular o comprimento do vetor w
        Lw = np.linalg.norm(w)

        # Copiar Lw na posição i+1 do vetor w'
        w_linha[i + 1] = Lw

        # Calcular o vetor N
        N = w - w_linha

        # Normalizar o vetor N
        n_vec = N / np.linalg.norm(N)

        # Montar a matriz de Householder
        H_i = np.eye(n) - 2 * np.outer(n_vec, n_vec.T)

        # Atualizar a matriz tridiagonal
        A_tridiag = H_i @ A_tridiag @ H_i

        # Acumular as transformações de Householder
        H_acumulada = H_acumulada @ H_i

    return A_tridiag, H_acumulada


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


def matriz_jacobi_baseada_no_elemento_ij_de_R_velha(R, i, j, n, epsilon=1e-9):
    """
    Constrói a matriz de Jacobi para zerar o elemento (i, j) de R.

    Parâmetros:
    R : np.array
        Matriz onde o elemento (i, j) deve ser zerado.
    i, j : int
        Índices para a construção da matriz de Jacobi.
    n : int
        Dimensão da matriz R.
    epsilon : float, opcional
        Tolerância para considerar o elemento R[i, j] ou R[j, j] como zero. O padrão é 1e-9.

    Retorna:
    J : np.array
        Matriz de Jacobi completa para zerar o elemento (i, j) de R.
    """

    J = np.eye(n)  # Matriz identidade

    # Se o elemento R[i, j] é suficientemente pequeno para ser considerado zero
    if np.abs(R[i, j]) <= epsilon:
        return J  # Retorna a matriz identidade

    # Se o elemento R[j, j] for muito pequeno
    if np.abs(R[j, j]) <= epsilon:
        if R[i, j] < 0:  # O numerador será positivo e assumimos tangente tende a +inf
            theta = np.pi / 2  # 90 graus
        else:  # O numerador será negativo e assumimos tangente tende a -inf
            theta = -np.pi / 2  # -90 graus
    else:
        # Se R[j, j] não é pequeno, calcula o ângulo normalmente
        theta = np.arctan2(-R[i, j], R[j, j])

    cos_t = np.cos(theta)
    sin_t = np.sin(theta)

    # Constrói a matriz de Jacobi baseada no ângulo calculado
    J[j, j] = cos_t
    J[i, i] = cos_t
    J[i, j] = sin_t
    J[j, i] = -sin_t

    return J


def decomposicao_qr(A):
    """
    Realiza a decomposição QR da matriz A.

    Parâmetros:
    A : np.array
        Matriz quadrada para ser decomposta.

    Retorna:
    Q : np.array
        Matriz ortogonal da decomposição QR.
    R : np.array
        Matriz triangular superior da decomposição QR.
    """

    n = A.shape[0]  # Dimensão de A
    QT = np.eye(n)  # Inicializa QT como identidade
    R_velha = A.copy()  # Copia da matriz original

    for j in range(n - 1):  # Loop das colunas
        for i in range(j + 1, n):  # Loop das linhas
            # Construção da matriz de Jacobi J_ij
            J_ij = matriz_jacobi_baseada_no_elemento_ij_de_R_velha(R_velha, i, j, n)

            # Matriz modificada com elemento (i, j) zerado
            R_nova = np.dot(J_ij, R_velha)

            # Salvar para o próximo passo
            R_velha = R_nova.copy()

            # Acumular o produto das matrizes de Jacobi
            QT = np.dot(J_ij, QT)  # QT é a transposta de Q. Note a ordem do produto

    # No final do loop externo, o formato da matriz R_nova é triangular superior
    Q = QT.T  # Transposta de QT para obter Q
    R = R_nova
    return Q, R


def metodo_qr(A, epsilon=1e-9, imprimir_iteracao=True):
    """
    Método QR para encontrar autovalores e autovetores de uma matriz,
    seguindo o algoritmo descrito no PDF.

    Parâmetros:
    A : np.array
        Matriz quadrada para a qual os autovalores e autovetores serão encontrados.
    epsilon : float
        Tolerância para a convergência.

    Retorna:
    P : np.array
        Matriz acumulada das transformações de similaridade.
    Lamb : np.array
        Vetor com os autovalores da matriz A.
    A_nova : np.array
        Matriz diagonal resultante após as iterações do método QR.
    """

    n = A.shape[0]
    P = np.eye(n)  # Inicializa a matriz P como a matriz identidade
    A_velha = A.copy()  # Copia a matriz original
    val = 100.0  # Escalar para verificar a convergência com a soma dos quadrados dos elementos abaixo da diagonal
    iteracao = 1

    while val > epsilon:
        # Decomposição QR (devolve as matrizes Q e R)
        Q, R = decomposicao_qr(A_velha)

        # Calcula a nova matriz A_nova = RQ
        A_nova = np.dot(R, Q)

        # Salvar A_nova para a próxima iteração
        A_velha = A_nova.copy()

        if imprimir_iteracao:
            # Imprime a matriz após cada iteração (item 1c)
            print(f"\nIteracao {iteracao}:\n")
            print(A_nova)
            iteracao += 1

        # Acumula o produto das matrizes Q
        P = np.dot(P, Q)

        # Verifica se a matriz A_nova já é diagonal
        # Soma dos quadrados dos elementos abaixo da diagonal
        val = np.sum(np.tril(A_nova, -1) ** 2)

    Lamb = np.diag(A_nova)  # Autovalores são os elementos da diagonal de A_nova
    return P, Lamb, A_nova


def verificar_autovetores(A, P, atol=1e-6):
    """
    Verifica se as colunas de P são autovetores de A.

    Parâmetros:
    A : np.array
        Matriz original.
    P : np.array
        Matriz cujas colunas serão testadas como autovetores.
    atol : float
        Tolerância absoluta para comparação.

    Retorna:
    True se todas as colunas de P forem autovetores de A.
    """

    for i in range(P.shape[1]):
        v = P[:, i]
        Av = np.dot(A, v)
        lambda_v = np.dot(v.T, Av) / np.dot(
            v.T, v
        )  # Ajuste na forma de calcular lambda_v

        # Verifica se Av é proporcional a v (considerando sinais opostos)
        if not (
            np.allclose(Av, lambda_v * v, atol=atol)
            or np.allclose(Av, -lambda_v * v, atol=atol)
        ):
            return False
    return True
