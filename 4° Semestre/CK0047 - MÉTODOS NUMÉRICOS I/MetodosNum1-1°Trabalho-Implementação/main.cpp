#include <iostream>
#include "Format.h"
#include "Methods.h"

int main() {
  std::cout << "1o Trabalho de Métodos Numéricos I - Raízes de Equações \n";
  std::cout << "Tema2:\n";
  double newton_r, newton_m, sec_t;
  std::pair<double, std::map<int, std::vector<double>>> par_newton;
  std::pair<double, std::map<int, std::vector<double>>> par_newton_mod;
  std::pair<double, std::map<int, std::vector<double>>> par_secante;
  std::map<int, std::vector<double>> M_newton_raphson;
  std::map<int, std::vector<double>> M_newton_raphson_mod;
  std::map<int, std::vector<double>> M_secante;

  int n;
  std::cout << "Digite o número de valores de 'a': ";
  std::cin >> n;

  std::vector<double> a_values(n);
  for (int i = 0; i < n; i++) {
    std::cout << "Digite o valor de 'a' para o caso " << i + 1 << ": ";
    std::cin >> a_values[i];
  }

  double epsilon1;
  std::cout << "Digite a precisão desejada do double epsilon1: ";
  std::cin >> epsilon1;

  double epsilon2;
  std::cout << "Digite a precisão desejada do double epsilon2: ";
  std::cin >> epsilon2;

  double x0;
  std::cout << "Digite o x0 para os métodos de Newton: ";
  std::cin >> x0;
  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  // Implementação do item a)
  std::cout << "a) Implementar algoritmo para calcular d pelo método da "
               "Newton-Raphson:\n";

  std::cout << "\n";
  for (int i = 0; i < n; i++) {
    std::cout << "\n"
              << "Para o teste " << i + 1 << ":\n";
    double a = a_values[i];
    std::pair<double, std::map<int, std::vector<double>>> par_newton =
        newton_raphson(a, x0, epsilon1, epsilon2);
    double d;
    d = par_newton.first;
    newton_r = d;
    std::cout << "\n"
              << "Resultado para 'a' = " << a << ": d = " << d << "\n"
              << "\n";
  }

  std::cout << "\n\n";

  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  // Implementação do item b)
  std::cout << "b) Implementar algoritmo para calcular d pelo método de Newton "
               "modificado:\n";

  std::cout << "\n";
  for (int i = 0; i < n; i++) {
    std::cout << "\n"
              << "Para o teste " << i + 1 << ":\n";
    double a = a_values[i];
    par_newton_mod = newton_modificado(a, x0, epsilon1, epsilon2);
    double d = par_newton_mod.first;
    std::cout << "\n"
              << "Resultado para 'a' = " << a << ": d = " << d << "\n"
              << "\n";
  }

  std::cout << "\n\n";

  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  // Implementação do item c)

  std::cout << "c) Implementar algoritmo para calcular d pelo método da "
               "Secante tradicional:\n";

  std::cout << "Digite o valor de 'x0': ";
  std::cin >> x0;

  double x1;
  std::cout << "Digite o valor de 'x1': ";
  std::cin >> x1;

  std::cout << "\n";
  for (int i = 0; i < n; i++) {
    std::cout << "\n"
              << "Para o teste " << i + 1 << ":\n";
    double a = a_values[i];
    par_secante = secante(a, x0, x1, epsilon1, epsilon2);
    double d = par_secante.first;
    std::cout << "\n"
              << "Resultado para 'a' = " << a << ": d = " << d << "\n"
              << "\n";
  }

  std::cout << "\n\n";
  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  // Implementação do item d)

  std::cout << "d) Testar os resultados para d usando como padrão a = 1, d0 = "
               "0,5 e e = 10^-4:\n";

  std::cout << "Newton_raphson:\n";
  // mudado aqui para receber o par de newton normal
  double d0;
  par_newton = newton_raphson(1, 0.5, 0.0001, 0.0001);
  d0 = par_newton.first;
  newton_r = d0;
  std::cout << "\n\n";
  std::cout << "Newton_modificado:\n";
  par_newton_mod = newton_modificado(1, 0.5, 0.0001, 0.0001);
  double d1 = par_newton_mod.first;
  newton_m = d1;
  std::cout << "\n\n";
  std::cout << "Secante:\n";
  par_secante = secante(1, 0.5, 1.0, 0.0001, 0.0001);
  double d2 = par_secante.first;
  sec_t = d2;
  std::cout << "\n\n";
  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  //-------------------------------------------------------------------
  // Implementação do item e)

  std::cout << "e) Fornecer um quadro resposta, com d calculado para cada "
               "método dado:\n";
  quadro_resposta(newton_r, newton_m, sec_t);

  int x = 0, y = 0, z = 0;
  M_newton_raphson = par_newton.second;
  for (std::map<int, std::vector<double>>::iterator it =
           M_newton_raphson.begin();
       it != M_newton_raphson.end(); ++it) {
    x++;
  }

  M_newton_raphson_mod = par_newton_mod.second;
  for (std::map<int, std::vector<double>>::iterator it =
           M_newton_raphson_mod.begin();
       it != M_newton_raphson_mod.end(); ++it) {
    y++;
  }

  M_secante = par_secante.second;
  for (std::map<int, std::vector<double>>::iterator it = M_secante.begin();
       it != M_secante.end(); ++it) {
    z++;
  }
  if (x > y && y > z) {
    imprime_tabela(M_newton_raphson, M_newton_raphson_mod, M_secante, x, y, z,
                   "newton_raphson: ,newton_raphson_mod: ,secante: ",
                   "x0    fx        fpx    ERx;x   x2    fpx      fx0      ERx;x0  fx0      x1  fx1       ERx");
  } else if (x > y && y < z) {
    imprime_tabela(M_newton_raphson, M_secante, M_newton_raphson_mod, x, z, y,
                   "newton_raphson: ,secante: ,newton_raphson_mod: ",
                   "x0    fx        fpx    ERx;x0  fx0      x1  fx1       ERx;x   x2    fpx      fx0      ERx");
  } else if (z > x && x > y) {
    imprime_tabela(M_secante, M_newton_raphson, M_newton_raphson_mod, z, x, y,
                   "secante: ,newton_raphson: ,newton_raphson_mod: ",
                   "x0  fx0      x1  fx1       ERx;x0    fx        fpx    ERx;x   x2    fpx      fx0      ERx");
  } else if (z > y && y > x) {
    imprime_tabela(
        M_secante, M_newton_raphson_mod, M_newton_raphson, z, y, x,
        "secante: ,newton_raphson_mod: ,newton_raphson: ",
        "x0  fx0      x1  fx1       ERx;x   x2    fpx      fx0      ERx;x0    fx        fpx    ERx;");
  } else if (y > z && z > x) {
    imprime_tabela(M_newton_raphson_mod, M_secante, M_newton_raphson, y, z, x,
                   "newton_raphson_mod: ,secante: ,newton_raphson: ",
                   "x   x2    fpx      fx0      ERx;x0  fx0      x1  fx1       ERx;x0    fx        fpx    ERx");
  } else if (y > x && x > z) {
    imprime_tabela(M_newton_raphson_mod, M_newton_raphson, M_secante, y, x, z,
                   "newton_raphson_mod: ,newton_raphson: ,secante: ",
                   "x   x2    fpx      fx0      ERx;x0    fx        fpx    ERx;x0  fx0      x1  fx1       ERx");
  }
  return 0;
}