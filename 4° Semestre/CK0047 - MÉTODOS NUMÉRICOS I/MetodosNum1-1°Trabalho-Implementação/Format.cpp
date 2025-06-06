#include "Format.h"

void imprime_iteracao(int k, double x, double fx, double erro_relativo) {
  std::cout << "Iteração " << k << ":\n";
  std::cout << "d" << k << " = " << x << ", f(d" << k << ") = " << fx
            << ", Erro Relativo = " << erro_relativo << std::endl;
}

void quadro_resposta(double newton_r, double newton_m, double sec_t) {
  std::cout << "\nQUADRO RESPOSTA \n";
  std::cout << "\nRaiz pelo método de Newton-Raphson: " << newton_r;
  std::cout << "\n========================================== \n";
  std::cout << "\nRaiz pelo método de Newton Modificado: " << newton_m;
  std::cout << "\n========================================== \n";
  std::cout << "\nRaiz pelo método da Secante Tradicional: " << sec_t;
  std::cout << "\n========================================== \n";
}

std::vector<std::string> strings;
std::vector<std::string> strings2;
void customSplit(std::string str, char separator) {
  int startIndex = 0, endIndex = 0;
  for (int i = 0; i <= str.size(); i++) {

    // If we reached the end of the word or the end of the input.
    if (str[i] == separator || i == str.size()) {
      endIndex = i;
      std::string temp;
      temp.append(str, startIndex, endIndex - startIndex);
      strings.push_back(temp);
      startIndex = endIndex + 1;
    }
  }
}

void customSplit2(std::string str, char separator) {
  int startIndex = 0, endIndex = 0;
  for (int i = 0; i <= str.size(); i++) {

    // If we reached the end of the word or the end of the input.
    if (str[i] == separator || i == str.size()) {
      endIndex = i;
      std::string temp;
      temp.append(str, startIndex, endIndex - startIndex);
      strings2.push_back(temp);
      startIndex = endIndex + 1;
    }
  }
}

void imprime_tabela(std::map<int, std::vector<double>> M_1,
                    std::map<int, std::vector<double>> M_2,
                    std::map<int, std::vector<double>> M_3, int x_1, int x_2,
                    int x_3, std::string ordem, std::string cabecalho) {
  char separetor(',');
  char separetor2(';');
  customSplit(ordem, separetor);
  std::cout << "\nTABELA DE RESULTADOS \n";

  std::cout << "\n\n" << strings[0];
  customSplit2(cabecalho, separetor2);
  std::cout << "\n" << "                " << strings2[0];
  // para o maior,mais lento
  for (std::map<int, std::vector<double>>::iterator it = M_1.begin();
       it != M_1.end(); ++it) {
    std::cout << "\n"
              << "iteração: " << it->first + 1 << " -> ";
    for (int j = 0; j < it->second.size();
         j++) { // imprime tudo de uma interação
      std::cout << it->second[j] << "| ";
    }
  }

  customSplit(ordem, separetor);
  std::cout << "\n\n" << strings[1];
  customSplit2(cabecalho, separetor2);
  std::cout << "\n" << "                " << strings2[1];
  for (std::map<int, std::vector<double>>::iterator it = M_2.begin();
       it != M_2.end(); ++it) {
    std::cout << "\n"
              << "iteração: " << it->first + 1 << " -> ";
    for (int j = 0; j < it->second.size();
         j++) { // imprime tudo de uma interação
      std::cout << it->second[j] << "| ";
    }
  }

  customSplit(ordem, separetor);
  std::cout << "\n\n" << strings[2];
  customSplit2(cabecalho, separetor2);
  std::cout << "\n" << "                " << strings2[2];
  for (std::map<int, std::vector<double>>::iterator it = M_3.begin();
       it != M_3.end(); ++it) {
    std::cout << "\n"
              << "iteração: " << it->first << " -> ";
    for (int j = 0; j < it->second.size();
         j++) { // imprime tudo de uma interação
      std::cout << it->second[j] << "| ";
    }
  }
}