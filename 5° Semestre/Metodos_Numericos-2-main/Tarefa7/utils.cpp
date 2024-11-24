#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "utils.h"

using namespace std;

double problema1_exponecial_dupla(double s) {
    const double PI = 3.141592653589793;
    double sinh_s = sinh(s);
    double tanh_term = tanh(PI / 2 * sinh_s);
    double cosh_s = cosh(s);
    double cosh_term = cosh(PI / 2 * sinh_s);

    double numerator = (PI / 2) * cosh_s;
    double denominator = pow(cosh_term, 2) * cbrt(pow(tanh_term, 2.0));

    double result = numerator / denominator;
    return result;
}

double problema1_exponecial_simples(double s) {
    double tanh_s = tanh(s);
    double cosh_s = cosh(s);

    double resultado = 1.0 / (cbrt(pow(tanh_s, 2.0))) * 1.0 / (pow(cosh_s, 2));
    return resultado;
}

double problema2_exponecial_dupla(double s) {
    double pi = 3.141592653589793;
    double sinh_s = sinh(s);
    double tanh_term = tanh(pi / 2 * sinh_s);
    double cosh_s = cosh(s);
    double cosh_term = cosh(pi / 2 * sinh_s);

    double term1 = sqrt(4 - pow(-1 + tanh_term, 2));
    double term2 = (pi / 2) * cosh_s / pow(cosh_term, 2);

    double result = 1.0 / term1 * term2;
    return result;
}

double problema2_exponecial_simples(double s) {
    double tanh_s = tanh(s);
    double cosh_s = cosh(s);

    double term1 = sqrt(4 - pow(- 1 + tanh_s, 2));
    double term2 = pow(cosh_s, 2);

    double result = 1.0 / term1 * 1.0 / term2;
    return result;
}


void integracao(double a, double b, double epsilon, int problema, int forma, int grau) {
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
            if(problema==1){
                if(forma==1){
                    if (grau == 2) {
                        res_atual += gauss_legendre_2pontos(xi, xf, problema1_exponecial_simples);
                    } else if (grau == 3) {
                        res_atual += gauss_legendre_3pontos(xi, xf, problema1_exponecial_simples);
                    } else if (grau== 4) {
                        res_atual += gauss_legendre_4pontos(xi, xf, problema1_exponecial_simples);
                    }
                }
                else if (forma == 2){
                    if (grau == 2) {
                        res_atual += gauss_legendre_2pontos(xi, xf, problema1_exponecial_dupla);
                    } else if (grau == 3) {
                        res_atual += gauss_legendre_3pontos(xi, xf, problema1_exponecial_dupla);
                    } else if (grau== 4) {
                        res_atual += gauss_legendre_4pontos(xi, xf, problema1_exponecial_dupla);
                    }
                }
            }
            else if(problema==2){
                if(forma==1){
                    if (grau == 2) {
                        res_atual += gauss_legendre_2pontos(xi, xf, problema2_exponecial_simples);
                    } else if (grau == 3) {
                        res_atual += gauss_legendre_3pontos(xi, xf, problema2_exponecial_simples);
                    } else if (grau== 4) {
                        res_atual += gauss_legendre_4pontos(xi, xf, problema2_exponecial_simples);
                    }
                }
                else if (forma == 2){
                    if (grau == 2) {
                        res_atual += gauss_legendre_2pontos(xi, xf, problema2_exponecial_dupla);
                    } else if (grau == 3) {
                        res_atual += gauss_legendre_3pontos(xi, xf, problema2_exponecial_dupla);
                    } else if (grau== 4) {
                        res_atual += gauss_legendre_4pontos(xi, xf, problema2_exponecial_dupla);
                    }
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

        if (erro < epsilon || interacao >= 21 || isnan(res_atual)) {
            integ = false;
        }
    }
}

double gauss_legendre_4pontos(double xi, double xf, double (*func)(double)) {
    double a1 = sqrt((3.0 / 7) - (2.0 * sqrt(6.0 / 5) / 7));
    double a2 = -sqrt((3.0 / 7) - (2.0 * sqrt(6.0 / 5) / 7));
    double a3 = sqrt((3.0 / 7) + (2.0 * sqrt(6.0 / 5) / 7));
    double a4 = -sqrt((3.0 / 7) + (2.0 * sqrt(6.0 / 5) / 7));

    double w1 = (18 + sqrt(30.0)) / 36;
    double w2 = (18 + sqrt(30.0)) / 36;
    double w3 = (18 - sqrt(30.0)) / 36;
    double w4 = (18 - sqrt(30.0)) / 36;

    return ((xf - xi) / 2) * (func(((xf - xi) / 2) * a1 + ((xf + xi) / 2)) * w1 +
                              func(((xf - xi) / 2) * a2 + ((xf + xi) / 2)) * w2 +
                              func(((xf - xi) / 2) * a3 + ((xf + xi) / 2)) * w3 +
                              func(((xf - xi) / 2) * a4 + ((xf + xi) / 2)) * w4);
}

double gauss_legendre_3pontos(double xi, double xf, double (*func)(double)) {
    double a1 = -sqrt(3.0 / 5);
    double a2 = 0;
    double a3 = sqrt(3.0 / 5);

    double w1 = 5.0 / 9;
    double w2 = 8.0 / 9;
    double w3 = 5.0 / 9;

    return ((xf - xi) / 2) * (func(((xf - xi) / 2) * a1 + ((xf + xi) / 2)) * w1 +
                              func(((xf - xi) / 2) * a2 + ((xf + xi) / 2)) * w2 +
                              func(((xf - xi) / 2) * a3 + ((xf + xi) / 2)) * w3);
}

double gauss_legendre_2pontos(double xi, double xf, double (*func)(double)) {
    double a1 = -sqrt(1.0 / 3);
    double a2 = sqrt(1.0 / 3);

    double w1 = 1;
    double w2 = 1;

    return ((xf - xi) / 2) * (func(((xf - xi) / 2) * a1 + ((xf + xi) / 2)) * w1 +
                              func(((xf - xi) / 2) * a2 + ((xf + xi) / 2)) * w2);
}

double abordagem_aberta_grau3(double xi, double xf, double (*func)(double)) {
    double h = (xf - xi) / 5;
    return (5 * h / 24) * (11 * func(xi) + func(xi + h) + func(xi + 2 * h) + 11 * func(xi + 3 * h));
}

double abordagem_fechada_grau3(double xi, double xf, double (*func)(double)) {
    double h = (xf - xi) / 3;
    return (3 * h / 8) * (func(xi) + 3 * func(xi + h) + 3 * func(xi + 2 * h) + func(xi + 3 * h));
}