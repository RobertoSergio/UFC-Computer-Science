from algoritmos import metodo_predictor_corrector_4ordem
import numpy as np

# Condições iniciais
V0 = 5.0  # Velocidade inicial (m/s)
Y0 = 200.0  # Posição inicial (m)
T0 = 0.0  # Tempo inicial (s)
M = 2  # Massa do objeto
K = 0.25  # Constante de aerodinâmica
G = 10  # Gravidade

# Diferentes passos de tempo
DELTA_TS = [0.1, 0.01, 0.001, 0.0001]

def F(v):
    dv_dt = -G - (K / M) * v  # dv/dt
    dy_dt = v  # dy/dt
    return dv_dt, dy_dt

def main():

    # Aplicar para cada delta
    for delta_t in DELTA_TS:
        print(f"\nResultados para delta_t = {delta_t}:")

        tempos, velocidades = metodo_predictor_corrector_4ordem(
            lambda t, v: F(v)[0], T0, V0, delta_t, int(20/delta_t)
        )

        posicoes = [Y0 + v * delta_t for v in velocidades]

        # Encontrar a altura máxima e o tempo correspondente
        idx_max_altura = np.argmax(posicoes)  # Índice da altura máxima
        y_max = posicoes[idx_max_altura]
        t_max = tempos[idx_max_altura]

        # Tempo total até a queda no mar e velocidade no impacto
        t_total = tempos[-1]
        v_impacto = velocidades[-1]

        # Resultados
        print(f"Altura máxima: {y_max} m")
        print(f"Tempo até a altura máxima: {t_max} s")
        print(f"Tempo total até a queda no mar: {t_total} s")
        print(f"Velocidade no impacto com o mar: {v_impacto} m/s")


if __name__ == "__main__":
    main()