#include <iostream>
#include <cmath>
#include "utils.cpp"

using namespace std;

main(){
    cout << "---------------------------------------------" << endl;
    cout << "-------------------Tarefa 3------------------" << endl;
    cout << "---------------------------------------------" << endl;

    bool programa = true;

    while(programa){
        cout << ("A funcao usada sera: (sen(2x) + 4*(x)^2 + 3x)^2\n");
        int xi;
        cout << "Escreva o valor de xi:";
        cin >> xi;
        int xf;
        cout << "Escreva o valor de xf:";
        cin >> xf;
        double epilson;
        cout << "Escreva o valor do erro:";
        cin >> epilson;
        cout << "Escolha a abordagem desejada:\n";
        cout << "1: Abordagem Aberta" << endl;
        cout << "2: Abordagem Fechada" << endl;
        int escolha;
        cout << "Digite o número da abordagem que voce quer escolher" << endl;
        cin >> escolha;

        cout << "Escolha o grau desejado::\n";
        cout << "1: 1 grau" << endl;
        cout << "2: 2 grau" << endl;
        cout << "3: 3 grau" << endl;
        cout << "4: 4 grau" << endl;
        int grau;
        cout << "Digite o número da abordagem que voce quer escolher" << endl;
        cin >> grau;

        if(escolha == 1){
            if(grau == 1){
                cout << "Voce escolheu a Abordagem Aberta de 1°grau" << endl;
                integracao(xi, xf, epilson, escolha, grau);
            } else if(grau ==2){
                cout << "Voce escolheu a Abordagem Aberta de 2°grau" << endl;
                integracao(xi, xf, epilson, escolha, grau);
            } else if(grau ==3){
                cout << "Voce escolheu a Abordagem Aberta de 3°grau" << endl;
                integracao(xi, xf, epilson, escolha, grau);
            } else if(grau ==4){
                cout << "Voce escolheu a Abordagem Aberta de 4°grau" << endl;
                integracao(xi, xf, epilson, escolha, grau);
            } else{
                cout << "Essa opção não existe" << endl;
                break;
            }
        }

        if(escolha == 2){
            if(grau == 1){
                cout << "Voce escolheu a Abordagem Fechada de 1°grau" << endl;
                integracao(xi, xf, epilson, escolha, grau);
            } else if(grau ==2){    
                cout << "Voce escolheu a Abordagem Fechada de 2°grau" << endl;
                integracao(xi, xf, epilson, escolha, grau);
            } else if(grau ==3){
                cout << "Voce escolheu a Abordagem Fechada de 3°grau" << endl;
                integracao(xi, xf, epilson, escolha, grau);
            } else if(grau ==4){
                cout << "Voce escolheu a Abordagem Fechada de 4°grau" << endl;
                integracao(xi, xf, epilson, escolha, grau);
            } else{
                cout << "Essa opção não existe" << endl;
                break;
            }
        }
        cout << "Quer continuar com o programa?\n";
        cout << "1: Sim" << endl;
        cout << "2: Não" << endl;
        int resposta;
        cout << "Digite o número da resposta:" << endl;
        cin >> resposta;
        if(resposta == 2){
            programa=false;
        }
    } 
}