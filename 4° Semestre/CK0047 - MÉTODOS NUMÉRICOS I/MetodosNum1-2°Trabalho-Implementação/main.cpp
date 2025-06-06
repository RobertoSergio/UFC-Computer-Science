/* 
2o Trabalho de Métodos Numéricos I - Sistemas de Equações
Em um fenômeno da natureza os deslocamentos d1, d2,..., dn encontrados são dados pela solução do sistema de
equações lineares Ad = b, onde A é a matriz das propriedades, d é o vetor das incógnitas e b é o vetor dos
termos independentes (vetor constante). Caso um desses deslocamentos passe de 0,4 cm, em módulo, podem
ocorrer sérios danos e um problema gigantesco. Uma das soluções possíveis para achar o vetor d é através da
inversa de A (d = (A^-1)b). 
Se A é uma matriz nxn que possui como inversa uma matriz A^-1 então AA^-1 = I, onde I é a matriz Identidade, 
e uma maneira de se achar A^-1 é achar se as colunas de A^-1 uma por vez, através de A(A^-1)1 = {1 0 ... 0}T , 
A(A^-1)2 = {0 1 ... 0}T ... A(A^-1)n = {0 0 ... 1}T, onde (A^-1)1, (A^-1)2 ... (A^-1)n são as n colunas de A^-1. 
Desenvolva um sistema para calcular deslocamentos ds dessas partes com os requisitos abaixo:

a) Implementar algoritmo para calcular A^-1 e depois {d} pelo método de Gauss-Jacobi.
b) Implementar algoritmo para calcular A^-1 e depois {d} pelo método de Gauss-Seidel.
c) Calibrar o sistema feito usando como padrão matriz [A] e vetor {b} dados abaixo.
d) Fornecer um quadro resposta para cada método, variando os valores de [A] e de {b}.
e) Analisar o que vai acontecer nesse fenômeno, para esse sistema mencionado abaixo. 

Dados de entrada: n (número de deslocamentos), termos de [A]nxn e de {b}nx1 e e (precisão).
Dados de saída: A^-1 e os termos de {d}nx1 que representam os n deslocamentos d1, d2,..., dn.

*/

#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "methods.h"

using namespace std;

const int MAXIMO_ITERACOES = 100;
const double Lim = 0.4;

int main() {
  int n, q;
  double epsilon;

  cout << "2o Trabalho de Métodos Numéricos I - Raízes de Equações" << endl;
  cout << "Tema2:" << endl;
  cout << "a) Implementar algoritmo para calcular A^{-1} e depois d pelo "
          "método de Gauss-Jacobi."
       << endl
       << endl;

  cout << "Quantas matrizes deseja testar?" << endl;
  cin >> q;

  cout << "Tamanho n das matrizes nxn:" << endl;
  cin >> n;

  vector<vector<vector<double>>> lista_matrizes(
      q, (vector<vector<double>>(n, vector<double>(n))));

  vector<vector<double>> lista_ds(q, vector<double>(n));

  vector<vector<double>> lista_v0s(q, vector<double>(n));

  vector<double> lista_epsilons(q);

  vector<vector<double>> lista_jacobis(q, vector<double>(n));

  vector<vector<double>> lista_seidels(q, vector<double>(n));

  for (int i = 0; i < q; i++) {
    vector<vector<double>> A(n, vector<double>(n));
    vector<vector<double>> A_copia(n, vector<double>(n));
    vector<vector<double>> A_inversa(n, vector<double>(n));

    cout << "Digite a Matriz A :" << endl;
    cria_matriz(A, n);  

    lista_matrizes[i] = A;

    cout << "Matriz A inserida:" << endl;
    imprime_e_copia_matriz(A, A_copia, n);

    cout << "Digite o vetor das incognitas d:" << endl;
    vector<double> d(n);
    vector<double> d_copia(n); // Alteração aqui, vetor unidimensional

    lista_ds[i] = d;

    for (int k = 0; k < n; ++k) {
      cout << "d[" << k + 1 << "]: ";
      cin >> d[k];
    }
    cout << "Vetor das incognitas d inserido:" << endl;
    imprime_e_copia_vetor(d, d_copia, n);

    cout << "Digite o vetor das incognitas v0:" << endl;
    vector<double> v(n); // Alteração aqui, vetor unidimensional
    vector<double> v_copia(n);
    for (int l = 0; l < n; ++l) {
      cout << "v[" << l + 1 << "]: ";
      cin >> v[l];
    }

    lista_v0s[i] = v;

    cout << "Vetor das incognitas v inserido:" << endl;
    imprime_e_copia_vetor(v, v_copia, n);

    cout << "Digite o valor do Epsilon:" << endl;
    cin >> epsilon;

    lista_epsilons[i] = epsilon;

    cout << endl;
    cout << endl;

    // ------------- Gauss Jordan (Inversa) -------------

    A_inversa = calcula_inversa(n, A);
    cout << "Matriz Inversa calculada:" << endl;
    imprime_matriz(A_inversa, n);

    cout << endl;

    vector<double> solucao_inversa = multiplica_matriz_por_vetor(A_inversa, d, n);

    cout << "Solução do sistema utilizando matriz inversa: " << endl;
    imprime_vetor(solucao_inversa, n);

    // ------------- Gauss Jacobi -------------

    cout << "Para o método de Gauss Jacobi:" << endl;
    vector<double> resultado_jacobi =
        gauss_jacobi(n, A, d, v, epsilon, MAXIMO_ITERACOES);

    lista_jacobis[i] = resultado_jacobi;

    cout << endl << "Resultado final: ";

    cout << endl;
    imprime_resultado_final_com_limite(resultado_jacobi, n);
    cout << endl;

    // ------------- Gauss Seidel -------------

    cout << "Para o método de Gauss Seidel:" << endl;
    vector<double> resultado_seidel =
        gauss_seidel(n, A_copia, d_copia, v_copia, epsilon, MAXIMO_ITERACOES);

    lista_seidels[i] = resultado_seidel;

    cout << endl << "Resultado final: ";

    cout << endl;
    imprime_resultado_final_com_limite(resultado_seidel, n);
    cout << endl;
  }

  cout << "d) Fornecer um quadro resposta para cada método, variando os "
          "valores de [A] e de {b}"
       << endl;
  quadro_resposta(n, q, lista_matrizes, lista_jacobis, lista_seidels);

  item_e();

  return 0;
}