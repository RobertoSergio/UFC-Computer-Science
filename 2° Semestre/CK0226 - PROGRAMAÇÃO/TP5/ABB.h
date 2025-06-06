/* TAD: No (chave, conteudo, esq, dir) */
typedef struct node No;

/* Aloca e retorna um No com os dados passados por parâmetro. Retorna no nó
 * criado ou NULL caso não seja posivel criar o nó. */
No *abb_cria_no(int chave, char conteudo);

/* Libera a memória de um nó e toda as suas sub-árvores. Retorna 1 se for
 * possivel fazer a liberação ou 0 caso o nó seja NULL. */
int abb_libera_no(No *no);

/* Retorna a chave do nó ou -1 caso o nó seja NULL.  */
int abb_chave_no(No *no);

/* Retorna o conteúdo do no ou '#' caso o nó seja NULL. */
char abb_conteudo_no(No *no);

/* Adiciona um nó à esquerda ou à direita do no raiz. Retorna a raiz da árvore
 * resultante ou NULL caso (i) a raiz ou o nó sejam NULL e (ii) caso o nó possua
 * mesma chave que outro nó previamente inserido na árvore. */
No *abb_insere_no(No *raiz, No *no);

/* Procura o nó pela chave. Retorna o nó caso a busca obtenha sucesso ou NULL em
 * caso contrário. */
No *abb_busca_no(No *raiz, int chave);

/* Remove o nó com a chave fornecida. Retorna a raiz da arvore atualizada ou
 * NULL em caso a raiz fornecida seja NULL. */
No *abb_remove_no(No *raiz, int chave);

/* Retorna a altura da árvore ou -1 caso araiz seja NULL. */
int abb_altura(No *raiz);

/* Retorna o número de nós da árvore ou -1 caso araiz seja NULL. */
int abb_numero(No *raiz);

/*Retorna a concatenação do conteúdo da árvore fazendo percurso em pré-ordem à
 * partir do nó ou '#' caso o nó seja NULL. */
char *abb_pre_ordem(No *no);

/*Retorna a concatenação do conteúdo da árvore fazendo percurso em ordem à
 * partir do nó ou '#' caso o nó seja NULL. */
char *abb_ordem(No *no);

/*Retorna a concatenação do conteúdo da árvore fazendo percurso em pós-ordem à
 * partir do nó ou '#' caso o nó seja NULL. */
char *abb_pos_ordem(No *no);
