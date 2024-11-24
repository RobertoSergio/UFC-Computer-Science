#include "Diretorio.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

Diretorio::Diretorio(int PG) {
  fstream registros;
  fstream buckets;

  registros.open("diretorio.txt", ios::out);

  registros << PG << endl;
  this->registros.push_back(to_string(PG));
  
  int iterator = pow(2, PG);

  for (int i = 0; i < iterator; i++) {
    registros << i << "," << PG << endl;
    this->registros.push_back(to_string(i) + "," + to_string(PG));
  }

  registros.close();

  for (int i = 0; i < iterator; i++) {
    buckets.open("buckets/" + to_string(i) + ".txt", ios::out);
    buckets.close();
  }
};

vector<int> Diretorio::inserir_compra(Compras compra) {
  vector<int> retorno;
  int duplica = 0;
  int ano = compra.ano;
  int PG = stoi(this->registros[0]);
  int hash_function = ano & ((1 << PG) - 1);
  string registro = this->registros[hash_function + 1];
  int k = registro.find_first_of(",");
  int ponteiro = stoi(registro.substr(0, k));
  int PL = stoi(registro.substr(k + 1, 1));
  int novo_PL = PL;

  if (PL != PG) {
    int aux1 = pow(2, PG - 1);
    int aux2 = pow(2, PL);

    while (aux2 < ponteiro) {
      ponteiro = ponteiro - aux1;
      aux1 = aux1 / 2;
    }
  }

  Bucket bucket(to_string(ponteiro));

  int aux = bucket.adicionar_compra(compra.Pedido, compra.valor, compra.ano);

  if (aux == 1) {
    if (PL == PG) {
      this->duplicar_diretorio(PG);
      duplica = 1;
    }
    novo_PL = this->duplicar_bucket(PL, ponteiro);
    this->inserir_compra(compra);
  }
  
  retorno.push_back(duplica);
  retorno.push_back(novo_PL);
  return retorno;
}

int Diretorio::buscar_compra(int ano) {
  int PG = stoi(this->registros[0]);
  int hash_function = ano & ((1 << PG) - 1);
  string registro = this->registros[hash_function + 1];
  int k = registro.find_first_of(",");
  int ponteiro = stoi(registro.substr(0, k));
  int PL = stoi(registro.substr(k + 1, 1));

  if (PL != PG) {
    int aux1 = pow(2, PG - 1);
    int aux2 = pow(2, PL);

    while (aux2 < ponteiro) {
      ponteiro = ponteiro - aux1;
      aux1 = aux1 / 2;
    }
  }

  Bucket bucket(to_string(ponteiro));

  int quantidade = bucket.buscar_compra(ano);

  return quantidade;
}

vector<int> Diretorio::remover_compra(int ano) {
  vector <int> retorno;
  int PG = stoi(this->registros[0]);
  int hash_function = ano & ((1 << PG) - 1);
  string registro = this->registros[hash_function + 1];
  int k = registro.find_first_of(",");
  int ponteiro = stoi(registro.substr(0, k));
  int PL = stoi(registro.substr(k + 1, 1));

  if (PL != PG) {
    int aux1 = pow(2, PG - 1);
    int aux2 = pow(2, PL);

    while (aux2 < ponteiro) {
      ponteiro = ponteiro - aux1;
      aux1 = aux1 / 2;
    }
  }

  Bucket bucket(to_string(ponteiro));
  int quantidade = bucket.remover_compra(ano);
  retorno.push_back(quantidade);
  retorno.push_back(PL);
  return retorno;
}

void Diretorio::duplicar_diretorio(int PG) {
  fstream registros;
  
  int iterator = pow(2, PG+1);

  this->registros[0]=to_string(PG+1);
  
  for (int i = pow(2,PG) ; i < iterator; i++){
    int aux = i - pow(2,PG);
    string linha_correspondente = this->registros[aux+1];
    int k1 = linha_correspondente.find(",");
    int PL = stoi(linha_correspondente.substr(k1 + 1));
    this->registros.push_back(to_string(i) + "," + to_string(PL));
  }
  registros.open("diretorio.txt", ios::out);
  for (int i = 0; i < this->registros.size(); i++){
    registros << this->registros[i] << endl;
  }
  registros.close();
}

int Diretorio::duplicar_bucket(int PL, int ponteiro){
  int ponteiro2 = ponteiro + pow(2, PL);
  string local = "buckets/" + to_string(ponteiro) + ".txt";
  int novo_PL = PL + 1;
  fstream diretorio;

  registros[ponteiro + 1] = to_string(ponteiro) + "," + to_string(novo_PL);

  registros[ponteiro2 + 1] = to_string(ponteiro2) + "," + to_string(novo_PL);

  ponteiro2 = ponteiro2 + pow(2, PL +1);

  while (ponteiro2 < pow(2, stoi(registros[0].substr(0, 1)))) {
    registros[ponteiro2 + 1] = to_string(ponteiro2) + "," + to_string(novo_PL);
  }

  diretorio.open("diretorio.txt", ios::out);
  for (const auto &registro : registros) {
    diretorio << registro << endl;
  }
  diretorio.close();

  Bucket bucket(to_string(ponteiro));
  fstream arq;
  arq.open(local, ios::out);
  arq.close();

  this->inserir_compra(bucket.compras[0]);
  this->inserir_compra(bucket.compras[1]);
  this->inserir_compra(bucket.compras[2]);
  return novo_PL;
}