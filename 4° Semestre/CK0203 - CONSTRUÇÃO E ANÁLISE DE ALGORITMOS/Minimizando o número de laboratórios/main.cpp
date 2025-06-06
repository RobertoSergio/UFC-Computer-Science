#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Atividade {
    int inicio, fim;
};

// Função de particionamento para quicksort
int particionar(vector<Atividade>& atividades, int key, int inicio, int fim) {
    int pivot = atividades[(inicio + fim) / 2].inicio; // Escolhe o ponto médio como pivô
    int i = inicio - 1;
    int j = fim + 1;

    while (true) {
        do {
            i++;
        } while (atividades[i].inicio < pivot);

        do {
            j--;
        } while (atividades[j].inicio > pivot);

        if (i >= j) {
            return j;
        }

        swap(atividades[i], atividades[j]);
    }
}

// Função quicksort 
void quicksort(vector<Atividade>& atividades, int key, int inicio, int fim) {
    if (inicio < fim) {
        int p = particionar(atividades, key, inicio, fim);
        quicksort(atividades, key, inicio, p);
        quicksort(atividades, key, p + 1, fim);
    }
}
// função principal para descobrir o máximo de laboratórios que ficaram abertos ao mesmo tempo 
int min_lab(vector<Atividade>& atividades, int n) {
    // Ordena as atividades pelo início usando quicksort
    quicksort(atividades, 0, 0, n - 1);

    vector<int> ati_inicio(n);
    vector<int> ati_fim(n);

    for (int i = 0; i < n; ++i) {
        ati_inicio[i] = atividades[i].inicio;
        ati_fim[i] = atividades[i].fim;
    }

    // Ordena as atividades pelo fim usando quicksort
    quicksort(atividades, 1, 0, n - 1);

    int i = 0, f = 0, max_lab = 0, lab = 0;

    while (i < n && f < n) {
        if (ati_inicio[i] < ati_fim[f]) {
            lab++;
            i++;

            if (lab > max_lab) {
                max_lab = lab;
            }
        } else {
            lab--;
            f++;
        }
    }

    return max_lab;
}

int main() {
    vector<Atividade> atividades = {{1, 3}, {2, 5}, {4, 7}, {6, 9}, {8, 11}};
    int resultado = min_lab(atividades, atividades.size());
    cout << "Maior número de laboratórios abertos ao mesmo tempo é: " << resultado << endl;

    return 0;
}
