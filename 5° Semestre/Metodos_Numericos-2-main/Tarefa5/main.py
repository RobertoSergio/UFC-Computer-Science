from utils import integracao


if __name__ == "__main__":

    print("---------------------------------------------")
    print("-------------------Tarefa 5------------------")
    print("---------------------------------------------\n")

    programa = True

    while programa:
        print("A funcao usada sera: (sen(2x) + 4*(x)^2 + 3x)^2\n")
        xi = int(input("Escreva o valor de xi:"))
        xf = int(input("Escreva o valor de xf:"))
        epilson = float(input("Escreva o valor do erro:"))

        print("Escolha quantos pontos a Quadratura de Gauss-Legendre: ")
        print("0: 2 pontos ")
        print("1: 3 pontos ")
        print("2: 4 pontos ")
        pontos = int(input("Digite qual tipo de Quadratura de Gauss-Legendre voce quer usar: "))
        
        if pontos == 0:
            print("Você escolheu  Quadratura de Gauss-Legendre de 2 pontos")
            integracao(xi, xf, epilson, pontos)
        if pontos == 1:
            print("Você escolheu  Quadratura de Gauss-Legendre de 3 pontos")
            integracao(xi, xf, epilson, pontos)
        if pontos == 2:
            print("Você escolheu  Quadratura de Gauss-Legendre de 4 pontos")
            integracao(xi, xf, epilson, pontos)      
            
        print("\n---------------------------------------------")
        print("1-Rodar o programa novamente ")
        print("2-Sair do programa")
        print("---------------------------------------------")

        novamente = int(input("Digite a sua escolha?"))

        if novamente == 1:
            programa = True
        if novamente == 2:
            programa = False