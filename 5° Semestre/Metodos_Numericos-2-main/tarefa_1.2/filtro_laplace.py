import numpy as np


def aplicar_filtro_laplace(imagem):
    # Kernels 3x3 usado em Laplace
    kernel_laplace = np.array(
        [
            [0, 1, 0],
            [1, -4, 1],
            [0, 1, 0],
        ],
        dtype=np.float32,
    )

    altura, largura = imagem.shape
    imagem_laplace = np.zeros_like(imagem, dtype=np.float32)

    # Pixels da borda são evitados
    for i in range(1, altura - 1):
        for j in range(1, largura - 1):
            acumulador = 0
            for k in range(3):
                for l in range(3):
                    acumulador += imagem[i + k - 1, j + l - 1] * kernel_laplace[k, l]
            imagem_laplace[i, j] = acumulador

    return imagem_laplace


def gerar_matriz_b(matriz_a, tolerancia=0.0001):
    """
    3) Por simplicidade, gere uma imagem/matriz, B, percorrendo a imagem A e escrevendo em B
       1. caso o pixel correspondente da matriz A seja diferente de 0 dentro de uma tolerância (0.0001, por exemplo)
       0. cado o pixel correspondente da matriz A seja igual a 0 dentro de uma tolerância (0.0001, por exemplo).
    """
    matriz_b = np.where(np.abs(matriz_a) > tolerancia, 1, 0)
    return matriz_b
