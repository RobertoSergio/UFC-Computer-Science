#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>

void imprime_iteracao(int k, double x, double fx, double erro_relativo);
void quadro_resposta(double newton_r, double newton_m, double sec_t);
void customSplit(std::string str, char separator);
void customSplit2(std::string str, char separator);
void imprime_tabela(std::map<int, std::vector<double>> M_1,
                    std::map<int, std::vector<double>> M_2,
                    std::map<int, std::vector<double>> M_3, int x_1, int x_2,
                    int x_3, std::string ordem, std::string cabecalho);