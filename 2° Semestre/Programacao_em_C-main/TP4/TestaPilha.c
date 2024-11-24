#include "Pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float teste_aluno_novo_com_dados_validos() {
  char nome[50];
  char curso[30];
  float pontuacao = 0;

  Aluno *aluno = alu_novo(1, "Abraão", "Computação");

  if (aluno != NULL) {
    printf("[Passou 1.50] - Teste da função alu_novo() com dados válidos!\n");
    pontuacao = 1.5;
  } else {
    printf("[Falhou 0.00] - Teste da função alu_novo() com dados válidos!\n");
  }
  return pontuacao;
}

float teste_aluno_novo_com_dados_invalidos() {
  char nome[55] = "N";
  char curso[35] = "C";
  float pontuacao = 0;

  for (int i = 0; i < 53; i++) {
    strcat(nome, "N");
  }

  for (int i = 0; i < 33; i++) {
    strcat(curso, "C");
  }

  Aluno *aluno = alu_novo(-1, nome, curso);
  if (aluno == NULL) {
    printf("[Passou 1.00] - Teste da função alu_novo() com dados inválidos!\n");
    pontuacao = 1;
  } else {
    printf("[Falhou 0.00] - Teste da função alu_novo() com dados inválidos!\n");
  }
  return pontuacao;
}

float teste_aluno_novo_com_dados_nulos() {
  float pontuacao = 0;

  Aluno *aluno = alu_novo(-1, NULL, NULL);
  if (aluno == NULL) {
    printf("[Passou 0.67] - Teste da função alu_novo() com dados nulos!\n");
    pontuacao = 0.67;
  } else {
    printf("[Falhou 0.00] - Teste da função alu_novo() com dados nulos!\n");
  }
  return pontuacao;
}

float teste_aluno_acessa_com_dados_validos() {
  int matricula;
  char nome[50];
  char curso[30];
  float pontuacao = 0;

  Aluno *aluno = alu_novo(1, "Abraão", "Computação");
  if (aluno != NULL) {
    alu_acessa(aluno, &matricula, nome, curso);
    if (matricula == 1 && strcmp(nome, "Abraão") == 0 &&
        strcmp(curso, "Computação") == 0) {
      printf(
          "[Passou 1.50] - Teste da função alu_acessa() com dados válidos!\n");
      pontuacao = 1.5;
    } else {
      printf(
          "[Falhou 0.00] - Teste da função alu_acessa()com dados válidos!\n");
    }
  } else {
    printf("[Falhou 0.00] - Teste da função alu_acessa() com dados válidos!\n");
  }
  return pontuacao;
}

float teste_aluno_atribui_com_dados_validos() {
  int matricula;
  char nome[50];
  char curso[30];
  float pontuacao = 0;

  Aluno *aluno = alu_novo(1, "Abraão", "Computação");
  if (aluno != NULL) {
    alu_atribui(aluno, 2, "Jacó", "Sistemas de Informação");
    alu_acessa(aluno, &matricula, nome, curso);
    if (matricula == 2 && strcmp(nome, "Jacó") == 0 &&
        strcmp(curso, "Sistemas de Informação") == 0) {
      printf(
          "[Passou 1.50] - Teste da função alu_atribui() com dados válidos!\n");
      pontuacao = 1.5;
    } else {
      printf(
          "[Falhou 0.00] - Teste da função alu_atribui() com dados válidos!\n");
    }
  } else {
    printf(
        "[Falhou 0.00] - Teste da função alu_atribui() com dados válidos!\n");
  }
  return pontuacao;
}

float teste_aluno_atribui_com_dados_invalidos() {
  int matricula;
  char nome[55] = "N";
  char curso[35] = "C";
  float pontuacao = 0;

  for (int i = 0; i < 53; i++) {
    strcat(nome, "N");
  }

  for (int i = 0; i < 33; i++) {
    strcat(curso, "C");
  }

  Aluno *aluno = alu_novo(1, "Abraão", "Computação");
  if (aluno != NULL) {
    alu_atribui(aluno, 2, nome, curso);
    alu_acessa(aluno, &matricula, nome, curso);
    if (matricula == 1 || strcmp(nome, "Abraão") == 0 ||
        strcmp(curso, "Computação") == 0) {
      printf("[Passou 1.00] - Teste da função alu_atribui() com dados "
             "inválidos!\n");
      pontuacao = 1;
    } else {
      printf("[Falhou 0.00] - Teste da função alu_atribui() com dados "
             "inválidos!\n");
    }
  } else {
    printf(
        "[Falhou 0.00] - Teste da função alu_atribui() com dados inválidos!\n");
  }
  return pontuacao;
}

float teste_aluno_atribui_com_dados_nulos() {
  int matricula;
  char nome[50];
  char curso[30];
  float pontuacao = 0;

  Aluno *aluno = alu_novo(1, "Abraão", "Computação");
  if (aluno != NULL) {
    alu_atribui(NULL, -1, NULL, NULL);
    alu_acessa(aluno, &matricula, nome, curso);
    if (matricula == 1 && strcmp(nome, "Abraão") == 0 &&
        strcmp(curso, "Computação") == 0) {
      printf(
          "[Passou 0.67] - Teste da função alu_atribui() com dados nulos!\n");
      pontuacao = 0.67;
    } else {
      printf(
          "[Falhou 0.00] - Teste da função alu_atribui() com dados nulos!\n");
    }
  } else {
    printf("[Falhou 0.00] - Teste da função alu_atribui() com dados nulos!\n");
  }
  return pontuacao;
}

float teste_aluno_libera_com_dados_validos() {
  int matricula;
  char nome[50];
  char curso[30];
  float pontuacao = 0;

  Aluno *aluno = alu_novo(1, "Abraão", "Computação");
  alu_libera(&aluno);
  if (aluno != NULL) {
    printf("[Falhou 0.00] - Teste da função alu_libera() com dados válidos!\n");
    pontuacao = 0.0;
  } else {
    printf("[Passou 1.50] - Teste da função alu_libera() com dados válidos!\n");
    pontuacao = 1.5;
  }
  return pontuacao;
}

float teste_aluno_libera_com_dados_nulos() {
  int matricula;
  char nome[50];
  char curso[30];
  float pontuacao = 0;

  Aluno *aluno = NULL;
  alu_libera(&aluno);
  if (aluno == NULL) {
    printf("[Passou 0.67] - Teste da função alu_libera() com dados nulos!\n");
    pontuacao = 0.67;
  } else {
    printf("[Falhou 0.00] - Teste da função alu_libera() com dados nulos!\n");
  }
  return pontuacao;
}

float teste_pilha_cria_com_dados_validos() {
  float pontuacao = 0;
  Pilha *pilha = pilha_cria();
  if (pilha != NULL) {
    printf("[Passou 1.00] - Teste da função pilha_cria() com dados válidos!\n");
    pontuacao = 1.0;
  } else {
    printf("[Falhou 0.00] - Teste da função pilha_cria() com dados válidos!\n");
  }
  return pontuacao;
}

float teste_pilha_libera_com_dados_validos() {
  float pontuacao = 0;
  Pilha *pilha = pilha_cria();
  pilha_libera(&pilha);
  if (pilha != NULL) {
    printf(
        "[Falhou 0.00] - Teste da função pilha_libera() com dados válidos!\n");
  } else {
    printf(
        "[Passou 1.00] - Teste da função pilha_libera() com dados válidos!\n");
    pontuacao = 1;
  }
  return pontuacao;
}

float teste_pilha_libera_com_dados_nulos() {
  float pontuacao = 0;
  if (pilha_libera(NULL) == 0) {
    printf("[Passou 0.50] - Teste da função pilha_libera() com dados nulos!\n");
    pontuacao = 0.50;
  } else {
    printf("[Falhou 0.00] - Teste da função pilha_libera() com dados nulos!\n");
  }
  return pontuacao;
}

float teste_pilha_vazia_com_dados_validos() {
  float pontuacao = 0.0;
  Pilha *pilha = pilha_cria();
  if (pilha != NULL && pilha_vazia(pilha)) {
    printf(
        "[Passou 1.00] - Teste da função pilha_vazia() com dados válidos!\n");
    pontuacao = 1.0;
  } else {
    printf(
        "[Falhou 0.00] - Teste da função pilha_vazia() com dados válidos!\n");
  }
  return pontuacao;
}

float teste_pilha_push_com_dados_validos() {
  float pontuacao = 0;
  Pilha *pilha = pilha_cria();
  if (pilha != NULL) {
    Aluno *abraao = alu_novo(1, "Abraão", "Computação");
    if (pilha_push(pilha, abraao) == 1) {
      Aluno *jaco = alu_novo(2, "Jaco", "Computação");
      if (pilha_push(pilha, jaco) == 1) {
        Aluno *jose = alu_novo(3, "Jose", "Computação");
        if (pilha_push(pilha, jose) == 1) {
          printf("[Passou 1.00] - Teste da função pilha_push() com dados "
                 "válidos!\n");
          pontuacao = 1.0;
        } else {
          printf("[Falhou 0.00] - Teste da função pilha_push() com dados "
                 "válidos!\n");
        }
      } else {
        printf("[Falhou 0.00] - Teste da função pilha_push() com dados "
               "válidos!\n");
      }
    } else {
      printf("[Falhou 0.00] - Teste da função pilha_push() com dados "
             "válidos!\n");
    }
  } else {
    printf("[Falhou 0.00] - Teste da função pilha_push() com dados válidos!\n");
  }
  return pontuacao;
}

float teste_pilha_push_com_dados_invalidos() {
  float pontuacao = 0.0;
  Pilha *pilha = pilha_cria();

  if (pilha != NULL) {
    Aluno *abraao = alu_novo(1, "Abraão", "Computação");
    pilha_push(pilha, abraao);
    Aluno *jaco = alu_novo(1, "Jaco", "Computação");
    if (pilha_push(pilha, jaco) == 0) {
      printf("[Passou 0.67] - Teste da função pilha_push() com dados "
             "inválidos!\n");
      pontuacao = 0.67;
    }
  } else {
    printf("[Falhou 0.00] - Teste da função pilha_push() com dados "
           "inválidos!\n");
  }

  return pontuacao;
}

float teste_pilha_push_com_dados_nulos() {
  float pontuacao = 0;
  Pilha *pilha = pilha_cria();
  if (pilha_push(pilha, NULL) == -1) {
    Aluno *abraao = alu_novo(1, "Abraão", "Computação");
    if (pilha_push(NULL, abraao) == -1) {
      if (pilha_push(NULL, NULL) == -1) {
        printf("[Passou 0.50] - Teste da função pilha_push() com dados "
               "nulos!\n");
        pontuacao = 0.50;
      } else {
        printf("[Falhou 0.00] - Teste da função pilha_push() com dados "
               "nulos!\n");
      }
    } else {
      printf("[Falhou 0.00] - Teste da função pilha_push() com dados nulos!\n");
    }
  } else {
    printf("[Falhou 0.00] - Teste da função pilha_push() com dados nulos!\n");
  }
  return pontuacao;
}

float teste_pilha_pop_com_dados_validos() {
  float pontuacao = 0;
  Pilha *pilha = pilha_cria();
  if (pilha != NULL) {
    Aluno *abraao = alu_novo(1, "Abraão", "Computação");
    pilha_push(pilha, abraao);
    Aluno *jaco = alu_novo(2, "Jaco", "Computação");
    pilha_push(pilha, jaco);
    Aluno *jose = alu_novo(3, "Jose", "Computação");
    pilha_push(pilha, jose);
    Aluno *aluno = pilha_pop(pilha);

    if (alu_igual(aluno, jose) == 1) {
      aluno = pilha_pop(pilha);
      if (alu_igual(aluno, jaco) == 1) {
        aluno = pilha_pop(pilha);
        if (alu_igual(aluno, abraao) == 1) {
          printf("[Passou 1.00] - Teste da função pilha_pop() com dados "
                 "válidos!\n");
          pontuacao = 1.0;
        } else {
          printf("[Falhou 0.00] - Teste da função pilha_pop() com dados "
                 "válidos!\n");
        }
      } else {
        printf("[Falhou 0.00] - Teste da função pilha_pop() com dados "
               "válidos!\n");
      }
    } else {
      printf(
          "[Falhou 0.00] - Teste da função pilha_pop() com dados válidos!\n");
    }
  } else {
    printf("[Falhou 0.00] - Teste da função pilha_pop() com dados válidos!\n");
  }
  return pontuacao;
}

float teste_pilha_pop_com_dados_nulos() {
  float pontuacao = 0;
  if (pilha_pop(NULL) == NULL) {
    printf("[Passou 0.50] - Teste da função pilha_pop() com dados nulos!\n");
    pontuacao = 0.50;
  } else {
    printf("[Falhou 0.00] - Teste da função pilha_pop() com dados nulos!\n");
  }
  return pontuacao;
}

float teste_pilha_top_com_dados_validos() {
  float pontuacao = 0;
  Pilha *pilha = pilha_cria();
  if (pilha != NULL) {
    Aluno *abraao = alu_novo(1, "Abraão", "Computação");
    pilha_push(pilha, abraao);
    Aluno *jaco = alu_novo(2, "Jaco", "Computação");
    pilha_push(pilha, jaco);
    Aluno *jose = alu_novo(3, "Jose", "Computação");
    pilha_push(pilha, jose);
    Aluno *aluno = pilha_top(pilha);

    if (alu_igual(aluno, jose) == 1) {
      printf("[Passou 0.335] - Teste da função pilha_top() com dados "
             "válidos!\n");
      pontuacao = 0.335;

    } else {
      printf("[Falhou 0.00] - Teste da função pilha_top() com dados "
             "válidos!\n");
    }
  } else {
    printf("[Falhou 0.00] - Teste da função pilha_top() com dados válidos!\n");
  }
  return pontuacao;
}

float teste_pilha_top_com_dados_nulos() {
  float pontuacao = 0;
  Pilha *pilha = pilha_cria();

  if (pilha_top(pilha) == NULL) {
    pilha = NULL;
    if (pilha_top(pilha) == NULL) {
      printf("[Passou 0.335] - Teste da função pilha_top() com dados "
             "nulos!\n");
      pontuacao = 0.335;
    } else {
      printf("[Falhou 0.00] - Teste da função pilha_top() com dados nulos!\n");
    }
  } else {
    printf("[Falhou 0.00] - Teste da função pilha_top() com dados nulos!\n");
  }

  return pontuacao;
}

float teste_pilha_busca_com_dados_validos() {
  float pontuacao = 0.0;
  int matricula;
  char nome[50];
  char curso[30];

  Pilha *pilha = pilha_cria();
  if (pilha != NULL) {
    Aluno *abraao = alu_novo(1, "Abraão", "Computação");
    pilha_push(pilha, abraao);
    Aluno *jaco = alu_novo(2, "Jaco", "Computação");
    pilha_push(pilha, jaco);
    Aluno *jose = alu_novo(3, "Jose", "Computação");
    pilha_push(pilha, jose);
    Aluno *aux = pilha_busca(pilha, 2);
    if (aux != NULL) {
      alu_acessa(aux, &matricula, nome, curso);
      if (matricula == 2 && strcmp(nome, "Jaco") == 0 &&
          strcmp(curso, "Computação") == 0) {
        printf("[Passou 1.00] - Teste da função pilha_busca() com dados "
               "válidos!\n");
        pontuacao = 1.0;
      } else {
        printf("[Falhou 0.00] - Teste da função pilha_busca() com dados "
               "válidos!\n");
      }
    } else {
      printf("[Falhou 0.00] - Teste da função pilha_busca() com dados "
             "válidos!\n");
    }
  } else {
    printf(
        "[Falhou 0.00] - Teste da função pilha_busca() com dados válidos!\n");
  }
  return pontuacao;
}

float teste_pilha_busca_com_dados_invalidos() {
  float pontuacao = 0;
  int matricula;
  char nome[50];
  char curso[30];

  Pilha *pilha = pilha_cria();
  if (pilha != NULL) {
    Aluno *abraao = alu_novo(1, "Abraão", "Computação");
    pilha_push(pilha, abraao);
    Aluno *jaco = alu_novo(2, "Jaco", "Computação");
    pilha_push(pilha, jaco);
    Aluno *jose = alu_novo(3, "Jose", "Computação");
    pilha_push(pilha, jose);
    Aluno *aux = pilha_busca(pilha, 5);
    if (aux == NULL) {
      printf("[Passou 0.67] - Teste da função pilha_busca() com dados "
             "inválidos!\n");
      pontuacao = 0.67;
    } else {
      printf("[Falhou 0.00] - Teste da função pilha_busca() com dados "
             "inválidos!\n");
    }
  } else {
    printf("[Falhou 0.00] - Teste da função pilha_busca() com dados "
           "inválidos!\n");
  }
  return pontuacao;
}

float teste_pilha_busca_com_dados_nulos() {
  float pontuacao = 0;
  int matricula;
  char nome[50];
  char curso[30];

  Aluno *aux = pilha_busca(NULL, 1);
  if (aux == NULL) {
    printf("[Passou 0.50] - Teste da função pilha_busca() com dados nulos!\n");
    pontuacao = 0.50;
  } else {
    printf("[Falhou 0.00] - Teste da função pilha_busca() com dados nulos!\n");
  }
  return pontuacao;
}

float bateria_testes_01() {
  printf("====================================================================="
         "====================\n");
  printf(".:: Teste do TAD Aluno: Bateria de Testes 01 ::.\n");
  printf("====================================================================="
         "====================\n");
  float pontuacao = 0;
  pontuacao = teste_aluno_novo_com_dados_validos() +
              teste_aluno_atribui_com_dados_validos() +
              teste_aluno_acessa_com_dados_validos() +
              teste_aluno_libera_com_dados_validos();
  printf("\nTotal: %f\n", pontuacao);
  printf("====================================================================="
         "====================\n\n");
  return pontuacao;
}

float bateria_testes_02() {
  printf("====================================================================="
         "====================\n");
  printf(".:: Teste do TAD Aluno: Bateria de Testes 02 ::.\n");
  printf("====================================================================="
         "====================\n");
  float pontuacao = 0;
  pontuacao = teste_aluno_novo_com_dados_invalidos() +
              teste_aluno_atribui_com_dados_invalidos();
  printf("\nTotal: %f\n", pontuacao);
  printf("====================================================================="
         "====================\n\n");
  return pontuacao;
}

float bateria_testes_03() {
  printf("====================================================================="
         "====================\n");
  printf(".:: Teste do TAD Aluno: Bateria de Testes 03 ::.\n");
  printf("====================================================================="
         "====================\n");
  float pontuacao = 0;
  pontuacao = teste_aluno_novo_com_dados_nulos() +
              teste_aluno_atribui_com_dados_nulos() +
              teste_aluno_libera_com_dados_nulos();
  printf("\nTotal: %f\n", pontuacao);
  printf("====================================================================="
         "====================\n\n");
  return pontuacao;
}

float bateria_testes_04() {
  printf("====================================================================="
         "====================\n");
  printf(".:: Teste do TAD Pilha: Bateria de Testes 04 ::.\n");
  printf("====================================================================="
         "====================\n");
  float pontuacao = 0;
  pontuacao += teste_pilha_cria_com_dados_validos() +
               teste_pilha_push_com_dados_validos();

  pontuacao += teste_pilha_libera_com_dados_validos() +
               teste_pilha_pop_com_dados_validos();

  pontuacao +=
      teste_pilha_top_com_dados_validos() + teste_pilha_top_com_dados_nulos();

  pontuacao += teste_pilha_busca_com_dados_validos() +
               teste_pilha_vazia_com_dados_validos();
  printf("\nTotal: %f\n", pontuacao);
  printf("====================================================================="
         "====================\n\n");
  return pontuacao;
}

float bateria_testes_05() {
  printf("====================================================================="
         "====================\n");
  printf(".:: Teste do TAD Pilha: Bateria de Testes 05 ::.\n");
  printf("====================================================================="
         "====================\n");
  float pontuacao = 0;
  pontuacao += teste_pilha_push_com_dados_invalidos();

  pontuacao += teste_pilha_busca_com_dados_invalidos();
  printf("\nTotal: %f\n", pontuacao);
  printf("====================================================================="
         "====================\n\n");
  return pontuacao;
}

float bateria_testes_06() {
  printf("====================================================================="
         "====================\n");
  printf(".:: Teste do TAD Pilha: Bateria de Testes 06 ::.\n");
  printf("====================================================================="
         "====================\n");
  float pontuacao = 0;
  pontuacao +=
      teste_pilha_push_com_dados_nulos() + teste_pilha_libera_com_dados_nulos();

  pontuacao +=
      teste_pilha_pop_com_dados_nulos() + teste_pilha_busca_com_dados_nulos();
  printf("\nTotal: %f\n", pontuacao);
  printf("====================================================================="
         "====================\n\n");
  return pontuacao;
}

int main(void) {
  float pontuacao_TAD_Aluno = bateria_testes_01();
  pontuacao_TAD_Aluno += bateria_testes_02();
  pontuacao_TAD_Aluno += bateria_testes_03();

  float pontuacao_TAD_Fila = bateria_testes_04();
  pontuacao_TAD_Fila += bateria_testes_05();
  pontuacao_TAD_Fila += bateria_testes_06();
  printf("Nota TP04: %f\n",
         0.3 * pontuacao_TAD_Aluno + 0.7 * pontuacao_TAD_Fila);
  return 0;
}