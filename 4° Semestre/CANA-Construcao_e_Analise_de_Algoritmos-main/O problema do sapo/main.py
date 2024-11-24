def Atravessar(Estrutura):
    n = len(Estrutura)

    # Inicializa a lista_memoria para armazenar resultados calculados
    lista_memoria = [[-1] * n for _ in range(n)]

    # Chama a função recursiva inicial
    return atravessar_recursivo(Estrutura, 0, 0, lista_memoria, n)

def atravessar_recursivo(Estrutura, pos, velocidade, lista_memoria, n):
    # Verifica se atingiu ou ultrapassou o final da estrutura
    if pos >= n:
        return False

    # Verifica se o resultado já foi calculado e retorna o valor armazenado
    if lista_memoria[pos][velocidade] != -1:
        return lista_memoria[pos][velocidade]

    # Verifica se a posição atual é alcançável
    if Estrutura[pos] == '*':
        # Tenta as três opções de velocidade (velocidade atual, velocidade atual + 1, velocidade atual - 1)
        if atravessar_recursivo(Estrutura, pos + velocidade, velocidade, lista_memoria, n) \
           or atravessar_recursivo(Estrutura, pos + velocidade + 1, velocidade + 1, lista_memoria, n) \
           or atravessar_recursivo(Estrutura, pos + velocidade - 1, velocidade - 1, lista_memoria, n):

            # Se qualquer uma das opções for True, marca como possível e armazena o resultado
            lista_memoria[pos][velocidade] = True
            return True

    # Marca como impossível e armazena o resultado
    lista_memoria[pos][velocidade] = False
    return False

# Main:
Rio = "* * - *"
Estrutura = Rio.split()
r = Atravessar(Estrutura)
if r:
    print("É possível atravessar o rio.")
else:
    print("Não é possível atravessar o rio.")
