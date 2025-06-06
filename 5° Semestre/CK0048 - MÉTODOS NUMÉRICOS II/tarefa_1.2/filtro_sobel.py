import numpy as np


def aplicar_filtro_sobel(imagem):
    # Kernels 3x3 usado em Sobel
    sobel_x = np.array(
        [
            [-1, 0, 1],
            [-2, 0, 2],
            [-1, 0, 1],
        ],
        dtype=np.float32,
    )
    sobel_y = np.array(
        [
            [-1, -2, -1],
            [0, 0, 0],
            [1, 2, 1],
        ],
        dtype=np.float32,
    )

    altura, largura = imagem.shape
    a = np.zeros_like(imagem, dtype=np.float32)
    b = np.zeros_like(imagem, dtype=np.float32)

    # Aplicação do kernel, evitando bordas
    for i in range(1, altura - 1):
        for j in range(1, largura - 1):
            gx = 0
            gy = 0
            for k in range(3):
                for l in range(3):
                    gx += imagem[i + k - 1, j + l - 1] * sobel_x[k, l]
                    gy += imagem[i + k - 1, j + l - 1] * sobel_y[k, l]
            a[i, j] = gx
            b[i, j] = gy

    return a, b


def calcular_magnitude_gradiente(a, b):
    # 2.3) em cada uma das matrizes, A e B, eleve ao quadrado os valores dos elementos
    a_quadrado = np.square(a)
    b_quadrado = np.square(b)

    # 2.4) some as duas matrizes A e B modificadas no passo 2.3 e tire
    # a raiz quadrada  de cada elemento dessa matriz, C
    c = np.sqrt(a_quadrado + b_quadrado)
    return c


def aplicar_threshold(magnitude_gradiente, threshold):
    """
    4) gere uma matriz Final, D, com
      - pixel 0 caso o pixel correspondente da matriz C seja menor do que o threshold
      - pixel 1. caso o pixel correspondente da matriz C seja maior do que o threshold.
    """
    matriz_final = np.where(magnitude_gradiente > threshold, 1, 0)
    return matriz_final
