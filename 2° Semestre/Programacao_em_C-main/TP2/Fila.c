#include "Fila.h"
#include <stdio.h>
#include <stdlib.h>

struct node {
  Aluno *aluno;
  struct node *proximo;
};

typedef struct node No;

struct fila {
  No *primeiro;
};

/* Aloca espaço em memória e retorna uma fila */
Fila *fila_cria() {
  Fila *fila = (Fila *)malloc(sizeof(Fila));
  fila->primeiro = NULL;
  return fila;
}

/* Libera a memória de uma fila previamente criada e atribui NULL ao ponteiro
 * fila. Retorna 1 caso seja possível fazer a liberação e 0 caso a fila
 * informada seja NULL. */
int fila_libera(Fila **fila) {
  if (fila != NULL) {
    if ((*fila)->primeiro != NULL) {
      No *aux = (*fila)->primeiro;
      do {
        alu_libera(&aux->aluno);
        aux = aux->proximo;
      } while (aux != NULL);
    }
    free(*fila);
    *fila = NULL;
    return 1;
  }
  return 0;
}

/* Insere um aluno na fila. Retorna 1 se foi possível adicionar, 0 caso já
 * exista um aluno com a mesma matricula (nesse caso, o aluno não pode ser
 * adicionado) e -1 caso a fila ou aluno sejam NULL
 */
int fila_insere(Fila *fila, Aluno *aluno) {
  int auxmatricula;
  char curso[30];
  char nome[50];

  if (fila == NULL || aluno == NULL) {
    return -1;
  }
  alu_acessa(aluno, &auxmatricula, nome, curso);
  Aluno *aux = fila_busca(fila, auxmatricula);
  if (aux != NULL) {
    return 0;
  } else {
    return 1;
  }
}

/* Remove um aluno na fila. Retorna o aluno ou NULL caso a fila esteja vazia ou
 * seja NULL */
Aluno *fila_retira(Fila *fila) {
  if (fila == NULL || fila->primeiro == NULL) {
    return NULL;
  } else {
    No *noaux = fila->primeiro->proximo;
    fila->primeiro = noaux;
    return noaux->aluno;
  }
}

/* Recupera o primeiro aluno da fila. Retorna o aluno ou NULL caso a fila esteja
 * vazia ou seja NULL */
Aluno *fila_primeiro(Fila *fila) {
  if (fila == NULL || fila_vazia(fila) == 0) {
    return NULL;
  } else {
    return fila->primeiro->aluno;
  }
}

/* Busca aluno pelo número de matricula. Retorna o aluno se este estiver na
 * lista e NULL caso contrário, isto é, (i) fila vazia; (ii) não exista aluno
 * com a matricula fornecida; ou (iii) a fila seja NULL */
Aluno *fila_busca(Fila *fila, int matricula) {
  if (fila == NULL || fila->primeiro == NULL) {
    return NULL;
  }
  int auxmatricula;
  char curso[30];
  char nome[50];

  alu_acessa(fila->primeiro->aluno, &auxmatricula, nome, curso);
  int auxquant = fila_quantidade(fila);
  No *aux = fila->primeiro;
  for (int i = 0; i < auxquant; i++) {
  }
}

/* Verifica se a fila está vazia. Retorna 1 se a fila estiver vazia, 0 caso não
 * esteja vazia e -1 se a fila for NULL
 */
int fila_vazia(Fila *fila) {
  if (fila == NULL) {
    return -1;
  } else if (fila->primeiro == NULL) {
    return 1;
  } else {
    return 0;
  }
}

/* Computa a quantidade de alunos alunos na fila. Retorna a quantidade de alunos
 * ou -1, caso a fila for NULL.
 */
int fila_quantidade(Fila *fila) {
  if (fila != NULL) {
    No *noaux = fila->primeiro;
    int tam = 0;
    if (fila->primeiro != NULL && fila->primeiro->aluno != NULL) {
      do {
        tam = tam + 1;
        noaux = noaux->proximo;
      } while (noaux->proximo != NULL);
    }
    return tam;
  }
  return -1;
}