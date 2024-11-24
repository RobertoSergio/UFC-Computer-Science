#include <fstream>
#include <iostream>
#include "Compras.h"
#include <vector>
using namespace std;

class Bucket {
public:
  vector<Compras> compras;
  string ponteiro;

  Bucket(string ponteiro);

  bool bucket_is_full();

  int adicionar_compra(int Pedido, double valor, int ano);

  int buscar_compra(int ano);

  int remover_compra(int ano);

  void duplicar(int PL, int ponteiro);
};