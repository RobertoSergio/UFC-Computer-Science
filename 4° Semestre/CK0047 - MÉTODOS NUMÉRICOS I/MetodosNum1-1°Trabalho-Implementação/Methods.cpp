#include "Methods.h"
#include "Format.h"

const int MAXIMO_ITERACOES = 100;

double funcao(double d, double a) { return a * exp(d) - 4 * d * d; }
double derivada(double d, double a) { return a * exp(d) - 8 * d; }

std::pair<double, std::map<int, std::vector<double>>>
newton_raphson(double a, double x0, double epsilon1, double epsilon2) {
  std::map<int, std::vector<double>>
      M_newton_raphson; // indexado pela interação
  int k = 0;
  double fx = funcao(x0, a);
  double fpx = derivada(x0, a);

  M_newton_raphson.insert(
      std::pair<int, std::vector<double>>(k, {x0, fx, fpx, x0}));

  if (std::abs(fx) < epsilon1) { // condição inicial
    imprime_iteracao(k, x0, fx, epsilon1);
    return std::make_pair(x0, M_newton_raphson);
  }

  while (true) {
    k++;
    double fx = funcao(x0, a);
    double fpx = derivada(x0, a);
    double x = x0 - fx / fpx;

    double erro_relativo = std::abs(x - x0) / std::abs(x0);
    imprime_iteracao(k, x, fx, erro_relativo);

    M_newton_raphson.insert(std::pair<int, std::vector<double>>(
        k, {x0, a, fx, fpx, erro_relativo}));

    if (std::abs(fx) < epsilon1 || std::abs(x - x0) < epsilon2 ||
        k > MAXIMO_ITERACOES) { // Condições de parada
      return std::make_pair(x, M_newton_raphson);
    }

    x0 = x;
  }
}

std::pair<double, std::map<int, std::vector<double>>>
newton_modificado(double a, double x0, double epsilon1, double epsilon2) {
  std::map<int, std::vector<double>> M_newton_raphson_mod;
  int k = 0;
  double x = x0;
  double x2 = x;

  // A derivada é sempre calculada com o valor de x0.
  double fpx = derivada(x0, a);
  double fx0 = funcao(x0, a);

  M_newton_raphson_mod.insert(
      std::pair<int, std::vector<double>>(k, {x, x2, fpx, fx0, x}));

  if (fpx == 0) { // Derivada de x0 não pode ser 0 (divisão por 0)
    std::cout << "Derivada de " << x0 << " não pode ser 0.";
    std::cout << x0;
  }
  if (std::abs(fx0) < epsilon1) { // condição inicial
    imprime_iteracao(k, x0, fx0, epsilon1);
    return std::make_pair(x0, M_newton_raphson_mod);
  }

  while (true) {
    k++;
    double fx = funcao(x, a);
    x = x - fx / fpx;

    double erro_relativo = std::abs(x2 - x) / std::abs(x);
    imprime_iteracao(k, x, fx, erro_relativo);

    M_newton_raphson_mod.insert(std::pair<int, std::vector<double>>(
        k, {x, x2, fx, fx0, erro_relativo}));

    if (std::abs(fx) < epsilon1 || std::abs(x - x2) < epsilon2 ||
        k > MAXIMO_ITERACOES) { // Condições de parada
      return std::make_pair(x, M_newton_raphson_mod);
    }

    x2 = x;
  }
}

std::pair<double, std::map<int, std::vector<double>>>
secante(double a, double x0, double x1, double epsilon1, double epsilon2) {
  std::map<int, std::vector<double>> M_secante;

  int k = 0;
  double fx0 = funcao(x0, a);
  double fx1 = funcao(x1, a);

  if (std::abs(fx0) < epsilon1) {
    imprime_iteracao(k, x0, fx0, 0);
    return std::make_pair(x0, M_secante);
  }

  if (std::abs(fx1) < epsilon1 || std::abs(x1 - x0) < epsilon2) {

    double erro_relativo = std::abs(x1 - x0) / std::abs(x1);
    imprime_iteracao(k, x1, fx1, erro_relativo);

    return std::make_pair(x1, M_secante);
  }

  while (true) {
    k++;
    double fx0 = funcao(x0, a);
    double fx1 = funcao(x1, a);

    double x2 = x1 - (fx1 * (x1 - x0)) / (fx1 - fx0);

    double erro_relativo = std::abs(x1 - x0) / std::abs(x1);
    M_secante.insert(
        std::pair<int, std::vector<double>>(k, {x0,fx0,x1, fx1, erro_relativo}));

    std::cout << "Iteração " << k << ":\n";
    std::cout << "x" << k << " = " << x2 << ", f(x" << k
              << ") = " << funcao(x2, a)
              << ", Erro Relativo = " << erro_relativo << std::endl;

    if (std::abs(funcao(x2, a)) < epsilon1 || std::abs(x2 - x1) < epsilon2 ||
        k > MAXIMO_ITERACOES) { // Condições de parada
      return std::make_pair(x2, M_secante);
    }

    x0 = x1;
    x1 = x2;
  }

  return std::make_pair(x1, M_secante);
}