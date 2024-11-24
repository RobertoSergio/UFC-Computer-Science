from utils import integracao


if __name__ == "__main__":

    print("---------------------------------------------")
    print("-------------------Tarefa 3------------------")
    print("---------------------------------------------\n")

    programa = True

    while programa:
        print("A funcao usada sera: (sen(2x) + 4*(x)^2 + 3x)^2\n")
        xi = int(input("Escreva o valor de xi:"))
        xf = int(input("Escreva o valor de xf:"))
        epilson = float(input("Escreva o valor do erro:"))

        print("Escolha a abordagem desejada: ")
        print("1: Abordagem Aberta ")
        print("2: Abordagem Fechada ")
        escolha = int(input("Digite o número da abordagem que você quer: "))

        print("Escolha o grau desejado: ")
        print("1: 1°grau ")
        print("2: 2°grau ")
        print("3: 3°grau ")
        print("4: 4°grau ")
        grau = int(input("Digite grau que você quer: "))
        
        if escolha == 1:
            if grau == 1:
                print("Você escolheu a Abordagem Aberta de 1°grau")
                integracao(xi, xf, epilson, escolha, grau)
            if grau == 2:
                print("Você escolheu a Abordagem Aberta de 2°grau")
                integracao(xi, xf, epilson, escolha, grau)
            if grau == 3:
                print("Você escolheu a Abordagem Aberta de 3°grau")
                integracao(xi, xf, epilson, escolha, grau)
            if grau == 4:
                print("Você escolheu a Abordagem Aberta de 4°grau")
                integracao(xi, xf, epilson, escolha, grau)

        if escolha == 2:
            if grau == 1:
                print("Você escolheu a Abordagem Fechado de 1°grau")
                integracao(xi, xf, epilson, escolha, grau)
            if grau == 2:
                print("Você escolheu a Abordagem Fechado de 2°grau")
                integracao(xi, xf, epilson, escolha, grau)
            if grau == 3:
                print("Você escolheu a Abordagem Fechado de 3°grau")
                integracao(xi, xf, epilson, escolha, grau)
            if grau == 4:
                print("Você escolheu a Abordagem Fechado de 4°grau")
                integracao(xi, xf, epilson, escolha, grau)

        print("\n---------------------------------------------")
        print("1-Rodar o programa novamente ")
        print("2-Sair do programa")
        print("---------------------------------------------")

        novamente = int(input("Digite a sua escolha?"))

        if novamente == 1:
            programa = True
        if novamente == 2:
            programa = False
