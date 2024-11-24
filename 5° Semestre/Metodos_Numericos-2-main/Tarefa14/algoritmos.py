import numpy as np

# método de runde kutta de 4°ordem para usar na fase de inicialização
def metodo_runge_kutta_4ordem(f, x0, y0, h, n):
    x = np.zeros(n + 1)
    y = np.zeros(n + 1)
    x[0] = x0
    y[0] = y0

    for i in range(n):
        k1 = h * f(x[i], y[i])
        k2 = h * f(x[i] + h / 2, y[i] + k1 / 2)
        k3 = h * f(x[i] + h / 2, y[i] + k2 / 2)
        k4 = h * f(x[i] + h, y[i] + k3)
        x[i + 1] = x[i] + h
        y[i + 1] = y[i] + (k1 + 2 * k2 + 2 * k3 + k4) / 6

    return x, y
# método preditor-corretor de 4°ordem 
def metodo_predictor_corrector_4ordem(f, x0, y0, h, n):
    x = np.zeros(n + 1)
    y = np.zeros(n + 1)
    x[0] = x0
    y[0] = y0

    # Inicializa com Runge-Kutta de 4ª ordem para os primeiros 3 passos
    x_rk, y_rk = metodo_runge_kutta_4ordem(f, x0, y0, h, 3)
    x[1:4] = x_rk[1:4]
    y[1:4] = y_rk[1:4]

    for i in range(3, n):
        x[i + 1] = x[i] + h
        # Previsor
        yp = y[i] + h * (
            55 * f(x[i], y[i])
            - 59 * f(x[i - 1], y[i - 1])
            + 37 * f(x[i - 2], y[i - 2])
            - 9 * f(x[i - 3], y[i - 3])
        ) / 24
        # Corretor
        y[i + 1] = y[i] + h * (
            9 * f(x[i + 1], yp)
            + 19 * f(x[i], y[i])
            - 5 * f(x[i - 1], y[i - 1])
            + f(x[i - 2], y[i - 2])
        ) / 24

    return x, y