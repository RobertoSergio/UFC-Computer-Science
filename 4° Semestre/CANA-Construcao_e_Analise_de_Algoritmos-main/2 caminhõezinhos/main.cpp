#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Função recursiva para calcular a quantidade máxima de dados processados
int maximo_de_dados_processados_recursivo(const vector<int> &dados_processamento, const vector<int> &dados_possiveis_processados, int i, int j, vector<vector<int>> &Tabela_Memoria);

// Função auxiliar para determinar o próximo dia sem reiniciar
int proximo_dia_sem_reiniciar(int i, int j, const vector<int> &dados_possiveis_processados) {
    // Se houver um próximo dia, avance para ele; caso contrário, volte ao início
    return j + 1 < dados_possiveis_processados.size() ? j + 1 : 0;
}

// Função principal para calcular a quantidade máxima de dados processados
int maximo_de_dados_processados(const vector<int> &dados_processamento, const vector<int> &dados_possiveis_processados) {
    int n = dados_processamento.size();
    // Tabela de memória para armazenar resultados já calculados
    vector<vector<int>> Tabela_Memoria(n, vector<int>(dados_possiveis_processados.size(), -1));
    // Chama a função recursiva
    return maximo_de_dados_processados_recursivo(dados_processamento, dados_possiveis_processados, 0, 0, Tabela_Memoria);
}

// Função recursiva para calcular a quantidade máxima de dados processados
int maximo_de_dados_processados_recursivo(const vector<int> &dados_processamento, const vector<int> &dados_possiveis_processados, int i, int j, vector<vector<int>> &Tabela_Memoria) {
    int n = dados_processamento.size();

    // Se todas as entradas foram processadas, retorna 0
    if (i >= n) {
        return 0;
    }

    // Se já calculamos o resultado para essa posição, retornamos o valor memoizado
    if (Tabela_Memoria[i][j] != -1) {
        return Tabela_Memoria[i][j];
    }

    // Calcula a quantidade de dados processados no dia
    int dados = min(dados_processamento[i], dados_possiveis_processados[j]);

    // Calcula a quantidade de dados processados ao não reiniciar no dia i
    int nao_reiniciar = dados + maximo_de_dados_processados_recursivo(dados_processamento, dados_possiveis_processados, i + 1, proximo_dia_sem_reiniciar(i, j, dados_possiveis_processados), Tabela_Memoria);

    // Calcula a quantidade de dados processados ao reiniciar no dia i
    int reiniciar = maximo_de_dados_processados_recursivo(dados_processamento, dados_possiveis_processados, i + 1, 0, Tabela_Memoria);

    // Retorna o máximo entre as duas opções
    Tabela_Memoria[i][j] = max(nao_reiniciar, reiniciar);

    return Tabela_Memoria[i][j];
}

int main() {
    // Dados de processamento e possíveis dados processados
    vector<int> dados_processamento = {5, 1, 20, 5};
    vector<int> dados_possiveis_processados = {20, 15, 10, 5};

    // Inicializa a tabela de memória
    vector<vector<int>> Tabela_Memoria(dados_processamento.size(), vector<int>(dados_possiveis_processados.size(), -1));

    // Chama a função principal para obter o resultado
    int resultado = maximo_de_dados_processados(dados_processamento, dados_possiveis_processados);

    // Imprime o resultado
    cout << "Quantidade máxima de dados processados: " << resultado << endl;

    return 0;
}
