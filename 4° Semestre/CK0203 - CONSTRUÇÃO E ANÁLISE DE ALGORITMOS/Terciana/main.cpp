#include <iostream>
#include <vector>

using namespace std;

// Função de partição
int particao(vector<int>& L, int inicio, int fim, int pivot) {
    // Move o elemento pivot para a posição inicial
    swap(L[inicio], L[pivot]);
    int pivot_value = L[inicio];

    // Inicializa os índices i e k
    int i = inicio + 1;
    int k = fim;

    // Executa a partição
    while (i <= k) {
        // Troca os elementos se necessário
        if (L[i] > pivot_value && L[k] <= pivot_value) {
            swap(L[i], L[k]);
        }

        // Incrementa i se o elemento em L[i] é menor ou igual ao pivot
        if (L[i] <= pivot_value) {
            i++;
        }

        // Decrementa k se o elemento em L[k] é maior que o pivot
        if (L[k] > pivot_value) {
            k--;
        }
    }

    // Move o pivot para a posição correta na partição
    swap(L[inicio], L[k]);
    return k;
}

// Função para encontrar o elemento da terciana
int encontrar_terciana(vector<int>& L, int inicio, int fim) {
    // Se o intervalo tem apenas um elemento, retorna esse elemento
    if (inicio == fim) {
        return L[inicio];
    }

    // Calcula o índice do pivot para a terciana
    int terci = inicio + (fim - inicio) / 3;

    // Obtém o índice após particionar a lista
    int pivot_index = particao(L, inicio, fim, terci);

    // Verifica se o pivot está na posição correta para a terciana
    if (pivot_index == (L.size() / 3)) {
        return L[pivot_index];
    } else if (pivot_index > (L.size() / 3)) {
        // Se o pivot está à direita da terciana, busca na sublista à esquerda
        return encontrar_terciana(L, inicio, pivot_index - 1);
    } else {
        // Se o pivot está à esquerda da terciana, busca na sublista à direita
        return encontrar_terciana(L, pivot_index + 1, fim);
    }
}

int main() {
    // Exemplo de uso
    vector<int> L = {9, 3, 11, 7, 1, 6, 2, 8, 5};
    int n = L.size();
    int resultado = encontrar_terciana(L, 0, n - 1);
    cout << resultado << endl;

    return 0;
}
