#include <iostream>
#include <vector>

using namespace std;

vector<int> instala_antenas(const vector<int>& vilarejos) {
    // Inicializações
    int ini = vilarejos[0];  // Posição inicial do primeiro vilarejo
    vector<int> antenas = {ini + 4};  // A primeira antena é instalada a 4 km da posição inicial
    int alcance = ini + 8;  // O alcance da primeira antena é de 8 km (4 km para cada lado)
    int antenas_instaladas = 1;  // Contador de antenas instaladas

    // Itera sobre os vilarejos
    for (int vila : vilarejos) {
        // Se a vila estiver dentro do alcance, continua para a próxima vila
        if (vila < alcance) {
            continue;
        }

        // Adiciona uma antena 4 km após a posição do vilarejo
        antenas.push_back(vila + 4);
        antenas_instaladas++;
        alcance = vila + 8;  // Atualiza o alcance da antena
    }

    return antenas;
}

int main() {
    vector<int> vilarejos = {1, 6, 10, 14, 20, 25};
    vector<int> antenas_instaladas = instala_antenas(vilarejos);

    cout << "Localizações das antenas: ";
    for (int antena : antenas_instaladas) {
        cout << antena << " ";
    }
    cout << endl;

    return 0;
}
