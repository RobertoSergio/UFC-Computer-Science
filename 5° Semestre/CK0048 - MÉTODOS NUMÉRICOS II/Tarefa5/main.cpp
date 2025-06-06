#include <iostream>
#include <cmath>
#include "utils.cpp"

using namespace std;

int main() {

    cout << "---------------------------------------------" << endl;
    cout << "-------------------Tarefa 5------------------" << endl;
    cout << "---------------------------------------------\n" << endl;

    bool programa = true;

    while (programa) {
        cout << "A funcao usada sera: (sen(2x) + 4*(x)^2 + 3x)^2\n" << endl;
        int xi;
        cout << "Escreva o valor de xi:";
        cin >> xi;
        int xf;
        cout << "Escreva o valor de xf:";
        cin >> xf;
        double epilson;
        cout << "Escreva o valor do erro:";
        cin >> epilson;

        cout << "Escolha quantos pontos a Quadratura de Gauss-Legendre: " << endl;
        cout << "0: 2 pontos " << endl;
        cout << "1: 3 pontos " << endl;
        cout << "2: 4 pontos " << endl;
        int pontos;
        cout << "Digite qual tipo de Quadratura de Gauss-Legendre voce quer usar: ";
        cin >> pontos;
        
        if (pontos == 0) {
            cout << "Você escolheu  Quadratura de Gauss-Legendre de 2 pontos" << endl;
            integracao(xi, xf, epilson, pontos);
        } else if (pontos == 1) {
            cout << "Você escolheu  Quadratura de Gauss-Legendre de 3 pontos" << endl;
            integracao(xi, xf, epilson, pontos);
        } else if (pontos == 2) {
            cout << "Você escolheu  Quadratura de Gauss-Legendre de 4 pontos" << endl;
            integracao(xi, xf, epilson, pontos);
        }      
            
        cout << "\n---------------------------------------------" << endl;
        cout << "1-Rodar o programa novamente " << endl;
        cout << "2-Sair do programa" << endl;
        cout << "---------------------------------------------" << endl;

        int novamente;
        cout << "Digite a sua escolha?";
        cin >> novamente;

        if (novamente == 1) {
            programa = true;
        } else if (novamente == 2) {
            programa = false;
        }
    }

    return 0;
}
