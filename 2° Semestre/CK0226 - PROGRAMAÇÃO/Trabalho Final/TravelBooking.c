#include "TravelBooking.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data {
  int dia;
  int mes;
  int ano;
};

struct voo {
  int codigo;
  char origem[50];
  char destino[50];
};

struct no_voo {
  Voo *voo;
  struct no_voo *proximo;
};

struct lista_voo {
  struct no_voo *primeiro;
};

struct passageiro {
  int id;
  char nome[50];
  char endereco[50];
};

struct no_passageiro {
  Passageiro *passageiro;
  struct no_passageiro *proximo;
};

struct lista_passageiro {
  struct no_passageiro *primeiro;
};

struct reserva {
  int codigo;
  Data *data_viagem;
  Passageiro *passageiro;
  Voo *voo;
  Assento assento;
};
struct agenda {
  Reserva *reserva;
  Agenda *esq;
  Agenda *dir;
};

struct trecho {
  Reserva *reserva;
  struct trecho *proximo;
};

struct viagem {
  struct trecho *trechos;
};

struct tabela_viagem {
  int tamanho;
  Viagem **tabela_hash;
};

struct lista_aux_viagem {
  Viagem *viagem;
  ListaAuxViagem *prox;
};

// verifica a quantidade de dias de cada mês, se o número de dias passar do
// total de dias do mês a função retorna 0, caso contrário retorna 1.
int verifica_dias(int dia, int mes) {
  if ((mes == 1 && dia <= 31) || (mes == 3 && dia <= 31) ||
      (mes == 5 && dia <= 31) || (mes == 7 && dia <= 31) ||
      (mes == 8 && dia <= 31) || (mes == 10 && dia <= 31) ||
      (mes == 12 && dia <= 31) || (mes == 2 && dia <= 28) ||
      (mes == 4 && dia <= 30) || (mes == 6 && dia <= 30) ||
      (mes == 9 && dia <= 30) || (mes == 11 && dia <= 30)) {
    return 1;
  } else {
    return 0;
  }
}

// se data1 for passado da data2 retorna 1
// se data1 for futuro da data2 retorna 2
// se forem o mesmo dia retorna 0
int passado_futuro(Data *data1, Data *data2) {
  if (data1->ano < data2->ano) {
    return 1;
  } else if (data1->ano > data2->ano) {
    return 2;
  } else {
    if (data1->mes < data2->mes) {
      return 1;
    } else if (data1->mes > data2->mes) {
      return 2;
    } else {
      if (data1->dia < data2->dia) {
        return 1;
      } else if (data1->dia > data2->dia) {
        return 2;
      } else {
        return 0;
      }
    }
  }
}

// Se nome, endereço ou ID forem invalidos, retorna -1
// Se todos os parametros forem validos, retorna 1
int verif_parametros(int id, char *nome, char *endereco) {
  if (nome == NULL || endereco == NULL) {
    return -1;
  } else if (id < 0 || strlen(nome) > 50 || strlen(endereco) > 50) {
    return -1;
  } else {
    return 1;
  }
}

// Recebe os campos <id,nome,endereco> e retorna uma passageiro com
// com esses valores ou NULL caso id<0, nome=NULL ou endereco=NULL
Passageiro *criar_passageiro(int id, char *nome, char *endereco) {
  if (verif_parametros(id, nome, endereco) == -1) {
    return NULL;
  }
  Passageiro *passageiro = (Passageiro *)malloc(sizeof(Passageiro));
  passageiro->id = id;
  strcpy(passageiro->nome, nome);
  strcpy(passageiro->endereco, endereco);
  return passageiro;
}

// libera passageiro
void pas_libera(Passageiro **passageiro) {
  if (passageiro != NULL) {
    free(*passageiro);
    *passageiro = NULL;
  }
}

// Cria e retorna um No com um passageiro dentro
// retorna NULL caso passageiro seja NULL
No_passageiro *criar_no_passageiro(Passageiro *passageiro) {
  if (passageiro == NULL) {
    return NULL;
  }
  No_passageiro *no_passageiro = (No_passageiro *)malloc(sizeof(No_passageiro));
  no_passageiro->passageiro = passageiro;

  return no_passageiro;
}

// Inicia e retorna uma lista_passageiro
Lista_Passageiro *criar_lista_passageiro() {
  Lista_Passageiro *lista_passageiro =
      (Lista_Passageiro *)malloc(sizeof(Lista_Passageiro));
  return lista_passageiro;
}

// libera Lista_passageiro
// Retorna 0 se a lista não pode ser liberada
// Retorna 1 se a liberação foi concluida
int lis_pas_libera(Lista_Passageiro **lista_passageiro) {
  if (lista_passageiro != NULL) {
    if ((*lista_passageiro)->primeiro != NULL) {
      No_passageiro *aux = (*lista_passageiro)->primeiro;
      // no_aux recebe o primeiro da lista_passageiro
      while (aux != NULL) { // passa por toda a lista e libera memoria
        pas_libera(&aux->passageiro);
        aux = aux->proximo; // quando o proximo de aux for NULL, aux é o ultimo
                            // elemento
      }
    }
    free(*lista_passageiro);
    *lista_passageiro = NULL; // apos liberação de memoria, atribui NULL a lista
    return 1;
  }
  return 0;
}

// Verifica se existe um passageiro com o id inserido, retorna NULL se o
// id não existir, a lista for vazia ou se a lista for NULL
Passageiro *buscar_passageiro(Lista_Passageiro *lista_passageiro, int id) {
  if (lista_passageiro == NULL || lista_passageiro->primeiro == NULL ||
      id < 0) {
    return NULL;
  }
  No_passageiro *no_aux = lista_passageiro->primeiro;
  Passageiro *aux = no_aux->passageiro;
  // Percorrer a lista ate o final (ate o proximo ser NULL)
  while (no_aux != NULL) {
    if (aux->id == id) {
      // se for o ID procurado, retorna o passageiro correspondente
      return aux;
    }
    no_aux = no_aux->proximo;   // vai para o proximo no_passageiro
    if (no_aux != NULL) {       // se esse proximo no nao for NULL
      aux = no_aux->passageiro; // pega o passageiro desse novo no
    }
  } // se o ID nao estiver na lista, sai do while loop e retorna NULL
  return NULL;
}

// Insere um novo no_passageiro a lista, retorna 1 se for possivel
// adicionar, retorna 0 caso a lista seja NULL,caso o no seja NULL ou já exista
// o id do passageiro
int inserir_passageiro(Lista_Passageiro *lista_passageiro,
                       No_passageiro *no_passageiro) {
  if (lista_passageiro == NULL || no_passageiro == NULL ||
      buscar_passageiro(lista_passageiro, no_passageiro->passageiro->id) !=
          NULL) {
    return 0; // nao eh possivel inserir esse passageiro na lista
  }
  No_passageiro *aux = lista_passageiro->primeiro;
  no_passageiro->proximo =
      aux; // o proximo nó recebe a informação do primeiro nó
  lista_passageiro->primeiro = no_passageiro;
  // o primeiro nó agora recebe o novo no_passageiro a ser adicionado
  return 1;
}

// Remove e retorna no_passageiro com id inserido, retorna NULL caso id não seja
// encontrado, a lista esteja vazia ou seja NULL
Passageiro *remover_passageiro(Lista_Passageiro *lista_passageiro, int id) {
  if (buscar_passageiro(lista_passageiro, id) != NULL) {
    // se os parametros forem validos, entram no if
    No_passageiro *aux_ant = NULL;
    No_passageiro *aux = lista_passageiro->primeiro;
    while (aux->passageiro->id != id) {
      // enquanto nao for o ID desejado
      aux_ant = aux;
      // aux_ant vai recebendo um valor de no_passageiro aux que esta sendo
      // percorrido
      aux = aux->proximo;
    }
    if (aux_ant != NULL) {
      aux_ant->proximo = aux->proximo;
    } else {
      lista_passageiro->primeiro = aux->proximo;
    }
    return aux->passageiro;
  }
  return NULL;
}

// Compara dois passageiros
// retorna 1 se dois passageiros forem iguais e 0 caso forem diferentes
int comp_passageiros(Passageiro *passageiro1, Passageiro *passageiro2) {
  if (passageiro1->id == passageiro2->id) {
    if (strcmp(passageiro1->nome, passageiro2->nome) == 0) {
      if (strcmp(passageiro1->endereco, passageiro2->endereco) == 0) {
        return 1;
      }
      return 0;
    }
    return 0;
  }
  return 0;
}

// Modifica dados de um passageiro dentro da lista inserida
// retorna 1 caso tenha sido possivel realizar a modificação
// retorna 0 caso a lista seja NULL, a lista seja vazia,
// o passageiro não seja encontrado ou as novas informações não
// sejam coerentes com o formato exigido ou o novo id já exista na lista
int editar_passageiro(Passageiro *passageiro, int id, char *nome,
                      char *endereco, Lista_Passageiro *lista_passageiro) {
  if (lista_passageiro == NULL || lista_passageiro->primeiro == NULL ||
      passageiro == NULL || id < 0 || nome == NULL || endereco == NULL ||
      buscar_passageiro(lista_passageiro, passageiro->id) == NULL ||
      (passageiro->id != id &&
       buscar_passageiro(lista_passageiro, id) != NULL)) {
    return 0;
  }
  passageiro->id = id;
  strcpy(passageiro->nome, nome);
  strcpy(passageiro->endereco, endereco);
  return 1;
}

// Recupera <id,nome,endereco> de um passageiro, caso passageiro seja
// NULL recupera <-1,'NULL','NULL'>
void acessar_passageiro(Passageiro *passageiro, int *id, char *nome,
                        char *endereco) {
  if (passageiro != NULL) {
    *id = passageiro->id;
    strcpy(nome, passageiro->nome);
    strcpy(endereco, passageiro->endereco);
  } else {
    *id = -1;
    strcpy(nome, "NULL");
    strcpy(endereco, "NULL");
  }
}

// Se origem ou destino forem NULL, retorna -1
// se codigo, origem ou destino forem INVÁLIDOS, retorna -1
// se todos os parametros forme validos, retorna 1
int verif_parametros2(int codigo, char *origem, char *destino) {
  if (origem == NULL || destino == NULL) {
    return -1;
  } else if (codigo < 0 || strlen(origem) > 50 || strlen(destino) > 50) {
    return -1;
  } else {
    return 1;
  }
}

// Recebe os campos <codigo,origem,destino> e retorna um voo com
// com esses valores ou NULL caso codigo<0, origem=NULL ou endereco=NULL
Voo *criar_voo(int codigo, char *origem, char *destino) {
  // isdigit(int c) : retorna 0 se não for do tipo inteiro
  if (verif_parametros2(codigo, origem, destino) == -1) {
    return NULL;
  }
  Voo *voo = (Voo *)malloc(sizeof(Voo));
  voo->codigo = codigo;
  strcpy(voo->origem, origem);
  strcpy(voo->destino, destino);
  return voo;
}

// Cria e retorna um No com um voo dentro
// retorna NULL caso voo seja NULL
No_voo *criar_no_voo(Voo *voo) {
  No_voo *no_voo = (No_voo *)malloc(sizeof(No_voo));
  if (voo != NULL) {
    no_voo->voo = voo;

    return no_voo;
  }
  return NULL; // retorna NULL se voo for nulo
}

// Inicia e retorna uma lista_voo
Lista_Voo *criar_lista_voo() {
  Lista_Voo *lista_voo = (Lista_Voo *)malloc(sizeof(Lista_Voo));
  return lista_voo;
}

// verifica se existe um voo com o codigo inserido, retorna NULL se o
// codigo não existir, a lista for vazia ou se a lista for NULL
Voo *buscar_voo(int codigo, Lista_Voo *lista_voo) {
  if (lista_voo == NULL || lista_voo->primeiro == NULL) {
    return NULL;
  }
  No_voo *no_aux = lista_voo->primeiro;
  Voo *aux = no_aux->voo;
  while (no_aux != NULL) {
    // percorre a lista ate achar o voo de CODIGO desejado
    if (aux->codigo == codigo) {
      return aux; // retorna o voo desejado
    }
    no_aux = no_aux->proximo;
    if (no_aux != NULL) {
      aux = no_aux->voo; // pega o voo do novo no_aux
    }
  }
  return NULL;
}

// Insere um novo no_voo a lista, retorna 1 se for possivel
// adicionar, retorna 0 caso a lista seja NULL,caso o no seja NULL ou já exista
// o codigo do voo
int inserir_voo(Lista_Voo *lista_voo, No_voo *no_voo) {
  if (lista_voo == NULL || no_voo == NULL ||
      buscar_voo(no_voo->voo->codigo, lista_voo) != NULL) {
    return 0;
  }
  No_voo *aux = lista_voo->primeiro;
  no_voo->proximo = aux;
  lista_voo->primeiro = no_voo;
  return 1;
}

// Compara dois voos
// Se os voo forem iguais, retorna 1
// Senão, retorna 0
int comp_voo(No_voo *voo, Voo *voo2) {
  Voo *voo1 = voo->voo;
  if (voo1->codigo == voo2->codigo) {
    if (strcmp(voo1->origem, voo2->origem) == 0) {
      if (strcmp(voo1->destino, voo2->destino) == 0) {
        return 1;
      } else {
        return 0;
      }
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

// Remove e retorna no_voo com codigo inserido, retorna NULL caso codigo não
// seja encontrado, a lista esteja vazia ou seja NULL
No_voo *remover_voo(int codigo, Lista_Voo *lista_voo) {
  if (buscar_voo(codigo, lista_voo) != NULL) {
    No_voo *aux_ant = NULL;
    No_voo *aux = lista_voo->primeiro;
    while (aux->voo->codigo != codigo) {
      aux_ant = aux;
      aux = aux->proximo;
    }
    if (aux_ant == NULL) {
      lista_voo->primeiro = aux->proximo;
      return aux;
    }
    aux_ant->proximo = aux->proximo;
    return aux;
  }
  return NULL;
}

// Modifica dados de um voo dentro da lista inserida
// retorna 1 caso tenha sido possivel realizar a modificação
// retorna 0 caso a lista seja NULL, a lista seja vazia,
// o voo não seja encontrado ou as novas informações não
// sejam coerentes com o formato exigido ou o novo codigo já exista na lista
int editar_voo(Voo *voo, int codigo, char *origem, char *destino,
               Lista_Voo *lista_voo) {
  if (lista_voo == NULL || lista_voo->primeiro == NULL || voo == NULL ||
      codigo < 0 || origem == NULL || destino == NULL ||
      buscar_voo(voo->codigo, lista_voo) == NULL ||
      (voo->codigo != codigo && buscar_voo(codigo, lista_voo) != NULL)) {
    return 0;
  }
  voo->codigo = codigo;
  strcpy(voo->origem, origem);
  strcpy(voo->destino, destino);
  return 1;
}

// Recupera <codigo,origem,destino> de um voo, caso voo seja
// NULL recupera <-1,'NULL','NULL'>
void acessar_voo(Voo *voo, int *codigo, char *origem, char *destino) {
  if (voo != NULL) {
    *codigo = voo->codigo;
    strcpy(origem, voo->origem);
    strcpy(destino, voo->destino);
  } else {
    *codigo = -1;
    strcpy(origem, "NULL");
    strcpy(destino, "NULL");
  }
}

// Recebe os campos <dia,mes,ano> e retorna uma data com
// com esses valores ou NULL caso dia, mes, ano nao sejam validos
Data *add_data(int dia, int mes, int ano) {
  if (dia > 0 && verifica_dias(dia, mes) && mes > 0 && mes <= 12 && ano > 0) {
    Data *data = (Data *)malloc(sizeof(Data));
    data->dia = dia;
    data->mes = mes;
    data->ano = ano;

    return data;
  }
  return NULL;
}

// ==============================================================================
// RESERVA
// ==============================================================================

// Cria uma reserva com os valores de <codigo, data_viagem, passageiro, voo,
// assento> Retorna NULL se algum parametro for invalido
Reserva *criar_reserva(int codigo, Data *data_viagem, Passageiro *passageiro,
                       Voo *voo, Assento assento) {
  if (codigo >= 0 && voo != NULL && data_viagem != NULL && passageiro != NULL &&
      assento >= A0 && assento <= C9) {
    Reserva *reserva = (Reserva *)malloc(sizeof(Reserva));
    reserva->codigo = codigo;
    reserva->data_viagem = data_viagem;
    reserva->passageiro = passageiro;
    reserva->voo = voo;
    reserva->assento = assento;

    return reserva;
  }
  return NULL;
}

// Busca reserva na agenda pelo codigo
// Retorna NULL se nao achar
Agenda *buscar_agenda(Agenda *agenda, int codigo) {
  if (agenda == NULL || agenda->reserva == NULL || codigo < 0) {
    return NULL;
  }
  Agenda *aux = NULL;
  if (agenda != NULL && codigo >= 0) { // conferir dados validos
    if (agenda->esq != NULL) {         // se a esquerda da agenda for != NULL
      aux = buscar_agenda(agenda->esq, codigo);
    }
    if (agenda->reserva->codigo ==
        codigo) { // se for a reserva procurada, retorna a agenda dessa reserva
      return agenda;
    }
    if (agenda->dir != NULL && aux == NULL) {
      aux = buscar_agenda(agenda->dir, codigo);
    }
  }
  return aux;
}

// Busca reserva na agenda pelo codigo
// Retorna NULL se nao achar
Reserva *buscar_reserva(Agenda *agenda, int codigo) {
  if (agenda == NULL || codigo < 0 || agenda->reserva == NULL) {
    return NULL;
  }
  Agenda *aux = buscar_agenda(agenda, codigo);
  if (aux == NULL) {
    return NULL;
  }
  return aux->reserva;
  // retorna a reserva se dados forem validos
}

// Aloca memoria para uma agenda
Agenda *criar_agenda() {
  Agenda *agenda = (Agenda *)malloc(sizeof(Agenda));
  return agenda;
}

// Se der certo inserir, retorna 1. Caso não seja possível, retorna 0
int inserir_agenda(Agenda *agenda, Reserva *reserva) {
  if (reserva == NULL || agenda == NULL ||
      buscar_reserva(agenda, reserva->codigo) != NULL) {
    return 0;
  } else if (agenda->reserva == NULL) {
    // a agenda foi inicializada mas não tem nada, então inserimos a raiz
    agenda->reserva = reserva;
  } else if (passado_futuro(reserva->data_viagem,
                            agenda->reserva->data_viagem) == 1 ||
             passado_futuro(reserva->data_viagem,
                            agenda->reserva->data_viagem) == 0) {
    if (agenda->esq == NULL) {
      Agenda *aux = (Agenda *)malloc(sizeof(Agenda));
      aux->reserva = reserva;
      agenda->esq = aux;
    } else {
      inserir_agenda(agenda->esq, reserva);
    }
  } else {
    if (agenda->dir == NULL) {
      Agenda *aux = (Agenda *)malloc(sizeof(Agenda));
      aux->reserva = reserva;
      agenda->dir = aux;
    } else {
      inserir_agenda(agenda->dir, reserva);
    }
  }
  return 1;
}

// editar os valores de um nó da agenda
int editar_agenda(Agenda *agenda, Reserva *reserva) {
  if (agenda != NULL && agenda->reserva != NULL) {
    remover_agenda(agenda, reserva->codigo);
    inserir_agenda(agenda, reserva);
    return 1;
  }
  return 0; // agenda null ou vazia
}

// Recebe novos dados e modifica os dados de uma reserva
int editar_reserva(Reserva *reserva, int codigo, Data *data_viagem,
                   Passageiro *passageiro, Voo *voo, Assento assento,
                   Agenda *agenda) {
  if (agenda != NULL && codigo >= 0 && data_viagem != NULL &&
      verifica_dias(data_viagem->dia, data_viagem->mes) && passageiro != NULL &&
      voo != NULL && assento >= A0 && assento <= C9) {
    reserva->codigo = codigo;
    reserva->data_viagem = data_viagem;
    reserva->passageiro = passageiro;
    reserva->voo = voo;
    reserva->assento = assento;
    editar_agenda(agenda, reserva);
    return 1;
  }
  return 0;
}

// Encontrar o pai do nó fornecido
Agenda *busca_pai(Agenda *agenda, Agenda *aux_agenda) {
  if (agenda->reserva == aux_agenda->reserva) {
    return NULL;
  }
  Agenda *aux = NULL;
  if (agenda->esq != NULL) {
    if (agenda->esq->reserva == aux_agenda->reserva) {
      return agenda;
    }
    aux = busca_pai(agenda->esq, aux_agenda);
  }
  if (aux == NULL && agenda->dir != NULL) {
    if (agenda->dir->reserva == aux_agenda->reserva) {
      return agenda;
    }
    aux = busca_pai(agenda->dir, aux_agenda);
  }
  return aux;
}

// Busca o primeiro no mais à esquerda
Agenda *antecessor(Agenda *agenda) {
  Agenda *antecessor = max(agenda->esq);
  return antecessor;
}

// Busca o primeiro no mais à direita
Agenda *sucessor(Agenda *agenda) {
  Agenda *sucessor = min(agenda->dir);
  return sucessor;
}

// Maximo da agenda
// Percorre pela direita ate o ultimo elemento
Agenda *max(Agenda *agenda) {
  Agenda *max = agenda;
  while (max->dir != NULL) {
    max = max->dir;
  }
  return max;
}

// Minimo da agenda
// Percorre pela esquerda ate o ultimo elemento
Agenda *min(Agenda *agenda) {
  Agenda *min = agenda;
  while (min->esq != NULL) {
    min = min->esq;
  }
  return min;
}

// Função para auxiliar a função remover/serve para ajeitar os nos.
void transplantar(Agenda *agenda, Agenda *aux1, Agenda *aux2) {
  Agenda *pai_aux1 =
      busca_pai(agenda, aux1); // busca o pai do no aux1 na agenda
  if (pai_aux1 == NULL) {
    agenda = aux2;
  } else if (aux1 == pai_aux1->esq) {
    pai_aux1->esq = aux2;
  } else {
    pai_aux1->dir = aux2;
  }
}

// Retorna NULL caso a agenda seja NULL ou não exista dentro da agenda
// Remove o nó com o código fornecido da agenda e retorna a agenda removida
Agenda *remover_agenda(Agenda *agenda, int codigo) {
  Agenda *aux = buscar_agenda(agenda, codigo);
  if (aux == NULL) {
    return NULL;
  }
  if (aux->esq == NULL) { // se o no esquerdo for NULL, transplantar agenda
    transplantar(agenda, aux, aux->dir);
  } else if (aux->dir == NULL) { // se o no direito for NULL, transplantar agenda
    transplantar(agenda, aux, aux->esq);
  } else {
    Agenda *suc = sucessor(aux);
    Agenda *pai_aux2 = busca_pai(agenda, aux->esq);
    Agenda *pai_aux3 = busca_pai(agenda, aux->dir);
    transplantar(agenda, suc, suc->dir);
    suc->esq = aux->esq;
    pai_aux2 = suc;
    suc->dir = aux->dir;
    pai_aux3 = suc;
    transplantar(agenda, aux, suc);
  }
  return aux;
}

// Separa todas as reservas de um certo id da agenda em outra agenda separada
Reserva *busca_id(Agenda *agenda, int id) {
  Reserva *aux = NULL;
  if (agenda->esq != NULL) {
    aux = busca_id(agenda->esq, id);
  }
  if (agenda->reserva->passageiro->id == id) {
    return agenda->reserva;
  }
  if (aux == NULL && agenda->dir != NULL) {
    aux = busca_id(agenda->dir, id);
  }
  return aux;
}

// busca reservas com o mesmo codigo de voo
void busca_codigo(Agenda *agenda, Agenda *agenda_codigo, int codigo) {
  if (agenda->esq != NULL) {
    busca_codigo(agenda->esq, agenda_codigo, codigo);
  }
  if (agenda->reserva->voo->codigo == codigo) {
    inserir_agenda(agenda_codigo, agenda->reserva);
  }
  if (agenda->dir != NULL) {
    busca_codigo(agenda->dir, agenda_codigo, codigo);
  }
}

// busca uma reserva pelo id do passageiro e pelo codigo do voo
Reserva *busca_id_codigo(Agenda *agenda, int id, int codigo) {
  if (agenda == NULL || agenda->reserva == NULL || id < 0 || codigo < 0) {
    return NULL;
  }
  Agenda *agenda_codigo = criar_agenda();
  busca_codigo(agenda, agenda_codigo, codigo);
  if (agenda_codigo->reserva == NULL) {
    return NULL;
  }
  Reserva *reserva = busca_id(agenda_codigo, id);
  return reserva;
}

// Busca uma uma reserva pela data dentro de uma arvore
void busca_data(Agenda *agenda, Agenda *agenda_data, Data *data) {
  if (agenda->esq != NULL) {
    busca_data(agenda->esq, agenda_data, data);
  }
  if (agenda->reserva->data_viagem->ano == data->ano &&
      agenda->reserva->data_viagem->mes == data->mes &&
      agenda->reserva->data_viagem->dia == data->dia) {
    inserir_agenda(agenda_data, agenda->reserva);
  }
  if (agenda->dir != NULL) {
    busca_data(agenda->dir, agenda_data, data);
  }
}

// Busca uma reserva pelo id do passageiro e pela data
Reserva *busca_id_data(Agenda *agenda, int id, Data *data) {
  if (agenda == NULL || id < 0 || data == NULL || agenda->reserva == NULL) {
    return NULL;
  }
  Agenda *agenda_data = criar_agenda();
  busca_data(agenda, agenda_data, data);
  if (agenda_data == NULL) {
    return NULL;
  }
  Reserva *reserva = busca_id(agenda, id);
  return reserva;
}

// TABELA HASH !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// TABELA HASH !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// TABELA HASH !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// TABELA HASH !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// TABELA HASH !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define M 23
#define hash(v, M) (v % M)

/* ********************************************************************
Valor da tabela Hash DEVE ser entre 0 e TAMANHO_TABELA - 1
Ou seja, 0 <= valor_tabela_hash < TAMANHO_TABELA
******************************************************************** */
// Para isso, basta fazer:
// valor_tabela_hash = valor_tabela_hash % TAMANHO_TABELA

// Inicializa e cria um trecho com uma reserva
// Retorna o trecho se reserva != NULL e retorna NULL se reserva == NULL
Trecho *criar_trecho(Reserva *reserva) {
  if (reserva == NULL) {
    return NULL;
  } else {
    Trecho *trecho = (Trecho *)malloc(sizeof(Trecho *));
    trecho->reserva = reserva;
    return trecho;
  }
}

// Inicializa e retorna uma viagem
Viagem *criar_viagem() {
  Viagem *viagem = (Viagem *)malloc(sizeof(Viagem));
  return viagem;
}

// Retorna o ultimo trecho de uma viagem
Trecho *ult_trecho(Viagem *viagem) {
  Trecho *aux = viagem->trechos;
  while (aux->proximo != NULL) {
    aux = aux->proximo; // quando o proximo de aux for NULL, aux é o ultimo
  }
  return aux;
}

// Verifica se o trecho da viagem é valido 
// Retorna 1 se for valido e 0 se for invalido
int verifica_trechos(Viagem *viagem, Trecho *trecho) {
  Trecho *aux = ult_trecho(viagem);
  if (strcmp(aux->reserva->voo->destino, trecho->reserva->voo->origem) == 0 &&
      aux->reserva->passageiro->id == trecho->reserva->passageiro->id &&
      passado_futuro(aux->reserva->data_viagem, trecho->reserva->data_viagem) == 1) {
    return 1;
  } else {
    return 0;
  }
}

// Insere um trecho em uma viagem
// Retorna 1 se foi possivel inserir e 0 se não foi possivel
int inserir_trecho(Viagem *viagem, Trecho *trecho) {
  if (viagem == NULL || trecho == NULL) {
    return 0;
  }
  if (viagem->trechos == NULL) {
    viagem->trechos = trecho;
    return 1;
  } else {
    int x = verifica_trechos(viagem, trecho);
    if (x == 1) {
      ult_trecho(viagem)->proximo = trecho;
      return 1;
    }
  }
  return 0;
}

// Busca um trecho de uma viagem pelo seu codigo
Trecho *buscar_trecho(Viagem *viagem, int codigo) {
  Trecho *aux = viagem->trechos;
  while (aux != NULL) {
    if (aux->reserva->codigo == codigo) {
      return aux;
    }
    aux = aux->proximo;
  }
  return NULL;
}

// Auxiliar do remove_trecho
Trecho *buscar_ant(Viagem *viagem, int codigo) {
  Trecho *aux = viagem->trechos;
  while (aux != NULL) {
    if (aux->proximo->reserva->codigo == codigo) {
      return aux;
    }
    aux = aux->proximo;
  }
  return NULL;
}

// Remove um trecho de uma viagem pelo seu codigo
Trecho *remover_trecho(Viagem *viagem, int codigo) {
  if (viagem == NULL || viagem->trechos == NULL || codigo < 0) {
    return NULL;
  }
  Trecho *aux = buscar_trecho(viagem, codigo);
  if (aux != NULL) {
    Trecho *ant = buscar_ant(viagem, codigo);
    ant->proximo = aux->proximo;
  }
  return aux;
}

// Inicia a tabela_hash
Viagem **inicializar_tabela() {
  Viagem **tabela_hash;
  tabela_hash = (Viagem **)malloc(M * sizeof(Viagem *));
  return tabela_hash;
}
// Inicia a tabela_viagens
TabelaViagem *inicializar_tabela_Viagem() {
  Viagem** tabela_hash=inicializar_tabela();
  TabelaViagem *Tabela_Viagem = (TabelaViagem *)malloc(sizeof(TabelaViagem));
  Tabela_Viagem->tamanho = M; // valor padrão inicial
  Tabela_Viagem->tabela_hash = tabela_hash;
  return Tabela_Viagem;
}
// Função para inserir viagens na tabela hash, caso consiga inserir retorna 1,
// caso não consiga inserir retorna 0.
int inserir_na_tabela(Viagem *tabela_hash[M], Viagem *viagem) {
  if(viagem==NULL){
    return 0;
  }
  int v = calculo_chave(viagem);
  // v é somatorio dos codigos das reservas + ID passageiro
  int h = hash(v, M); // faz v % M
  if (busca_tabela_id(tabela_hash, viagem->trechos->reserva->passageiro->id) ==
      NULL) {
    if (tabela_hash[h] == NULL) {
      tabela_hash[h] = viagem;
      return 1;
    }
  } else {
    if (verifica_cronologia(
            busca_tabela_id(tabela_hash,
                            viagem->trechos->reserva->passageiro->id),
            viagem) == 1) {
      if (tabela_hash[h] == NULL) {
        tabela_hash[h] = viagem;
        return 1;
      }
    }
  }
  return 0;
}

// Retorna a primeira data de uma viagem 
Data *prim_data(Viagem *viagem) {
  Data *data = viagem->trechos->reserva->data_viagem;
  return data;
}

// Retorna a ultima data de uma viagem 
Data *ult_data(Viagem *viagem) {
  Trecho *aux = viagem->trechos;
  while (aux->proximo != NULL) {
    aux = aux->proximo; // quando o proximo for NULL, é o ultimo
  }
  return aux->reserva->data_viagem;
}

// Verifica a data das viagens
int verifica_cronologia(ListaAuxViagem *lista, Viagem *viagem) {
  int k = 0;
  if (lista->prox != NULL) {
    k = verifica_cronologia(lista->prox, viagem);
  }
  if ((passado_futuro(prim_data(lista->viagem), ult_data(viagem)) == 2 ||
       passado_futuro(ult_data(lista->viagem), prim_data(viagem)) == 1) &&
      (k != 0 || lista->prox == NULL)) {
    return 1;
  } else {
    return 0;
  }
}

// Função de busca
ListaAuxViagem *busca_tabela_id(Viagem *tabela_hash[M], int id) {
  int h = 0;
  ListaAuxViagem *lista_aux_viagem = (ListaAuxViagem *)malloc(sizeof(ListaAuxViagem));
  //lista_aux_viagem->prox = NULL; 
  ListaAuxViagem *aux = lista_aux_viagem->prox; 
  while (h != M) {
    if (tabela_hash[h] != NULL &&
        tabela_hash[h]->trechos->reserva->passageiro->id == id) {
      aux = (ListaAuxViagem *)malloc(sizeof(ListaAuxViagem));
      aux->viagem = tabela_hash[h];
      aux = aux->prox;
      h++;
    }
  }
  return lista_aux_viagem->prox;
}

// A partir da chave colocada a função irá encontrar a viagem que corresponde à chave na tabela hash
Viagem *buscar_chave(Viagem *tabela_hash[M], int chave) {
  int h = hash(chave, M);
  return tabela_hash[h];
}

// Função Remover - remove viagem de hash_id desejado da tabela_hash
/* Se não foi possivel fazer a remoção, retorna 0
Se foi possivel fazer a remoção, retorna 1 */
Viagem *remover_tabela(Viagem *tabela_hash[M], int hash_id) {
  int h = hash(hash_id, M);
  Viagem *aux = NULL;
  if (tabela_hash != NULL && hash_id >= 0) {
    aux = tabela_hash[h];
  }
  if (aux != NULL) {
    tabela_hash[h] = NULL; // remove da tabela
  }
  return aux;
}

// Somatorio dos codigos das reservas
int calculo_chave_aux(Trecho *aux) {
  if (aux->proximo == NULL) { // quando for NULL, retorna o valor final
    return aux->reserva->codigo;
  }
  return (aux->reserva->codigo) + calculo_chave_aux(aux->proximo);
}

// Calcula o indice final da hashmap
// Retorna -1 se a viagem for NULL e retorna o indice se viagem != NULL
int calculo_chave(Viagem *viagem) {
  if (viagem != NULL) {
    Trecho *aux = viagem->trechos;
    int soma_reserva = calculo_chave_aux(aux);
    soma_reserva = soma_reserva + (aux->reserva->passageiro->id);
    return soma_reserva; // somatorio dos codigos das reservas + ID passageiro
  } else {
    return -1;
  }
}


// Imprime o assento
void mostrar_assento(Assento assento) {
  switch (assento) {
  case 0:
    printf("Assento :A0");
    break;
  case 1:
    printf("Assento :B0");
    break;
  case 2:
    printf("Assento :C0");
    break;
  case 3:
    printf("Assento :A1");
    break;
  case 4:
    printf("Assento :B1");
    break;
  case 5:
    printf("Assento :C1");
    break;
  case 6:
    printf("Assento :A2");
    break;
  case 7:
    printf("Assento :B2");
    break;
  case 8:
    printf("Assento :C2");
    break;
  case 9:
    printf("Assento :A3");
    break;
  case 10:
    printf("Assento :B3");
    break;
  case 11:
    printf("Assento :C3");
    break;
  case 12:
    printf("Assento :A4");
    break;
  case 13:
    printf("Assento :B4");
    break;
  case 14:
    printf("Assento :C4");
    break;
  case 15:
    printf("Assento :A5");
    break;
  case 16:
    printf("Assento :B5");
    break;
  case 17:
    printf("Assento :C5");
    break;
  case 18:
    printf("Assento :A6");
    break;
  case 19:
    printf("Assento :B6");
    break;
  case 20:
    printf("Assento :C6");
    break;
  case 21:
    printf("Assento :A7");
    break;
  case 22:
    printf("Assento :B7");
    break;
  case 23:
    printf("Assento :C7");
    break;
  case 24:
    printf("Assento :A8");
    break;
  case 25:
    printf("Assento :B8");
    break;
  case 26:
    printf("Assento :C8");
    break;
  case 27:
    printf("Assento :A9");
    break;
  case 28:
    printf("Assento :B9");
    break;
  case 29:
    printf("Assento :C9");
    break;
  }
}

// Imprime o itinerario da tabela viagem
void mostrar_itinerario(TabelaViagem *tabela_viagem, int chave) {
  Viagem *viagem = buscar_chave(tabela_viagem->tabela_hash, chave);
  if (viagem == NULL) {
    printf("Viagem não encontrada.\n");
  }
  
  printf("\n");
  printf("Informações PASSAGEIRO:\n");
  printf("ID: %d\n", viagem->trechos->reserva->passageiro->id);
  printf("Nome: %s\n", viagem->trechos->reserva->passageiro->nome);
  printf("Endereço: %s\n", viagem->trechos->reserva->passageiro->endereco);
  printf("Informações TRECHOS:\n");
  Trecho *aux = viagem->trechos;
  int contador = 0;
  while (aux != NULL) {
    contador++;
    printf("Reserva: %d\n", contador);
    printf("Codigo da reserva: %d\n", aux->reserva->codigo);
    mostrar_assento(aux->reserva->assento);
    printf("\n");
    printf("Codigo do voo: %d\n", aux->reserva->voo->codigo);
    printf("Origem do voo: %s\n", aux->reserva->voo->origem);
    printf("Destino do voo: %s\n", aux->reserva->voo->destino);
    aux=aux->proximo;
  }
}