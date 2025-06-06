#include <iostream>
#include <cmath>
#include "utils.h"

double f(double x) {
    return pow((sin(2 * x) + 4 * pow(x, 2) + 3 * x), 2);
}

double gauss_legendre_4pontos(double xi, double xf) {
    double a1 = sqrt((3.0 / 7) - (2.0 * sqrt(6.0 / 5)/7));
    double a2 = -sqrt((3.0 / 7) - (2.0 * sqrt(6.0 / 5)/7));
    double a3 = sqrt((3.0 / 7) + (2.0 * sqrt(6.0 / 5)/7));
    double a4 = -sqrt((3.0 / 7) + (2.0 * sqrt(6.0 / 5)/7));

    double w1 = (18 + sqrt(30.0)) / 36;
    double w2 = (18 + sqrt(30.0)) / 36;
    double w3 = (18 - sqrt(30.0)) / 36;
    double w4 = (18 - sqrt(30.0)) / 36;

    return ((xf - xi) / 2) * (f(((xf - xi) / 2) * a1 + ((xf + xi) / 2)) * w1 +
                              f(((xf - xi) / 2) * a2 + ((xf + xi) / 2)) * w2 +
                              f(((xf - xi) / 2) * a3 + ((xf + xi) / 2)) * w3 +
                              f(((xf - xi) / 2) * a4 + ((xf + xi) / 2)) * w4);
}

double gauss_legendre_3pontos(double xi, double xf) {
    double a1 = -sqrt(3.0 / 5);
    double a2 = 0;
    double a3 = sqrt(3.0 / 5);

    double w1 = 5.0 / 9;
    double w2 = 8.0 / 9;
    double w3 = 5.0 / 9;

    return ((xf - xi) / 2) * (f(((xf - xi) / 2) * a1 + ((xf + xi) / 2)) * w1 +
                              f(((xf - xi) / 2) * a2 + ((xf + xi) / 2)) * w2 +
                              f(((xf - xi) / 2) * a3 + ((xf + xi) / 2)) * w3);
}

double gauss_legendre_2pontos(double xi, double xf) {
    double a1 = -sqrt(1.0 / 3);
    double a2 = sqrt(1.0 / 3);

    double w1 = 1;
    double w2 = 1;

    return ((xf - xi) / 2) * (f(((xf - xi) / 2) * a1 + ((xf + xi) / 2)) * w1 +
                              f(((xf - xi) / 2) * a2 + ((xf + xi) / 2)) * w2);
}

void integracao(double a, double b, double epsilon, int ponto) {
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
            if (ponto == 0) {
                res_atual += gauss_legendre_2pontos(xi, xf);
            } else if (ponto == 1) {
                res_atual += gauss_legendre_3pontos(xi, xf);
            } else if (ponto == 2) {
                res_atual += gauss_legendre_4pontos(xi, xf);
            }
        }

        std::cout << "---------------------------------------------" << std::endl;
        std::cout << "          Interação: " << interacao << std::endl;
        std::cout << "          Resultado: " << res_atual << std::endl;
        std::cout << "---------------------------------------------" << std::endl;

        N *= 2;
        res_ant = res;
        res = res_atual;
        erro = std::abs(res - res_ant);

        if (erro < epsilon || interacao >= 25) {
            integ = false;
        }
    }
}