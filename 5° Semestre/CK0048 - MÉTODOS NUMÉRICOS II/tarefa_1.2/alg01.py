import numpy as np
from filtro_gaussiano import aplicar_filtro_gaussiano, criar_kernel_gaussiano
from utils import carregar_imagem, salvar_imagem, mostrar_imagem
from filtro_sobel import (
    calcular_magnitude_gradiente,
    aplicar_threshold,
    aplicar_filtro_sobel,
)

if __name__ == "__main__":

    caminho_imagem = "dog.png"

    imagem = carregar_imagem(caminho_imagem)

    tamanho_kernel = 5
    sigma = 3.5
    threshold = 75

    # Gauss
    kernel = criar_kernel_gaussiano(tamanho_kernel, sigma)

    imagem_suavizada = aplicar_filtro_gaussiano(imagem, kernel)
    mostrar_imagem(imagem_suavizada.astype(np.uint8), "Imagem Suavizada - Gauss")

    # caminho_saida = "saida3.jpg"
    # salvar_imagem(imagem_suavizada.astype(np.uint8), "resultado_filtro_gaussiano")

    # Sobel
    a, b = aplicar_filtro_sobel(imagem)

    magnitude_gradiente = calcular_magnitude_gradiente(a, b)
    mostrar_imagem(magnitude_gradiente, "Magnitude do Gradiente")

    matriz_final = aplicar_threshold(magnitude_gradiente, threshold)
    mostrar_imagem(matriz_final, "Matriz Final com Threshold")
