#include "ABB.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  int chave;
  char conteudo;
  No *esq;
  No *dir;
};

/* Aloca e retorna um No com os dados passados por parâmetro. Retorna no nó
 * criado ou NULL caso não seja posivel criar o nó. */
No *abb_cria_no(int chave, char conteudo) {
  No* abb=(No*)malloc(sizeof(No));
  abb->chave=chave;
  abb->conteudo=conteudo;
  return abb;
}

/* Libera a memória de um nó e toda as suas sub-árvores. Retorna 1 se for
 * possivel fazer a liberação ou 0 caso o nó seja NULL. */
int abb_libera_no(No *no) {
  if(no==NULL){
    return 0;
  }
  if(no->esq!=NULL){
    abb_libera_no(no->esq);
  }
  if(no->dir!=NULL){
    abb_libera_no(no->dir);
  }
  free(no);
  return 1;
}

/* Retorna a chave do nó ou -1 caso o nó seja NULL.  */
int abb_chave_no(No *no) {
  if(no==NULL){
    return -1;
  }
  else{
    return no->chave;
  }
}

/* Retorna o conteúdo do no ou '#' caso o nó seja NULL. */
char abb_conteudo_no(No *no) {
  if(no==NULL){
    return '#';
  }
  else{
    return no->conteudo;
  }
}

/* Adiciona um nó à esquerda ou à direita do no raiz. Retorna a raiz da árvore
 * resultante ou NULL caso (i) a raiz e o nó sejam NULL e (ii) caso o nó possua
 * mesma chave que outro nó previamente inserido na árvore. */
No *abb_insere_no(No *raiz, No *no) {
  if ((raiz == NULL && no == NULL) || (abb_busca_no(raiz, no->chave) != NULL)) {
    return NULL;
  } 
  else if (raiz == NULL) {
    raiz = no;
  } 
  else {
    No *aux = NULL;
    No *aux_no = raiz;
    while (aux_no != no) {
      if (aux_no->chave > no->chave) {
        aux = aux_no;
        aux_no = aux_no->esq;
        if (aux_no == NULL) {
          aux_no = no;
          aux->esq =aux_no;
        }
      } 
      else if (aux_no->chave < no->chave) {
        aux = aux_no;
        aux_no = aux_no->dir;
        if (aux_no == NULL) {
          aux_no = no;
          aux->dir = aux_no;
        }
      }
    }
  }
  return raiz;
}

/* Procura o nó pela chave. Retorna o nó caso a busca obtenha sucesso ou NULL
 * em caso contrário. */
No *abb_busca_no(No *raiz, int chave) {
  while(raiz!=NULL){
    if(chave<raiz->chave){
      raiz=raiz->esq;
    }
    else if(chave>raiz->chave){
      raiz=raiz->dir;
    }
    else{
      return raiz;
    }
  }
  return NULL;
}


/* Remove o nó com a chave fornecida. Retorna a raiz da arvore atualizada ou
 * NULL em caso a raiz fornecida seja NULL. */
No *abb_remove_no(No *raiz, int chave) {
  if(raiz == NULL){
    return NULL;
  }
  else{
    if(raiz->chave!=chave){
      if(chave < raiz->chave){
        raiz->esq = abb_remove_no(raiz->esq,chave);
      }
      else{
        raiz->dir = abb_remove_no(raiz->dir,chave);
      }
      return raiz;
    }
    else{
      if(raiz->esq == NULL && raiz->dir == NULL){
        free(raiz);
        return NULL;
      }
      else if(raiz->esq != NULL && raiz->dir != NULL){
        No* aux_raiz = raiz->esq;
        while (aux_raiz->dir != NULL){
          aux_raiz = aux_raiz->dir;
        }
        raiz->chave = aux_raiz->chave;
        aux_raiz->chave = chave;
        raiz->esq = abb_remove_no(raiz->esq,chave);
        return raiz;
      }
      else{
        No* aux_raiz;
        if(raiz->esq != NULL){
          aux_raiz = raiz->esq;
        }
        else{
          aux_raiz = raiz->dir;
        }
        free(raiz);
        return aux_raiz;
      }
    }  
  }
}

/* Retorna a altura da árvore ou -1 caso araiz seja NULL. */
int abb_altura(No *raiz) {
  if(raiz==NULL){
    return -1;
  }
  else{
    int aux_esq= abb_altura(raiz->esq);
    int aux_dir= abb_altura(raiz->dir);
    if(aux_esq>aux_dir){
      return aux_esq+1;
    }
    else{
      return aux_dir+1;
    }
  }
}

/* Retorna o número de nós da árvore ou -1 caso araiz seja NULL. */
int aux_num=0;
int abb_numero(No *raiz) {
  if(raiz==NULL){
    return -1;
  }
  else{
    abb_numero(raiz->esq);
    aux_num=aux_num+1;
    abb_numero(raiz->dir);  
  } 
  return aux_num;
}

/*Retorna a concatenação do conteúdo da árvore fazendo percurso em pré-ordem à
 * partir do nó ou '#' caso o nó seja NULL. */
char *abb_pre_ordem(No *no) {
  if(no==NULL){
    return "#";
  }
  else{
    char aux_concat[abb_numero(no)];
    
  }
}

/*Retorna a concatenação do conteúdo da árvore fazendo percurso em ordem à
 * partir do nó ou '#' caso o nó seja NULL. */
char *abb_ordem(No *no) {
  if(no==NULL){
    return "#";
  }
  else{
    
  }
}

/*Retorna a concatenação do conteúdo da árvore fazendo percurso em pós-ordem à
 * partir do nó ou '#' caso o nó seja NULL. */
char *abb_pos_ordem(No *no) {
  if(no==NULL){
    return "#";
  }
  else{
    
  }
}
