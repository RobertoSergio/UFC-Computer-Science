#include "Pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACIDADE_INICIAL 10

struct node {
  Aluno *aluno;
  struct node *proximo;
};

typedef struct node No;

struct pilha {
  No *primeiro;
  No *ultimo;
};

/* Aloca espaço em memória e retorna uma pilha. */
Pilha *pilha_cria() {
  Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
  pilha->primeiro = NULL;
  return pilha;
}

/* Libera a memória de uma pilha previamente criada e atribui NULL ao ponteiro
 * pilha. Retorna 1 caso seja possível fazer a liberação e 0 caso a pilha
 * informada seja NULL. */
int pilha_libera(Pilha **pilha) {
  if (pilha != NULL) {
    if ((*pilha)->primeiro != NULL) {
      No *aux = (*pilha)->primeiro;
      do {
        alu_libera(&aux->aluno);
        aux = aux->proximo;
      } while (aux != NULL);
    }
    free(*pilha);
    *pilha = NULL;
    return 1;
  }
  return 0;
}

/* Insere um aluno na Pilha. Retorna 1 se foi possível adicionar, 0 caso já
 * exista um aluno com a mesma matricula (nesse caso, o aluno não pode ser
 * adicionado) e -1 caso a pilha ou aluno sejam NULL.
 */
int pilha_push(Pilha *pilha, Aluno *aluno) {
  
  if (pilha == NULL || aluno == NULL){
    return -1;
  }
  else{
    int auxmatricula;
    char curso[30];
    char nome[50];
  
    alu_acessa(aluno, &auxmatricula, nome, curso);
    Aluno *auxaluno = pilha_busca(pilha, auxmatricula);
    
    if(auxaluno!=NULL){
      return 0;
    }
    else{
      No *noaux=(No*)malloc(sizeof(No));
      noaux->aluno=aluno;
      noaux->proximo=NULL;
      
      if(pilha->primeiro==NULL){
        pilha->primeiro=noaux;
      }
      else{
        pilha->ultimo->proximo=noaux;
      }
      pilha->ultimo=noaux;
      return 1;
    }
  }
}

/* Remove um aluno na pilha. Retorna o aluno ou NULL caso a pilha esteja vazia
 * ou seja NULL. */
Aluno *pilha_pop(Pilha *pilha) {
  if (pilha == NULL) {
    return NULL;
  } 
  else {
    int quant = pilha_quantidade(pilha);
    if (quant == 0) {
      return NULL;
    }   
    else {
      No *noaux = pilha->primeiro;
      Aluno *auxaluno = pilha->ultimo->aluno;

      do {
        if (noaux->proximo == pilha->ultimo) {
          pilha->ultimo = noaux;
          noaux->proximo = NULL;
        }
        noaux = noaux->proximo;
      } while (noaux != NULL);

      free(noaux);
      return auxaluno;
    }
  }
}

Aluno *pilha_top(Pilha *pilha) {
  if (pilha == NULL || pilha_quantidade(pilha) == 0) {
    return NULL;
  } else {
    return pilha->ultimo->aluno;
  }
}
/* Busca aluno pelo número de matricula. Retorna o aluno se este estiver na
 * lista e NULL caso contrário, isto é, (i) pilha vazia; (ii) não exista aluno
 * com a matricula fornecida; ou (iii) a pilha seja NULL */
Aluno *pilha_busca(Pilha *pilha, int matricula) {
  if(pilha==NULL){
    return NULL;
  }
  else{
   int auxquant=pilha_quantidade(pilha);
    if(auxquant==0){
      return NULL;
    }
    else{
      int auxmatricula;
      char nome[50];
      char curso[30];
      No *noaux=pilha->primeiro;
      Aluno *auxaluno=noaux->aluno;
      
      for(int i=0;i<auxquant;i++){
        auxaluno=noaux->aluno;
        alu_acessa(auxaluno,&auxmatricula,nome,curso);
        if(auxmatricula==matricula){
          return auxaluno;
        }
        noaux = noaux->proximo;
      }
      return NULL;
    }
  } 
}

/* Verifica se a pilha está vazia. Retorna 1 se a pilha estiver vazia, 0 caso
 * não esteja vazia e -1 se p Pilha for NULL
 */
int pilha_vazia(Pilha *pilha) {
  if (pilha == NULL) {
    return -1;
  }
  if (pilha->primeiro == NULL) {
    return 1;
  }
  return 0;
}

/* Computa a quantidade de alunos na pilha. Retorna a quantidade de alunos
 * ou -1, caso a Pilha for NULL.
 */
int pilha_quantidade(Pilha *pilha) {
  if (pilha == NULL) {
    return -1;
  }
  else{
    No *noaux = pilha->primeiro;
    int quant = 0;
    while (noaux != NULL) {
      quant = quant + 1;
      noaux = noaux->proximo;
    }
    return quant;
  }
}