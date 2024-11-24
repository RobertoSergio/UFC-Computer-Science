#include <vector>
#include <string>
#include "Bucket.h"

using namespace std;

class Diretorio {
  public:
    vector<string> registros;

    Diretorio(int PG);

    vector<int> inserir_compra(Compras compra);

    int buscar_compra(int ano);

    vector<int> remover_compra(int ano);

    void duplicar_diretorio(int PG);

    int duplicar_bucket(int PL, int ponteiro);
};