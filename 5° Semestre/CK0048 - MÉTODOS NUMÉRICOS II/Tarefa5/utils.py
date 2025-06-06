import math

# Função f(X) que queremos calcular
def f(x):
    return pow((math.sin(2 * x) + 4 * pow(x, 2) + 3 * x), 2)

# formulas Quadratura de Gauss-Legendre com 2,3 e 4 pontos
def gauss_legendre_4pontos(xi,xf):
    a1 = -math.sqrt(3/7 - 2/7*math.sqrt(6/5))
    a2 = -math.sqrt(3/7 + 2/7*math.sqrt(6/5))
    a3 = math.sqrt(3/7 - 2/7*math.sqrt(6/5))
    a4 = math.sqrt(3/7 + 2/7*math.sqrt(6/5))

    w1 = (18 + math.sqrt(30)) / 36
    w2 = (18 - math.sqrt(30)) / 36
    w3 = (18 - math.sqrt(30)) / 36
    w4 = (18 + math.sqrt(30)) / 36
    
    return ((xf-xi)/2)*(
        f((xf-xi)/2*a1+(xf+xi)/2)*w1
        +f((xf-xi)/2*a2+(xf+xi)/2)*w2
        +f((xf-xi)/2*a3+(xf+xi)/2)*w3
        +f((xf-xi)/2*a4+(xf+xi)/2)*w4
    )

def gauss_legendre_3pontos(xi,xf):
    a1 = -math.sqrt(3/5)
    a2 = 0
    a3 = math.sqrt(3/5)
    
    w1 = 5/9
    w2 = 8/9
    w3 = 5/9
    
    return ((xf-xi)/2)*(
        f((xf-xi)/2*a1+(xf+xi)/2)*w1
        +f((xf-xi)/2*a2+(xf+xi)/2)*w2
        +f((xf-xi)/2*a3+(xf+xi)/2)*w3
    )

def gauss_legendre_2pontos(xi,xf):
    a1 = -math.sqrt(1/3)
    a2 = math.sqrt(1/3)
    
    w1 = 1
    w2 = 1
    
    return ((xf-xi)/2)*(
        f((xf-xi)/2*a1
        +(xf+xi)/2)*w1
        +f((xf-xi)/2*a2
        +(xf+xi)/2)*w2
    )

# função que calcula e define qual função da Quadratura de Gauss-Legendre será usada
def integracao(a, b, epsilon, ponto):
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
            if ponto == 0:
                res_atual += gauss_legendre_2pontos(xi,xf)
            if ponto == 1:
                res_atual += gauss_legendre_3pontos(xi,xf)
            if ponto == 2:
                res_atual += gauss_legendre_4pontos(xi,xf)
                
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
