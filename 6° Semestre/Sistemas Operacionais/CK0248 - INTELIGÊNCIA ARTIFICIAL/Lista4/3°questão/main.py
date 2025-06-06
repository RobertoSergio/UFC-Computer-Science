from utils import executar_algoritmo_colonia_formigas

if __name__ == "__main__":

    NUM_CIDADES = 20
    NUM_FORMIGAS = 50
    NUM_ITERACOES = 100
    ALFA = 1.0       
    BETA = 5.0       
    EVAPORACAO = 0.5    
    FEROMONIO_INICIAL = 0.1
    Q = 100             

    executar_algoritmo_colonia_formigas(NUM_CIDADES, NUM_FORMIGAS, NUM_ITERACOES, ALFA, BETA, EVAPORACAO, FEROMONIO_INICIAL, Q)
