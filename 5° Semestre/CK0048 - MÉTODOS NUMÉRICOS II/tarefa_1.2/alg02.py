import numpy as np
from filtro_gaussiano import aplicar_filtro_gaussiano, criar_kernel_gaussiano
from filtro_laplace import aplicar_filtro_laplace, gerar_matriz_b
from utils import carregar_imagem, mostrar_imagem, salvar_imagem

if __name__ == "__main__":

    caminho_imagem = "dog.png"

    imagem = carregar_imagem(caminho_imagem)

    # Gauss
    tamanho_kernel = 5
    sigma = 3.5
    kernel = criar_kernel_gaussiano(tamanho_kernel, sigma)

    imagem_suavizada = aplicar_filtro_gaussiano(imagem, kernel)

    # caminho_saida = "saida3.jpg"
    # salvar_imagem(imagem_suavizada.astype(np.uint8), "resultado_filtro_gaussiano")

    mostrar_imagem(imagem_suavizada.astype(np.uint8), "Imagem Suavizada")

    # Laplace
    matriz_a = aplicar_filtro_laplace(imagem_suavizada)

    mostrar_imagem(matriz_a, "Matriz A (Filtro de Laplace)")

    # 2.3 Gerar a matriz B
    tolerancia = 0.0001
    matriz_b = gerar_matriz_b(matriz_a, tolerancia)

    mostrar_imagem(matriz_b, "Matriz B (Threshold Laplace)")
