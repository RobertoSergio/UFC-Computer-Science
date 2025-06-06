#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Bucket.h"
#include <fstream>

using namespace std;

Bucket::Bucket(string ponteiro) {
  this->ponteiro = ponteiro;
  fstream bucket;
  string compra;
  string local = "buckets/" + ponteiro + ".txt";
  int k1;
  int k2;
  string pedido;
  string valor;
  string ano;
  bucket.open(local, ios::in);

  while(!bucket.eof() && getline(bucket, compra)){
    k1 = compra.find_first_of(",");
    k2 = compra.find_last_of(",");
    pedido = compra.substr(0, k1);
    valor = compra.substr(k1 + 1, k2 - k1 - 1);
    ano = compra.substr(k2 + 1, 4);
    Compras compra(stoi(pedido), stod(valor), stoi(ano));
    this->compras.push_back(compra);
  }

  bucket.close();
};

bool Bucket::bucket_is_full(){
  return compras.size() == 3;
}

int Bucket::adicionar_compra(int Pedido, double valor, int ano){{
    fstream bucket;
    string local = "buckets/" + ponteiro + ".txt";
    if (bucket_is_full()) {
      return 1;
    } else {
      compras.push_back(Compras(Pedido, valor, ano));
      bucket.open(local, ios::out);
      for (const auto &compra : this->compras){
        bucket << compra.Pedido << "," << compra.valor << "," << compra.ano << endl;
      }
      bucket.close();
      return 0;
    }
  }
}

int Bucket::buscar_compra(int ano){
  int total = 0;
  for (const auto &compra : this->compras) {
    if (compra.ano == ano) {
      total = total + 1;
    }
  }
  return total;
}

int Bucket::remover_compra(int ano){
  int total = 0;
  fstream bucket;
  string local = "buckets/" + ponteiro + ".txt";
  bucket.open(local, ios::out);
  for (int i = 0; i != compras.size(); ++i){
    if (compras[i].ano != ano) {
      bucket << compras[i].Pedido << "," << compras[i].valor << "," << compras[i].ano << endl;
    } else {
      total = total + 1;
    }
  }
  
  bucket.close(); 
  return total;
}

void Bucket::duplicar(int PL, int ponteiro){
  int ponteiro2 = ponteiro + pow(2, PL);
  int novo_PL = PL + 1;
  fstream diretorio;
  diretorio.open("diretorio.txt", ios::in);

  vector<string> registros;
  string registro;
  while (!diretorio.eof()) {
    getline(diretorio, registro);
    registros.push_back(registro);
  }
  
  diretorio.close();

  registros[ponteiro + 1] = to_string(ponteiro) + "," + to_string(novo_PL);

  registros[ponteiro2 + 1] = to_string(ponteiro) + "," + to_string(novo_PL);

  ponteiro2 = ponteiro2 + pow(2, PL +1);

  while (ponteiro2 < pow(2, stoi(registros[0].substr(0, 1)))) {
    registros[ponteiro2 + 1] = to_string(ponteiro) + "," + to_string(novo_PL);
  }

  diretorio.open("diretorio", ios::out);
  
}