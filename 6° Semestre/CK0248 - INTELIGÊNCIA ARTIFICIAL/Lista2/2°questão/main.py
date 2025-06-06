from utils import minimax, best_move

def main():
    estado_inicial = (2, 3, 5, 10)
    jogador_atual = True

    print(f"Estado inicial: {estado_inicial}")
    while not all(fichas == 0 for fichas in estado_inicial):
        if jogador_atual:
            print("\nJogador Maximillian (Máquina):")
            estado_inicial = best_move(estado_inicial, jogador_atual)
        else:
            print("\nJogador Mindy (Máquina):")
            estado_inicial = best_move(estado_inicial, jogador_atual)
        print(f"Novo estado: {estado_inicial}")
        jogador_atual = not jogador_atual

    if jogador_atual:
        print("\nMindy ganhou!")
    else:
        print("\nMaximillian ganhou!")

if __name__ == "__main__":
    main()
