#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

void imprime_matriz(vector<vector<double>> &M, int n);
void imprime_matriz2(vector<vector<double>> &M, int n);
void imprime_e_copia_matriz(vector<vector<double>> &M,
                            vector<vector<double>> &M_copia, int n);
void imprime_e_copia_vetor(vector<double> &v, vector<double> &v_copia, int n);
void imprime_vetor(vector<double> &v, int n);
bool imprime_resultado_final_com_limite(vector<double> &resultado, int n);
void imprime_conclusao(bool explodiu, string metodo);
void cria_matriz(vector<vector<double>> &A, int n);
vector<double> multiplica_matriz_por_vetor(const vector<vector<double>> &matrix,
                                           const vector<double> &vec, int n);
vector<vector<double>> calcula_inversa(int n, vector<vector<double>> A);
double calcula_norma(int n, vector<double> &x, vector<double> &v);
vector<double> gauss_jacobi(int n, vector<vector<double>> &A, vector<double> &d,
                            vector<double> &v, double epsilon, int iterMax);
vector<double> gauss_seidel(int n, vector<vector<double>> &A, vector<double> &d,
                            vector<double> &v, double epsilon, int iterMax);
void quadro_resposta(int n, int q, vector<vector<vector<double>>> &lista_matrizes, vector<vector<double>> &lista_jacobis, vector<vector<double>> &lista_seidels);
void item_e();