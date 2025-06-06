#include <iostream>
#include <cmath>

double f(double x);

double gauss_legendre_4pontos(double xi, double xf);

double gauss_legendre_3pontos(double xi, double xf);

double gauss_legendre_2pontos(double xi, double xf);

void integracao(double a, double b, double epsilon, int ponto);