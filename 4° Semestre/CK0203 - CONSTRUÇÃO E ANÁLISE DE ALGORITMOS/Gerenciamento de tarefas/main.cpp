#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Declaração antecipada das funções
int maximiza_tempo_ocupado_recursivo(const vector<vector<int>> &atividades, int indice, vector<int> &memo);
int proxima_atividade_sem_conflito(int indice, const vector<vector<int>> &atividades);

// Função para encontrar o próximo índice de atividade que não entra em conflito com a atividade atual
int proxima_atividade_sem_conflito(int indice, const vector<vector<int>>& atividades) {
    int tempo_fim_atual = atividades[indice][1];
    int proximo_indice = indice + 1;

    while (proximo_indice < atividades.size() && atividades[proximo_indice][0] < tempo_fim_atual) {
        proximo_indice++;
    }

    return proximo_indice;
}

// Função principal que inicia a ordenação e chama a função recursiva
int maximiza_tempo_ocupado(const vector<vector<int>>& atividades) {
    // Cria uma cópia das atividades e ordena com base no tempo de início
    vector<vector<int>> sorted_atividades = atividades;
    sort(sorted_atividades.begin(), sorted_atividades.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    });

    // Inicializa a tabela de memorização
    vector<int> memo(atividades.size(), -1);

    // Chama a função recursiva com as atividades ordenadas
    return maximiza_tempo_ocupado_recursivo(sorted_atividades, 0, memo);
}

// Função recursiva que realiza a lógica principal do algoritmo
int maximiza_tempo_ocupado_recursivo(const vector<vector<int>>& atividades, int indice, vector<int>& memo) {
    // Verifica se atingiu o final das atividades
    if (indice >= atividades.size()) {
        return 0;
    }

    // Verifica se o resultado para esta posição já foi calculado e retorna se sim
    if (memo[indice] != -1) {
        return memo[indice];
    }

    // Calcula o tempo total com a atividade atual
    int tempo_com_atividade_atual = atividades[indice][2] + maximiza_tempo_ocupado_recursivo(atividades, proxima_atividade_sem_conflito(indice, atividades), memo);

    // Calcula o tempo total sem a atividade atual
    int tempo_sem_atividade_atual = maximiza_tempo_ocupado_recursivo(atividades, indice + 1, memo);

    // Escolhe a opção que maximiza o tempo total
    int resultado = max(tempo_com_atividade_atual, tempo_sem_atividade_atual);

    // Armazena o resultado na tabela de memorização
    memo[indice] = resultado;

    // Retorna o resultado
    return resultado;
}

// Função principal do programa
int main() {
    // Definição das atividades
    vector<vector<int>> atividades = {
        {1, 3, 2},  // Atividade A
        {2, 5, 3},  // Atividade B
        {4, 7, 3},  // Atividade C
        {6, 9, 3},  // Atividade D
        {8, 11, 3}  // Atividade E
    };

    // Chama a função principal e imprime o resultado
    int resultado = maximiza_tempo_ocupado(atividades);
    cout << "Tempo total ocupado: " << resultado << endl;

    // Retorna 0 indicando sucesso
    return 0;
}
