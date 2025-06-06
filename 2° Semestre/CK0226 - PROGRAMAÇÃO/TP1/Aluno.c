#include "Aluno.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno {
  int matricula; 
  char nome[50];
  char curso[30];
};

Aluno *alu_novo(int matricula, char *nome, char *curso) {
  if ((matricula < 0) || (nome == NULL) || (curso == NULL) ||
      (strlen(nome) > 50) || strlen(curso) > 30) {
    return NULL;
  } else {
    Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));
    aluno->matricula = matricula;
    strcpy(aluno->nome, nome);
    strcpy(aluno->curso, curso);

    return aluno;
  }
}

void alu_libera(Aluno **aluno) {
  if (*aluno != NULL) {
    free(*aluno);
    *aluno = NULL;
  }
}

void alu_acessa(Aluno *aluno, int *matricula, char *nome, char *curso) {
  if (aluno == NULL) {
    *matricula = -1;      
    strcpy(nome, "NULL"); 
    strcpy(curso, "NULL");
    
  } else {
    *matricula = aluno->matricula; 
    strcpy(nome, aluno->nome);
    strcpy(curso, aluno->curso);
  }
}

void alu_atribui(Aluno *aluno, int matricula, char *nome, char *curso) {
  if ((aluno == NULL) || (matricula < 0) || (nome == NULL) || (curso == NULL) ||
      (strlen(nome) > 50) || (strlen(curso) > 30)) {
    // não faz nada
  } else {
    aluno->matricula = matricula;
    strcpy(aluno->nome, nome);
    strcpy(aluno->curso, curso);
  }
}

int alu_igual(Aluno *aluno1, Aluno *aluno2) {
  if ((aluno1 == NULL) || (aluno2 == NULL)) {
    return -1;
  } else if ((strcmp(aluno1->nome, aluno2->nome) == 1) &&
             (aluno1->matricula == aluno2->matricula) &&
             (strcmp(aluno1->curso, aluno2->curso) == 1)) {
    return 1;
  } else {
    return 0;
  }
}

int alu_tamanho() { return sizeof(struct aluno); }