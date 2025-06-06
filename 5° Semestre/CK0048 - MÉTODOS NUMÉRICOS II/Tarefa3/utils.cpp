#include "utils.h"
#include <iostream>
#include <cmath>

using namespace std;

// Função f(X) que queremos calcular
double f(double x) {
    return pow((sin(2 * x) + 4 * pow(x, 2) + 3 * x), 2);
}

// Fórmulas da abordagem fechada de 1°grau ao 4°grau
double abordagem_fechada_grau1(double xi, double xf) {
    return ((xf - xi) / 2) * (f(xi) + f(xf));
}

double abordagem_fechada_grau2(double xi, double xf) {
    double h = (xf - xi) / 2;
    return (h / 3) * (f(xi) + 4 * f(xi + h) + f(xi + 2 * h));
}

double abordagem_fechada_grau3(double xi, double xf) {
    double h = (xf - xi) / 3;
    return (3 * h / 8) * (f(xi) + 3 * f(xi + h) + 3 * f(xi + 2 * h) + f(xi + 3 * h));
}

double abordagem_fechada_grau4(double xi, double xf) {
    double h = (xf - xi) / 4;
    return (2 * h / 45) * (7 * f(xi) + 32 * f(xi + h) + 12 * f(xi + 2 * h) + 32 * f(xi + 3 * h) + 7 * f(xi + 4 * h));
}

// Fórmulas da abordagem aberta de 1°grau ao 4°grau
double abordagem_aberta_grau1(double xi, double xf) {
    double h = (xf - xi) / 3;
    return (3 * h / 2) * (f(xi + h) + f(xi + 2 * h));
}

double abordagem_aberta_grau2(double xi, double xf) {
    double h = (xf - xi) / 4;
    return (4 * h / 3) * (2 * f(xi) - f(xi + h) + 2 * f(xi + 2 * h));
}

double abordagem_aberta_grau3(double xi, double xf) {
    double h = (xf - xi) / 5;
    return (5 * h / 24) * (11 * f(xi) + f(xi + h) + f(xi + 2 * h) + 11 * f(xi + 3 * h));
}

double abordagem_aberta_grau4(double xi, double xf) {
    double h = (xf - xi) / 6;
    return (h / 10) * (33 * f(xi) - 42 * f(xi + h) + 78 * f(xi + 2 * h) - 42 * f(xi + 3 * h) + 33 * f(xi + 4 * h));
}

void integracao(double a, double b, double epsilon, int metodo, int grau) {
    double delta = 0;
    double erro = 0;
    double res = 0;
    double res_ant = 0;
    int N = 2;
    bool integ = true;
    int interacao = 0;

    while (integ) {
        interacao++;
        delta = (b - a) / N;
        double res_atual = 0;
        for (int i = 0; i < N; i++) {
            double xi = a + i * delta;
            double xf = xi + delta;
            if (metodo == 1) {
                if (grau == 1) {
                    res_atual += abordagem_aberta_grau1(xi, xf);
                }
                if (grau == 2) {
                    res_atual += abordagem_aberta_grau2(xi, xf);
                }
                if (grau == 3) {
                    res_atual += abordagem_aberta_grau3(xi, xf);
                }
                if (grau == 4) {
                    res_atual += abordagem_aberta_grau4(xi, xf);
                }
            }
            if (metodo == 2) {
                if (grau == 1) {
                    res_atual += abordagem_fechada_grau1(xi, xf);
                }
                if (grau == 2) {
                    res_atual += abordagem_fechada_grau2(xi, xf);
                }
                if (grau == 3) {
                    res_atual += abordagem_fechada_grau3(xi, xf);
                }
                if (grau == 4) {
                    res_atual += abordagem_fechada_grau4(xi, xf);
                }
            }
        }

        cout << "---------------------------------------------" << endl;
        cout << "          Interação: " << interacao << endl;
        cout << "          Resultado: " << res_atual << endl;
        cout << "---------------------------------------------" << endl;

        N *= 2;
        res_ant = res;
        res = res_atual;
        erro = abs(res - res_ant);

        if (erro < epsilon || interacao >= 25) {
            integ = false;
        }
    }
}
