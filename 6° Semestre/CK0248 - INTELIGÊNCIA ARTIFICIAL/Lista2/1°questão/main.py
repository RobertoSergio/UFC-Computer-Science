from utils import minimax

def main():
    estado_inicial = 10  
    jogador_inicial = True 

    resultado = minimax(estado_inicial, jogador_inicial)
    print(f"Resultado do jogo a partir do estado inicial ({estado_inicial}): {resultado}")

if __name__ == "__main__":
    main()
