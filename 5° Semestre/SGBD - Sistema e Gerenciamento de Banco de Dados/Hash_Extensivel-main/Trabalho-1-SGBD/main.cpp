#include "Diretorio.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main() {
  mkdir("buckets", 0777);
  fstream csv;
  vector<Compras> compras;
  csv.open("compras.csv", ios::in);
  string linha;
  int k1;
  int k2;
  string pedido;
  string valor;
  string ano;
  while (!csv.eof()) {
    getline(csv, linha);
    k1 = linha.find_first_of(",");
    k2 = linha.find_last_of(",");
    pedido = linha.substr(0, k1);
    valor = linha.substr(k1 + 1, k2 - k1 - 1);
    ano = linha.substr(k2 + 1, 4);
    Compras compra(stoi(pedido), stod(valor), stoi(ano));
    compras.push_back(compra);
  }

  ifstream arquivo_entrada("in.txt");
  ofstream arquivo_saida("out.txt");
  int profundidade_global;
  
  getline(arquivo_entrada, linha);
  profundidade_global = std::stoi(linha.substr(3));
  arquivo_saida << "PG/" << profundidade_global << endl;
  
  Diretorio diretorio(profundidade_global);
  while (getline(arquivo_entrada, linha)) {
    if (linha.substr(0, 3) == "INC") {
      int ano1 = stoi(linha.substr(4));
      int profundidade_local, aux;
      for(int i = 0; i < compras.size(); i++){
        if(compras[i].ano == ano1){
          vector <int> retorno = diretorio.inserir_compra(compras[i]);
          aux = retorno[0];
          profundidade_local = retorno[1];
          arquivo_saida << "INC:" << compras[i].ano << "/" << diretorio.registros[0][0] << "," << profundidade_local << endl;
        }
        if(aux == 1){
          arquivo_saida << "DUP_DIR:/" << diretorio.registros[0][0] << "," << profundidade_local << endl;
          aux = 0;
        }
      }
    } 
    else if (linha.substr(0, 3) == "REM") {
      int ano1 = stoi(linha.substr(4));
      int tuplas_removidas, profundidade_local;
      vector <int> retorno = diretorio.remover_compra(ano1);
      tuplas_removidas = retorno[0];
      profundidade_local = retorno[1];
      arquivo_saida << "REM:" << ano1 << "/" << tuplas_removidas << "," << profundidade_local << endl;
    } 
    else if (linha.substr(0, 3) == "BUS") {
      int ano1 = stoi(linha.substr(5));
      int qtd_tuplas_selecionadas;
      qtd_tuplas_selecionadas = diretorio.buscar_compra(ano1);
      arquivo_saida << "BUS:" << ano1 << "/" << qtd_tuplas_selecionadas << endl;
    }
  }
  arquivo_saida << "P:/" << diretorio.registros[0][0]  << endl;
  
  arquivo_entrada.close();
  arquivo_saida.close();
  return 0;
 }