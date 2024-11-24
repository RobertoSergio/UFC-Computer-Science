import numpy as np
from PIL import Image
import matplotlib.pyplot as plt


def carregar_imagem(caminho):
    # Converte para escala de cinza
    imagem = Image.open(caminho).convert("L")
    return np.array(imagem)


def salvar_imagem(imagem_array, caminho):
    imagem = Image.fromarray(imagem_array)
    imagem.save(caminho)


def mostrar_imagem(imagem, titulo):
    plt.imshow(imagem, cmap="gray")
    plt.title(titulo)
    plt.axis("off")
    plt.show()
