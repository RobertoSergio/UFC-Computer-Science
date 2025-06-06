from utils import inicializar_tabuleiro, exibir_tabuleiro, minimax, aplicar_movimento

def main():
    tabuleiro = inicializar_tabuleiro()
    exibir_tabuleiro(tabuleiro)
    turno_ia = True

    for _ in range(3):
        if turno_ia:
            _, movimento = minimax(tabuleiro, 3, True)
        else:
            _, movimento = minimax(tabuleiro, 3, False)
        if movimento:
            x, y, nx, ny = movimento
            tabuleiro = aplicar_movimento(tabuleiro, x, y, nx, ny)
        exibir_tabuleiro(tabuleiro)
        turno_ia = not turno_ia

if __name__ == "__main__":
    main()