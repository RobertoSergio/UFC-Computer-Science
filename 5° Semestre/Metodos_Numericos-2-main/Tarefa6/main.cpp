#include <iostream>
#include <cmath>
#include <vector>
#include "utils.cpp"

int main() {
    cout << "---------------------------------------------" << endl;
    cout << "-------------------Tarefa 6------------------" << endl;
    cout << "---------------------------------------------\n" << endl;

    bool programa = true;

    while (programa) {
        vector<double> raizes;
        vector<double> pesos;
        cout << "Escolha uma Quadratura especial de Gauss: " << endl;
        cout << "0: Gauss-Hermite " << endl;
        cout << "1: Gauss-Laguerre " << endl;
        cout << "2: Gauss-Chebyshev " << endl;
        int gauss;
        cout << "Digite qual tipo de Quadratura especial de Gauss voce quer usar: ";
        cin >> gauss;

        cout << "Escolha o grau desejado::\n";
        cout << "2: 2 grau" << endl;
        cout << "3: 3 grau" << endl;
        cout << "4: 4 grau" << endl;
        int grau;
        cout << "Digite o número da abordagem que voce quer escolher" << endl;
        cin >> grau;

        if (gauss == 0) {
            if (grau == 2){
                cout << "Você escolheu  Quadratura de Gauss-Hermite de grau 2" << endl;
                raizes = raiz_Laguerre_2();
                pesos = w_de_Laguerre_2(raizes);
            }
            else if(grau ==3){
                cout << "Você escolheu  Quadratura de Gauss-Hermite de grau 3" << endl;
                raizes = raiz_hermite_3();
                pesos = w_de_hermite_3(raizes);
            }
            else if(grau ==4){
                cout << "Você escolheu  Quadratura de Gauss-Hermite de grau 4" << endl;
                raizes = raiz_hermite_4();
                pesos = w_de_hermite_4(raizes);
            }
        } else if (gauss == 1) {
            if (grau == 2){
                cout << "Você escolheu  Quadratura de Gauss-Laguerre de grau 2" << endl;
                raizes = raiz_Laguerre_2();
                pesos = w_de_Laguerre_2(raizes);
            }
            else if(grau ==3){
                cout << "Você escolheu  Quadratura de Gauss-Laguerre de grau 3" << endl;
                raizes = raiz_Laguerre_3();
                pesos = w_de_Laguerre_3(raizes);
            }
            else if(grau ==4){
                cout << "Você escolheu  Quadratura de Gauss-Laguerre de grau 4" << endl;
                raizes = raiz_Laguerre_4();
                pesos = w_de_Laguerre_4(raizes);
            }
        } else if (gauss == 2) {
            if (grau == 2){
                cout << "Você escolheu  Quadratura de Gauss-Chebyshev de grau 2" << endl;
                raizes = raiz_Chebyshev_2();
                pesos = w_de_Chebyshev_2(raizes);
            }
            else if(grau ==3){
                cout << "Você escolheu  Quadratura de Gauss-Chebyshev de grau 3" << endl;
                raizes = raiz_Chebyshev_3();
                pesos = w_de_Chebyshev_3(raizes);
            }
            else if(grau ==4){
                cout << "Você escolheu  Quadratura de Gauss-Chebyshev de grau 4" << endl;
                raizes = raiz_Chebyshev_4();
                pesos = w_de_Chebyshev_4(raizes);
            }
        }
        cout << "Raizes: ";
        for (double raiz : raizes) {
            cout << raiz << " ";
        }
        cout << endl;

        cout << "Pesos: ";
        for (double peso : pesos) {
            cout << peso << " ";
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