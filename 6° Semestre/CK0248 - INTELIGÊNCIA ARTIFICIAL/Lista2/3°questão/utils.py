import math

def inicializar_tabuleiro():
    tabuleiro = [[" " for _ in range(8)] for _ in range(8)]
    tabuleiro[7][0] = "Q"
    tabuleiro[1][4] = "P"
    return tabuleiro

def exibir_tabuleiro(tabuleiro):
    for linha in tabuleiro:
        print(" ".join(linha))
    print()

def movimentos_rainha(tabuleiro, x, y):
    movimentos = []
    direcoes = [(-1, 0), (1, 0), (0, -1), (0, 1), (-1, -1), (-1, 1), (1, -1), (1, 1)]
    for dx, dy in direcoes:
        nx, ny = x + dx, y + dy
        while 0 <= nx < 8 and 0 <= ny < 8:
            if tabuleiro[nx][ny] == " " or tabuleiro[nx][ny] == "P":
                movimentos.append((nx, ny))
                if tabuleiro[nx][ny] == "P":
                    break
            else:
                break
            nx += dx
            ny += dy
    return movimentos

def movimentos_peao(tabuleiro, x, y):
    movimentos = []
    if x + 1 < 8 and tabuleiro[x + 1][y] == " ":
        movimentos.append((x + 1, y))
    for dx, dy in [(1, -1), (1, 1)]:
        nx, ny = x + dx, y + dy
        if 0 <= nx < 8 and 0 <= ny < 8 and tabuleiro[nx][ny] == "Q":
            movimentos.append((nx, ny))
    return movimentos

def avaliar(tabuleiro):
    rainha = None
    peao = None
    for i in range(8):
        for j in range(8):
            if tabuleiro[i][j] == "Q":
                rainha = (i, j)
            elif tabuleiro[i][j] == "P":
                peao = (i, j)

    if rainha is not None and peao is not None:
        if rainha == peao:
            return 100
        return -math.sqrt((rainha[0] - peao[0]) ** 2 + (rainha[1] - peao[1]) ** 2)
    return 0

def aplicar_movimento(tabuleiro, x, y, nx, ny):
    nova_tabuleiro = [linha[:] for linha in tabuleiro]
    nova_tabuleiro[nx][ny] = tabuleiro[x][y]
    nova_tabuleiro[x][y] = " "
    return nova_tabuleiro

def minimax(tabuleiro, profundidade, maximizando):
    if profundidade == 0 or avaliar(tabuleiro) == 100:
        return avaliar(tabuleiro), None
    melhor_movimento = None
    if maximizando:
        melhor_valor = -math.inf
        for i in range(8):
            for j in range(8):
                if tabuleiro[i][j] == "Q":
                    for nx, ny in movimentos_rainha(tabuleiro, i, j):
                        novo_tabuleiro = aplicar_movimento(tabuleiro, i, j, nx, ny)
                        valor, _ = minimax(novo_tabuleiro, profundidade - 1, False)
                        if valor > melhor_valor:
                            melhor_valor = valor
                            melhor_movimento = (i, j, nx, ny)
    else:
        melhor_valor = math.inf
        for i in range(8):
            for j in range(8):
                if tabuleiro[i][j] == "P":
                    for nx, ny in movimentos_peao(tabuleiro, i, j):
                        novo_tabuleiro = aplicar_movimento(tabuleiro, i, j, nx, ny)
                        valor, _ = minimax(novo_tabuleiro, profundidade - 1, True)
                        if valor < melhor_valor:
                            melhor_valor = valor
                            melhor_movimento = (i, j, nx, ny)
    return melhor_valor, melhor_movimento