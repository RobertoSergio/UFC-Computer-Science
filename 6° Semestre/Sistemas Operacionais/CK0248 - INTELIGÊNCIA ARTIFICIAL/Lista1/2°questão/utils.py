import math

lista = [1, 0.5, 0.2, 0.1, 0.05, 0.02, 0.01]
lista_trocado = {
    1: 0,
    0.5: 0,
    0.2: 0,
    0.1: 0,
    0.05: 0,
    0.02: 0,
    0.01: 0
}

def troca(quantia_paga, quantia_requerida):
    troco = quantia_paga - quantia_requerida

    for i in lista:
        while troco >= i:
            troco = round(troco - i, 2)  # Arredondamento para precisão
            lista_trocado[i] += 1

    print(lista_trocado)