#include "Aluno.h"

/* TAD: Pilha (pilha_alunos) */
typedef struct pilha Pilha;

/* Aloca espaço em memória e retorna uma pilha. */
Pilha *pilha_cria();

/* Libera a memória de uma pilha previamente criada e atribui NULL ao ponteiro
 * pilha. Retorna 1 caso seja possível fazer a liberação e 0 caso a pilha
 * informada seja NULL. */
int pilha_libera(Pilha **pilha);

/* Insere um aluno na Pilha. Retorna 1 se foi possível adicionar, 0 caso já
 * exista um aluno com a mesma matricula (nesse caso, o aluno não pode ser
 * adicionado) e -1 caso a pilha ou aluno sejam NULL.
 */
int pilha_push(Pilha *pilha, Aluno *aluno);

/* Remove um aluno na pilha. Retorna o aluno ou NULL caso a pilha esteja vazia
 * ou seja NULL. */
Aluno *pilha_pop(Pilha *pilha);

/* Recupera o primeiro aluno da pilha. Retorna o aluno ou NULL caso a pilha
 * esteja vazia ou seja NULL. */
Aluno *pilha_top(Pilha *pilha);

/* Busca aluno pelo número de matricula. Retorna o aluno se este estiver na
 * lista e NULL caso contrário, isto é, (i) pilha vazia; (ii) não exista aluno
 * com a matricula fornecida; ou (iii) a pilha seja NULL */
Aluno *pilha_busca(Pilha *pilha, int matricula);

/* Verifica se a pilha está vazia. Retorna 1 se a pilha estiver vazia, 0 caso
 * não esteja vazia e -1 se p Pilha for NULL
 */
int pilha_vazia(Pilha *pilha);

/* Computa a quantidade de alunos na pilha. Retorna a quantidade de alunos
 * ou -1, caso a Pilha for NULL.
 */
int pilha_quantidade(Pilha *pilha);