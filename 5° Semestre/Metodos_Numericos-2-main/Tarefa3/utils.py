import math

# Função f(X) que queremos calcular
def f(x):
    return pow((math.sin(2 * x) + 4 * pow(x, 2) + 3 * x), 2)

# formulas da abordagem fechada de 1°grau ao 4°grau
def abordagem_fechada_grau1(xi, xf):
    return ((xf-xi) / 2) * (f(xi) + f(xf))

def abordagem_fechada_grau2(xi, xf):
    h = (xf - xi) / 2
    return (h / 3) * (f(xi) + 4* f(xi + h) + f(xi + 2 * h))

def abordagem_fechada_grau3(xi, xf):
    h = (xf - xi) / 3
    return (3 * h / 8) * (f(xi) + 3 * f(xi + h) + 3 * f(xi + 2 * h) + f(xi + 3 * h))

def abordagem_fechada_grau4(xi, xf):
    h = (xf - xi) / 4
    return (2 * h / 45) * (7*f(xi) + 32 * f(xi + h) + 12 * f(xi + 2 * h) + 32*f(xi + 3 * h) + 7*f(xi + 4 * h))

# formulas da abordagem aberta de 1°grau ao 4°grau
def abordagem_aberta_grau1(xi, xf):
    h = (xf - xi) / 3
    return (3*h / 2) * (
        f(xi + h)
        + f(xi + 2 *h)
    )    
    
def abordagem_aberta_grau2(xi, xf):
    h = (xf - xi) / 4
    return (4*h / 3) * (
        2 * f(xi)
        - f(xi + h)
        + 2* f(xi + 2 * h)
    )    

def abordagem_aberta_grau3(xi, xf):
    h = (xf - xi) / 5
    return (5*h / 24) * (
        11 * f(xi)
        + f(xi + h)
        + f(xi + 2 * h)
        + 11 * f(xi + 3 * h)
    ) 
    
def abordagem_aberta_grau4(xi, xf):
    h = (xf - xi) / 6
    return ((h) / 10) * (
        33 * f(xi)
        - 42 * f(xi + h)
        + 78 * f(xi + 2 * h)
        - 42 * f(xi + 3 * h)
        + 33 * f(xi + 4 * h)
    )

# função que vai calcular a integração e definir qual abordagem e grau
def integracao(a, b, epsilon, metodo, grau):
    delta = 0
    erro = 0
    res = 0
    res_ant = 0
    N = 2
    integ = True
    interacao = 0

    while integ:
        interacao += 1
        delta = (b - a) / N
        res_atual = 0
        for i in range(N):
            xi = a + i * delta
            xf = xi + delta
            if metodo == 1:
                if grau == 1:
                    res_atual += abordagem_aberta_grau1(xi, xf)
                if grau == 2:
                    res_atual += abordagem_aberta_grau2(xi, xf)
                if grau == 3:
                    res_atual += abordagem_aberta_grau3(xi, xf)
                if grau == 4:
                    res_atual += abordagem_aberta_grau4(xi, xf)
            if metodo == 2:
                if grau == 1:
                    res_atual += abordagem_fechada_grau1(xi, xf)
                if grau == 2:
                    res_atual += abordagem_fechada_grau2(xi, xf)
                if grau == 3:
                    res_atual += abordagem_fechada_grau3(xi, xf)
                if grau == 4:
                    res_atual += abordagem_fechada_grau4(xi, xf)

        print("---------------------------------------------")
        print(f"          Interação: {interacao}")
        print(f"          Resultado: {res_atual}")
        print("---------------------------------------------")

        N *= 2
        res_ant = res
        res = res_atual
        erro = abs(res - res_ant)

        if erro < epsilon or interacao >= 25:
            integ = False
