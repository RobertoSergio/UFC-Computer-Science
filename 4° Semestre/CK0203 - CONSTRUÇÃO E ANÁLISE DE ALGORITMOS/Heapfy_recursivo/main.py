def dividir_heap_em_dois(lista_aux):
    tamanho_heap = len(lista_aux)

    if tamanho_heap < 2:
        return [], []

    if tamanho_heap == 2:
        return [lista_aux[0]], [lista_aux[1]]

    raiz_isolada = [lista_aux[0]]

    sub_heap1 = []
    sub_heap2 = []

    i = 1 
    elementos_por_grupo = 1 

    while i < tamanho_heap:
        for j in range(elementos_por_grupo):
            if i < tamanho_heap:
                sub_heap1.append(lista_aux[i])
                i += 1
        for j in range(elementos_por_grupo):
            if i < tamanho_heap:
                sub_heap2.append(lista_aux[i])
                i += 1
        elementos_por_grupo *= 2

    # Printar os resultados do heap
    print("Raiz Isolada:", raiz_isolada)
    print("Sub-Heap 1:", sub_heap1)
    print("Sub-Heap 2:", sub_heap2)
  
    # Chamadas recursivas para as sub-heaps
    dividir_heap_em_dois(sub_heap1)
    dividir_heap_em_dois(sub_heap2)
    
    return 0

# Exemplo de uso
lista = [100, 50, 70, 35, 55, 20, 40, 12, 26, 8, 17, 2, 7, 1]
dividir_heap_em_dois(lista)
