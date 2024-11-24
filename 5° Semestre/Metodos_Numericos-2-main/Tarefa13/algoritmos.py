import numpy as np


def runge_kutta_terceira_ordem(F, v0, y0, t0, delta_t):
    """
    Método de Runge-Kutta de Terceira Ordem para resolver um PVI até uma condição de parada.
    """
    tempos = [t0]
    velocidades = [v0]
    posicoes = [y0]

    while posicoes[-1] >= 0:  # Continua até que a posição seja negativa (atinge o solo)
        v_i = velocidades[-1]
        y_i = posicoes[-1]
        t_i = tempos[-1]

        F1_v, F1_y = F(v_i)  # Equação 47
        v_half = v_i + (delta_t / 2) * F1_v  # Equação 48
        # y_half = y_i + (delta_t / 2) * F1_y  # Equação 48

        F2_v, F2_y = F(v_half)  # Equação 49

        v_full = v_i + delta_t * F2_v  # Equação 50
        # y_full = y_i + delta_t * F2_y  # Equação 50

        F3_v, F3_y = F(v_full)  # Equação 51

        v_next = v_i + delta_t * (F1_v + 4 * F2_v + F3_v) / 6  # Equação 52
        y_next = y_i + delta_t * (F1_y + 4 * F2_y + F3_y) / 6  # Equação 52

        # Armazena os novos valores
        tempos.append(t_i + delta_t)
        velocidades.append(v_next)
        posicoes.append(y_next)

    return np.array(tempos), np.array(velocidades), np.array(posicoes)
