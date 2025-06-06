#include "Fila.h"
#include "Aluno.h"
#include <stdio.h>
#include <stdlib.h>

#define CAPACIDADE_INICIAL 10

struct fila {
  int tamanho;
  int capacidade_maxima;
  Aluno *fila_alunos;
};

Fila *fila_cria() {
  Fila *fila = (Fila *)malloc(sizeof(Fila));
  fila->fila_alunos = (Aluno *)malloc(CAPACIDADE_INICIAL * sizeof(Aluno *));
  fila->tamanho = 0;
  fila->capacidade_maxima = CAPACIDADE_INICIAL;
  return fila;
}

int fila_libera(Fila **fila) {
  if (fila != NULL) {
    if ((*fila)->tamanho > 0) {
      free((*fila)->fila_alunos);
      (*fila)->fila_alunos = NULL;
    }
    free(*fila);
    *fila = NULL;
    return 1;
  }
  return 0;
}
int fila_insere(Fila *fila, Aluno *aluno) {
  char nome[50], curso[30];
  int matricula;
  alu_acessa(aluno, &matricula, nome, curso);
  Aluno *aluno_aux = fila_busca(fila, matricula);

  if ((fila == NULL) || (aluno == NULL)) {
    return -1;
  } else if (aluno_aux != NULL) {
    return 0;
  } else if ((fila->capacidade_maxima) == (fila->tamanho)) {
    fila->capacidade_maxima += 1;
    fila->fila_alunos =
        realloc(fila->fila_alunos, fila->capacidade_maxima * sizeof(Aluno *));
  }
  fila->tamanho += 1;
  (&(fila->fila_alunos))[fila->tamanho] = aluno;
  return 1;
}

Aluno *fila_retira(Fila *fila) {
  if (fila == NULL || (fila->tamanho == 0)) {
    return NULL;
  } else {
    
  }
}

Aluno *fila_primeiro(Fila *fila) {
  if (fila == NULL || fila->tamanho == 0) {
    return NULL;
  }
  return (&(fila->fila_alunos))[0];
}

Aluno *fila_busca(Fila *fila, int matricula) {
  int matricula_aux;
  char nome_aux[50];
  char curso_aux[30];

  if (fila == NULL || (fila->tamanho == 0)) {
    return NULL;
  }
  for (int i = 0; i < fila->tamanho; i++) {
    alu_acessa((&(fila->fila_alunos))[i], &matricula_aux, nome_aux, curso_aux);
    if (matricula == matricula_aux) {
      return (&(fila->fila_alunos))[i];
    } else if (i == fila->tamanho) {
      return NULL;
    }
  }
}

int fila_vazia(Fila *fila) {
  if (fila == NULL) {
    return -1;
  }
  if (fila->tamanho == 0) {
    return 1;
  }
  return 0;
}

int fila_quantidade(Fila *fila) {
  if (fila == NULL) {
    return -1;
  }

  return fila->tamanho;
}