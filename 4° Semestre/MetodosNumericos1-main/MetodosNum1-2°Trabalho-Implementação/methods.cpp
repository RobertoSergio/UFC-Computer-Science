#include "methods.h"

using namespace std;

const int MAXIMO_ITERACOES = 100;
const double Lim = 0.4;

void imprime_matriz(vector<vector<double>> &M, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << M[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

// Imprimir matriz para a tabela com a linha separadora
void imprime_matriz2(vector<vector<double>> &M, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
        if (j == 0) {
            cout << "| " << M[i][j] << " ";
        }
        else {
            cout << M[i][j] << " ";
        }
    }
    cout << endl;
  }
}

void imprime_e_copia_matriz(vector<vector<double>> &M,
                            vector<vector<double>> &M_copia, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << M[i][j] << " ";
      M_copia[i][j] = M[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

void imprime_e_copia_vetor(vector<double> &v, vector<double> &v_copia, int n) {
  for (int i = 0; i < n; ++i) {
    cout << v[i] << " ";
    v_copia[i] = v[i];
  }
  cout << endl << endl;
}

void imprime_vetor(vector<double> &v, int n) {
  for (int i = 0; i < n; ++i) {
    cout << v[i] << " ";
  }
  cout << endl << endl;
}

bool imprime_resultado_final_com_limite(vector<double> &resultado, int n) {
  bool explodiu = false;
  for (int i = 0; i < n; ++i) {
    if (abs(resultado[i]) > Lim) {
      cout << "d" << i << " = " << resultado[i] << " passou do limite de "
           << Lim << "cm" << endl;
      explodiu = true;
    } else
      cout << "d" << i << " = " << resultado[i] << " não passou do limite de "
           << Lim << "cm" << endl;
  }
  cout << endl;

  return explodiu;
}

void imprime_conclusao(bool explodiu, string metodo) {
  cout << "Pelo método de " << metodo << ", ";
  if (explodiu) {
    cout << "Sérios danos ocorreram e um problema gigantesco aconteceu."
         << endl;
  } else {
    cout << "Nenhum dano aconteceu." << endl;
  }
}

void cria_matriz(vector<vector<double>> &A, int n) {
  cout << "Digite os elementos da matriz:" << endl;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << "Matriz[" << i + 1 << "][" << j + 1 << "]: ";
      cin >> A[i][j];
    }
  }
}

vector<double> multiplica_matriz_por_vetor(const vector<vector<double>> &matrix,
                                           const vector<double> &vec, int n) {
  vector<double> result(n, 0);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      result[i] += matrix[i][j] * vec[j];
    }
  }

  return result;
}

vector<vector<double>> calcula_inversa(int n, vector<vector<double>> A) {
  // Criar a matriz identidade I
  vector<vector<double>> I(n, vector<double>(n, 0));
  for (int i = 0; i < n; i++) {
    I[i][i] = 1;
  }

  // Aplicar o método de Gauss-Jordan
  for (int i = 0; i < n; i++) {
    // Tornar o elemento A[i][i] igual a 1 e ajustar a matriz I
    double diag = A[i][i];
    for (int j = 0; j < n; j++) {
      A[i][j] /= diag;
      I[i][j] /= diag;
    }

    // Tornar os outros elementos da coluna i iguais a 0
    for (int k = 0; k < n; k++) {
      if (k != i) {
        double factor = A[k][i];
        for (int j = 0; j < n; j++) {
          A[k][j] -= A[i][j] * factor;
          I[k][j] -= I[i][j] * factor;
        }
      }
    }
  }

  return I;
}

double calcula_norma(int n, vector<double> &x, vector<double> &v) {
  double normaNum = 0.0;
  double normaDen = 0.0;

  for (int i = 0; i < n; ++i) {
    double t = abs(v[i] - x[i]);
    if (t > normaNum)
      normaNum = t;
    if (abs(v[i]) > normaDen)
      normaDen = abs(v[i]);

    // Atualiza o vetor x com o vetor v
    x[i] = v[i];
  }

  double norma = normaNum / normaDen;
  return norma;
}

// Função para o método de Gauss-Jacobi
vector<double> gauss_jacobi(int n, vector<vector<double>> &A, vector<double> &d,
                            vector<double> &v, double epsilon, int iterMax) {
  // Construção da matriz e do vetor de iterações
  vector<double> x(n, 0.0);
  // Vetor de matrizes que armazena todos os A's de todas as iterações
  for (int i = 0; i < n; ++i) {
    double r = 1.0 / A[i][i];
    for (int j = 0; j < n; ++j) {
      if (i != j) {
        A[i][j] *= r;
      }
    }

    d[i] *= r;
    x[i] = d[i];
  }

  int k = 0;
  // Iterações de Jacobi
  while (true) {
    ++k;
    for (int i = 0; i < n; ++i) {
      double soma = 0.0;
      for (int j = 0; j < n; ++j) {
        if (i != j) {
          soma += A[i][j] * x[j];
        }
      }
      v[i] = d[i] - soma;
    }

    // Calcula a norma
    double norma = calcula_norma(n, x, v);

    // Imprime os resultados
    cout << "Iteração " << k << ": ";
    for (int i = 0; i < n; ++i) {
      cout << x[i] << " ";
    }

    cout << "Norma: " << norma << endl;
    // Verifica o critério de parada
    if (norma < epsilon || k >= iterMax) {
      break;
    }
  }

  // Retorna o vetor x e o vetor de matrizes A no final da função
  return x;
}

// Função para o método de Gauss-Seidel
vector<double> gauss_seidel(int n, vector<vector<double>> &A, vector<double> &d,
                            vector<double> &v, double epsilon, int iterMax) {
  // Construção da matriz e do vetor de iterações
  vector<double> x(n, 0.0);

  int k = 0;
  // Iterações de Gauss-Seidel
  while (true) {
    ++k;
    for (int i = 0; i < n; ++i) {
      double soma = 0.0;
      for (int j = 0; j < n; ++j) {
        if (i != j) {
          soma += A[i][j] * x[j];
        }
      }
      v[i] = x[i]; // Salva os valores anteriores de x em v
      x[i] = (d[i] - soma) / A[i][i];
    }

    // Calcula a norma
    double norma = calcula_norma(n, v, x);

    // Imprime os resultados
    cout << "Iteração " << k << ": ";
    for (int i = 0; i < n; ++i) {
      cout << x[i] << " ";
    }
    cout << "Norma: " << norma << endl;

    // Verifica o critério de parada
    if (norma <= epsilon || k >= iterMax) {
      break;
    }
  }
  return x;
}

// Função para imprimir o quadro reposta
void quadro_resposta(int n, int q, vector<vector<vector<double>>> &lista_matrizes, vector<vector<double>> &lista_jacobis, vector<vector<double>> &lista_seidels) { 
    for (int curr_q = 0; curr_q < q; curr_q++) {
        cout << "\n|--------------------------------------------------------------------------------";
        cout << "\n| Q = " << curr_q+1 << ": \n"; // Para q valores
        vector<vector<double>> A_curr = lista_matrizes[curr_q];
        cout << "|================================================================================ \n";
        // matriz do exemplo 'q'  
        cout << "| Matriz A: \n";
        imprime_matriz2(A_curr, n);  

        cout << "|================================================================================ \n";

        cout << "| Método de Gauss-Jacobi: \n";
        cout << "| Vetor b: \n";
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                cout << "| " << lista_jacobis[curr_q][i] << " ";
            }
            else {
                cout << lista_jacobis[curr_q][i] << " ";
            }

        } 

        cout << "\n|================================================================================ \n";

        cout << "| Método de Gauss-Seidel: \n";
        cout << "| Vetor b: \n";
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                cout << "| " << lista_seidels[curr_q][i] << " "; 
            }
            else {
                cout << lista_seidels[curr_q][i] << " "; 
            }
        }

        cout << "\n|================================================================================ \n";

    }
} 

void item_e() {
  cout << endl
       << "e) Analisar o que vai acontecer nesse fenômeno, para o sistema "
          "mencionado abaixo"
       << endl;

  int n = 3;
  vector<vector<double>> A = {{5, 3, 1}, {5, 6, 1}, {1, 6, 7}},
                         A_copia(n, vector<double>(n)), A_inversa;
  vector<double> b = {1, 2, 3}, b_copia(n);
  double epsilon;

  cout << "Matriz A fornecida:" << endl;
  imprime_e_copia_matriz(A, A_copia, n);

  cout << "Vetor b fornecido:" << endl;
  imprime_e_copia_vetor(b, b_copia, n);

  cout << "Digite o vetor das incognitas v0:\n";
  vector<double> v(n);
  vector<double> v_copia(n);
  for (int i = 0; i < n; ++i) {
    cout << "v[" << i + 1 << "]: ";
    cin >> v[i];
  }
  cout << endl;

  cout << "Vetor das incognitas v inserido:\n";
  imprime_e_copia_vetor(v, v_copia, n);

  cout << "Digite o valor do Epsilon:\n";
  cin >> epsilon;
  cout << endl;
  cout << endl;

  // ------------- Gauss Jordan (Inversa) -------------

  A_inversa = calcula_inversa(n, A);
  cout << "Matriz Inversa calculada:" << endl;
  imprime_matriz(A_inversa, n);

  vector<double> solucao_inversa = multiplica_matriz_por_vetor(A_inversa, b, n);

  cout << "Solução do sistema utilizando matriz inversa: " << endl;
  imprime_vetor(solucao_inversa, n);

  cout << endl;

  // ------------- Gauss Jacobi -------------

  cout << "Para o método de Gauss Jacobi:\n";
  vector<double> resultado_jacobi =
      gauss_jacobi(n, A, b, v, epsilon, MAXIMO_ITERACOES);
  cout << endl;

  cout << "Resultado final: " << endl;

  cout << endl;
  bool gj_explodiu = imprime_resultado_final_com_limite(resultado_jacobi, n);
  cout << endl;

  // ------------- Gauss Seidel -------------

  cout << "Para o método de Gauss Seidel:\n";
  vector<double> resultado_seidel =
      gauss_seidel(n, A_copia, b_copia, v_copia, epsilon, MAXIMO_ITERACOES);
  cout << endl;

  cout << "Resultado final: " << endl;

  cout << endl;
  bool gs_explodiu = imprime_resultado_final_com_limite(resultado_seidel, n);
  cout << endl;

  // ------------- Conclusão -------------

  cout << "Conclusão" << endl << endl;

  imprime_conclusao(gj_explodiu, "Gauss-Jacobi");
  imprime_conclusao(gs_explodiu, "Gauss-Seidel");
}