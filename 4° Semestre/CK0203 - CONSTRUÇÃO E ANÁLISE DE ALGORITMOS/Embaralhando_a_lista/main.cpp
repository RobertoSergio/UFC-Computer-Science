#include <iostream>
#include <vector>

using namespace std;

// Função de embaralhamento
void embaralhar(vector<int>& L, vector<int>& P) {
    int n = L.size();

    // Itera sobre os elementos de L
    for (int i = 0; i < n; ++i) {
        // Verifica se o elemento ainda não foi movido
        if (L[i] >= 0) {
            // Encontra o destino do elemento na permutação P
            int destino = -1;
            for (int j = 0; j < n; ++j) {
                if (P[j] == i) {
                    destino = j;
                    break;
                }
            }

            int origem = i;
            // Realiza a troca de elementos entre as posições origem e destino
            swap(L[origem], L[destino]);
            swap(P[origem], P[destino]);
            // Marca o elemento na posição origem como movido
            L[origem] = -L[origem];
        }
    }

    // Inverte o sinal dos elementos para restaurar seus valores originais
    for (int i = 0; i < n; ++i) {
        L[i] = -L[i];
    }
}

// Função principal
int main() {
    vector<int> L = {9, 3, 5, 8, 0, 7, 1, 6, 2, 4};
    vector<int> P = {5, 7, 0, 8, 1, 4, 3, 9, 2, 6};

    // Exibe a lista antes do embaralhamento
    cout << "Lista original:";
    for (int num : L) {
        cout << " " << num;
    }
    cout << endl;

    // Chama a função de embaralhamento
    embaralhar(L, P);

    // Exibe a lista após o embaralhamento
    cout << "Lista embaralhada:";
    for (int num : L) {
        cout << " " << num;
    }
    cout << endl;

    // Exibe a permutação utilizada no embaralhamento
    cout << "Permutação utilizada:";
    for (int index : P) {
        cout << " " << index;
    }
    cout << endl;

    return 0;
}
