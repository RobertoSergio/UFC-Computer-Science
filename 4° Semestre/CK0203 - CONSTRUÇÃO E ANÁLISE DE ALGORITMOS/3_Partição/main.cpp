#include <iostream>
#include <vector>

using namespace std;

// Função de partição
pair<int, int> particao(vector<int>& V, int pivot, int pivot2) {
    int j = 1;
    int k = V.size() - 1;

    while (j <= k) {
        if (V[j] > pivot && V[k] <= pivot) {
            swap(V[j], V[k]);
        }

        if (V[j] <= pivot) {
            j++;
        }
        if (V[k] > pivot) {
            k--;
        }
    }

    swap(V[0], V[k]);
    int p1 = k;
    j = k;
    k = V.size() - 1;

    while (j <= k) {
        if (V[j] > pivot2 && V[k] <= pivot2) {
            swap(V[j], V[k]);
        }

        if (V[j] <= pivot2) {
            j++;
        }
        if (V[k] > pivot2) {
            k--;
        }
    }

    swap(V[p1 + 1], V[k]);
    return {p1, k};
}

// Função de três partições
pair<int, int> tres_particao(vector<int>& V, vector<int>& l1, vector<int>& l2, vector<int>& l3) {
    int i = 0;

    if (V[0] > V[1]) {
        swap(V[0], V[1]);
    }
    int p1 = V[0];
    int p2 = V[1];

    pair<int, int> posicoes = particao(V, p1, p2);

    while (i < posicoes.first) {
        l1.push_back(V[i]);
        i++;
    }
    int j = posicoes.first;
    while (j < posicoes.second) {
        l2.push_back(V[j]);
        j++;
    }
    int k = posicoes.second;
    while (k < V.size()) {
        l3.push_back(V[k]);
        k++;
    }
    return posicoes;
}

int main() {
    vector<int> lista_desordenada = {23, 15, 37, 10, 14, 33, 13, 29, 16, 22, 24, 8};
    vector<int> lista1, lista2, lista3;

    cout << "Original:";
    for (int num : lista_desordenada) {
        cout << " " << num;
    }
    cout << endl;

    tres_particao(lista_desordenada, lista1, lista2, lista3);

    cout << "Ordenada:";
    for (int num : lista_desordenada) {
        cout << " " << num;
    }
    cout << endl;

    cout << "Menor que P1:";
    for (int num : lista1) {
        cout << " " << num;
    }
    cout << endl;

    cout << "Entre P1 e P2:";
    for (int num : lista2) {
        cout << " " << num;
    }
    cout << endl;

    cout << "Maior que P2:";
    for (int num : lista3) {
        cout << " " << num;
    }
    cout << endl;

    return 0;
}
