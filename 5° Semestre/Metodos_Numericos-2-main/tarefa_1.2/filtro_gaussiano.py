import numpy as np
import math


def criar_kernel_gaussiano(tamanho, sigma):
    kernel = np.zeros((tamanho, tamanho), dtype=np.float32)
    soma = 0
    meio = tamanho // 2

    for x in range(tamanho):
        for y in range(tamanho):
            # Aplica fórmula de gauss para matriz 2D
            # Utiliza a distância do centro
            ex = math.exp(-((x - meio) ** 2 + (y - meio) ** 2) / (2 * sigma**2))
            kernel[x, y] = (1 / (2 * math.pi * sigma**2)) * ex
            soma += kernel[x, y]

    kernel /= soma  # Normaliza o kernel
    return kernel


def aplicar_filtro_gaussiano(imagem, kernel):
    altura, largura = imagem.shape
    tamanho_kernel = kernel.shape[0]
    meio_kernel = tamanho_kernel // 2

    imagem_suavizada = np.zeros_like(imagem)

    # Pixels da borda são evitados com "meio_kernel"
    for i in range(meio_kernel, altura - meio_kernel):
        for j in range(meio_kernel, largura - meio_kernel):
            # Aplica filtro gaussiano de acordo com a matriz do kernel
            acumulador = 0
            for k in range(tamanho_kernel):
                for l in range(tamanho_kernel):
                    acumulador += (
                        imagem[i + k - meio_kernel, j + l - meio_kernel] * kernel[k, l]
                    )

            imagem_suavizada[i, j] = acumulador

    return imagem_suavizada
