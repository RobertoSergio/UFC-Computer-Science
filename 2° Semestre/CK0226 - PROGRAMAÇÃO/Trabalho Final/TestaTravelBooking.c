#include "TravelBooking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 23

struct tabela_viagem {
  int tamanho;
  Viagem **tabela_hash;
};

//=============================================== PASSAGEIRO

void teste_criar_passageiro_dados_validos(Passageiro *passageiro) {
  if (passageiro != NULL) {
    printf("teste_criar_passageiro_dados_validos PASSOU\n");
  } else {
    printf("teste_criar_passageiro_dados_validos NÃO PASSOU\n");
  }
}

void teste_criar_passageiro_dados_nulos() {
  Passageiro *passageiro = criar_passageiro(0, NULL, NULL);
  if (passageiro == NULL) {
    printf("teste_criar_passagero_dados_nulos PASSOU\n");
  } else {
    printf("teste_criar_passagero_dados_nulos NÃO PASSOU\n");
  }
}

void teste_criar_passageiro_dados_invalidos(Passageiro *passageiro) {
  if (passageiro == NULL) {
    printf("teste_criar_passagero_dados_invalidos PASSOU\n");
  } else {
    printf("teste_criar_passagero_dados_invalidos NÃO PASSOU\n");
  }
}

void teste_criar_no_passageiro_validos(No_passageiro *no_passageiro) {
  // vc esqueceu de declarar o struct No_passageiro*
  if (no_passageiro != NULL) {
    printf("teste_cria_no_passageiro_validos PASSOU\n");
    Lista_Passageiro *lista = criar_lista_passageiro();
  } else {
    printf("teste_cria_no_passageiro_validos NÃO PASSOU\n");
  }
}

void teste_criar_no_passageiro_nulos() {
  Passageiro *passageiro = NULL;
  No_passageiro *no = criar_no_passageiro(passageiro);
  if (no == NULL) {
    printf("teste_criar_no_passageiro_nulos PASSOU\n");
  } else {
    printf("teste_criar_no_passageiro_nulos NÃO PASSOU\n");
  }
}

void teste_criar_lista_passageiro_validos(Lista_Passageiro *lista) {
  if (lista != NULL) {
    printf("teste_criar_lista_passageiro_validos PASSOU\n");
  } else {
    printf("testecriar_lista_passageiro_validos NÃO PASSOU\n");
  }
}

//----------------------------------------------------------INSERIR PASSAGEIRO
void teste_inserir_lista_passageiro_com_dados_validos(int aux) {
  if (aux == 1) {
    printf("teste_inserir_passageiro_com_dados_validos PASSOU\n");
  } else {
    printf("teste_inserir_passageiro_com_dados_validos NÃO PASSOU\n");
  }
}

void teste_inserir_lista_passageiro_com_dados_invalidos(int aux2) {
  if (aux2 == 0) {
    printf("teste_inserir_passageiro_com_dados_invalidos PASSOU\n");
  } else {
    printf("teste_inserir_passageiro_com_dados_invalidos NÃO PASSOU\n");
  }
}

void teste_inserir_lista_passageiro_com_dados_nulos() {
  Lista_Passageiro *lista = criar_lista_passageiro();
  if (inserir_passageiro(lista, NULL) == 0) {
    Passageiro *passageiro1 = criar_passageiro(1, "Jorge", "Uberlândia");
    No_passageiro *no1 = criar_no_passageiro(passageiro1);
    if (inserir_passageiro(NULL, no1) == 0) {
      if (inserir_passageiro(NULL, NULL) == 0) {
        printf("teste_inserir_passageiro_com_dados_nulos PASSOU.\n");
      } else {
        printf("teste_inserir_passageiro_com_dados_nulos NÃO PASSOU.\n");
      }
    } else {
      printf("teste_inserir_passageiro_com_dados_nulos NÃO PASSOU.\n");
    }
  } else {
    printf("teste_inserir_passageiro_com_dados_nulos NÃO PASSOU.\n");
  }
}

//----------------------------------------------------------BUSCAR PASSAGEIRO

void teste_busca_passageiro_validos(Passageiro *passageiro1,
                                    Passageiro *passageiro2) {
  if (passageiro1 == passageiro2) {
    printf("teste_busca_passageiro_validos PASSOU\n");
  } else {
    printf("teste_busca_passageiro_validos NÃO PASSOU\n");
  }
}

void teste_busca_passageiro_invalidos(Passageiro *passageiro) {
  if (passageiro == NULL) {
    printf("teste_busca_passageiro_invalidos PASSOU\n");
  } else {
    printf("teste_busca_passageiro_invalidos NÃO PASSOU\n");
  }
}

void teste_busca_passageiro_nulos() {
  Lista_Passageiro *lista_passageiro = criar_lista_passageiro();
  Passageiro *aux = buscar_passageiro(NULL, 1);

  if (aux == NULL && buscar_passageiro(lista_passageiro, 1) == NULL) {
    printf("teste_busca_passageiro_nulos PASSOU \n");
  } else {
    printf("teste_busca_passageiro_nulos NÃO PASSOU \n");
  }
}

//----------------------------------------------------------REMOVER PASSAGEIRO

void teste_remove_passageiro_validos(Passageiro *passageiro,
                                     Passageiro *passageiro1) {
  if (passageiro == passageiro1) {
    printf("teste_remove_passageiro_validos PASSOU\n");
  } else {
    printf("teste_remove_passageiro_validos NÃO PASSOU\n");
  }
}

void teste_remove_passageiro_invalidos(Passageiro *passageiro) {
  if (passageiro == NULL) {
    printf("teste_remove_passageiro_invalidos PASSOU\n");
  } else {
    printf("teste_remove_passageiro_invalidos NÃO PASSOU\n");
  }
}

void teste_remove_passageiro_nulos() {
  Lista_Passageiro *lista_passageiro = NULL;
  if (remover_passageiro(NULL, 1) == NULL) {
    printf("teste_remover_passageiros_nulos PASSOU'\n");
  } else {
    printf("teste_remover_passageiros_nulos NÃO PASSOU'\n");
  }
}
//----------------------------------------------------------EDITAR PASSAGEIRO
void teste_editar_passageiro_validos(int aux) {

  if (aux == 1) {
    printf("teste_editar_passageiro_validos PASSOU\n");
  } else {
    printf("teste_editar_passageiro_validos NÃO PASSOU\n");
  }
}

void teste_editar_passageiro_invalidos(int aux_editar_passageiro2,
                                       int aux_editar_passageiro3,
                                       int aux_editar_passageiro4) {
  if (aux_editar_passageiro2 == 0 || aux_editar_passageiro3 == 0 ||
      aux_editar_passageiro4 == 0) {
    printf("teste_editar_passageiro_invalidos PASSOU\n");
  } else {
    printf("teste_editar_passageiro_invalidos NÃO PASSOU\n");
  }
}

void teste_editar_passageiro_nulos() {
  Passageiro *passageiro = NULL;
  Lista_Passageiro *lista_passageiro = NULL;
  char nome[50], endereco[50];
  Lista_Passageiro *lista_passageiro_2 = criar_lista_passageiro();
  Passageiro *passageiro1 = criar_passageiro(3, "Beto", "Amapa");
  Passageiro *passageiro2 = criar_passageiro(1, "Fluvio", "Fortal");
  Passageiro *passageiro3 = criar_passageiro(2, "Nicolas", "Russas");
  Passageiro *passageiro4 = criar_passageiro(4, "Julia", "Rio");
  No_passageiro *no1 = criar_no_passageiro(passageiro1);
  No_passageiro *no2 = criar_no_passageiro(passageiro2);
  No_passageiro *no3 = criar_no_passageiro(passageiro3);
  No_passageiro *no4 = criar_no_passageiro(passageiro4);
  inserir_passageiro(lista_passageiro, no1);
  inserir_passageiro(lista_passageiro, no2);
  inserir_passageiro(lista_passageiro, no3);
  inserir_passageiro(lista_passageiro, no4);
  if (editar_passageiro(passageiro, 3, "Beto", "Amapa", lista_passageiro_2) ==
      0) {
    if (editar_passageiro(passageiro1, 3, NULL, "Amapa", lista_passageiro_2) ==
        0) {
      if (editar_passageiro(passageiro1, 3, "Beto", NULL, lista_passageiro_2) ==
          0) {
        if (editar_passageiro(passageiro1, 3, "Beto", "Amapa",
                              lista_passageiro) == 0) {
          printf("teste_editar_passageiro_nulos PASSOU\n");
        } else {
          printf("teste_editar_passageiro_nulos NÃO PASSOU\n");
        }
      } else {
        printf("teste_editar_passageiro_nulos NÃO PASSOU\n");
      }
    } else {
      printf("teste_editar_passageiro_nulos NÃO PASSOU\n");
    }
  } else {
    printf("teste_editar_passageiro_nulos NÃO PASSOU\n");
  }
}

//----------------------------------------------------------ACESSAR PASSAGEIRO

void teste_acessar_passageiro_validos(Passageiro *passageiro) {
  int id;
  char nome[50];
  char endereco[50];
  acessar_passageiro(passageiro, &id, nome, endereco);
  if (id == 1 && strcmp(nome, "João Lucas") == 0 &&
      strcmp(endereco, "Russas") == 0) {
    printf("teste_acessa_passageiro_validos PASSOU \n");
  } else {
    printf("teste_acessa_passageiro_validos NÃO PASSOU \n");
  }
}

void teste_acessar_passageiro_nulos() {
  int id;
  char nome[50];
  char endereco[50];

  Passageiro *passageiro1 = NULL;
  acessar_passageiro(passageiro1, &id, nome, endereco);
  if (id == -1 && strcmp(nome, "NULL") == 0 && strcmp("NULL", endereco) == 0) {
    printf("teste_acessa_passageiro_nulos PASSOU \n");
  } else {
    printf("teste_acessa_passageiro_nulos NÃO PASSOU \n");
  }
}

//================================================ VOO
//================================================ VOO
//================================================ VOO

void teste_criar_voo_dados_validos(Voo *voo) {
  if (voo != NULL) {
    printf("teste_criar_voo PASSOU com dados válidos.\n");
  } else {
    printf("teste_criar_voo NÃO PASSOU com dados válidos.\n");
  }
}

void teste_criar_voo_dados_invalidos(Voo *voo) { // incompleto?
  if (voo == NULL) {
    printf("teste_criar_voo_dados_invalidos PASSOU\n");
  } else {
    printf("teste_criar_voo_dados_invalidos NÃO PASSOU\n");
  }
}

void teste_criar_voo_dados_nulos() {
  Voo *voo = criar_voo(-1, NULL, NULL);
  if (voo == NULL) { //
    printf("teste_criar_voo PASSOU com dados nulos.\n");
  } else {
    printf("teste_criar_voo NÃO PASSOU com dados nulos.\n");
  }
}

void teste_criar_no_voo_validos(No_voo *no_voo) {
  if (no_voo != NULL) {
    printf("teste_criar_no_voo PASSOU com dados válidos.\n");
  } else {
    printf("teste_criar_no_voo NÃO PASSOU com dados válidos.\n");
  }
}

void teste_criar_no_voo_nulos() {
  No_voo *no_voo = criar_no_voo(NULL);

  if (no_voo == NULL) {
    printf("teste_criar_no_voo() PASSOU com dados nulos.\n");
  } else {
    printf("teste_criar_no_voo() NÃO PASSOU com dados nulos.\n");
  }
}

void teste_criar_lista_voo_validos(Lista_Voo *lista) {
  if (lista != NULL) {
    printf("teste_criar_lista_voo_validos() PASSOU\n");
  } else {
    printf("teste_criar_lista_voo_validos NÃO PASSOU\n");
  }
}

//----------------------------------------------------------INSERIR VOO

void teste_inserir_lista_voo_com_dados_validos(int aux) {
  if (aux == 1) {
    printf("teste_inserir_voo_com_dados_validos PASSOU\n");
  } else {
    printf("teste_inserir_voo_com_dados_validos NÃO PASSOU\n");
  }
}

void teste_inserir_lista_voo_com_dados_invalidos(int aux) {
  if (aux == 0) {
    printf("teste_inserir_voo_com_dados_invalidos PASSOU\n");
  } else {
    printf("teste_inserir_voo_com_dados_invalidos NÃO PASSOU\n");
  }
}

void teste_inserir_lista_voo_com_dados_nulos() {
  Lista_Voo *lista = criar_lista_voo();
  if (inserir_voo(lista, NULL) == 0) {
    Voo *voo1 = criar_voo(1, "Paris", "Uberlândia");
    No_voo *no1 = criar_no_voo(voo1);
    if (inserir_voo(NULL, no1) == 0) {
      if (inserir_voo(NULL, NULL) == 0) {
        printf("teste_inserir_lista_voo_com_dados_nulos PASSOU.\n");
      } else {
        printf("Teste_inserir_lista_voo_com_dados_nulos NÃO PASSOU.\n");
      }
    } else {
      printf("Teste_inserir_lista_voo_com_dados_nulos NÃO PASSOU.\n");
    }
  } else {
    printf("teste_inserir_lista_voo_com_dados_nulos NÃO PASSOU.\n");
  }
}

//----------------------------------------------------------BUSCAR VOO

void teste_busca_voo_validos(Voo *voo1, Voo *voo2) {
  if (voo1 = voo2) {
    printf("teste_busca_voo_validos PASSOU\n");
  } else {
    printf("teste_busca_voo_validos NÃO PASSOU\n");
  }
}

void teste_busca_voo_invalidos(Voo *voo) {
  if (voo == NULL) {
    printf("teste_busca_voo_invalidos PASSOU\n");
  } else {
    printf("teste_busca_voo_invalidos NÃO PASSOU\n");
  }
}

void teste_busca_voo_nulos() {
  Lista_Voo *lista_voo = criar_lista_voo();
  Voo *aux = buscar_voo(1, NULL);

  if (aux == NULL || buscar_voo(1, lista_voo) == NULL) {
    printf("teste_busca_voo_nulos PASSOU \n");
  } else {
    printf("teste_busca_voo_nulos NÃO PASSOU \n");
  }
}

//----------------------------------------------------------REMOVER VOO
void teste_remove_voo_dados_validos(No_voo *no_voo, No_voo *no_voo1) {
  if (no_voo == no_voo1) {
    printf("teste_remover_voo_validos PASSOU'\n");
  } else {
    printf("teste_remover_voo_validos NÃO PASSOU\n");
  }
}

void teste_remove_voo_invalidos(No_voo *no_voo) {
  if (no_voo == NULL) {
    printf("teste_remover_voo_invalidos PASSOU'\n");
  } else {
    printf("teste_remover_voo_invalidos NÃO PASSOU\n");
  }
}

void teste_remove_voo_dados_nulos() {
  Lista_Voo *lista_voo = NULL;
  if (remover_voo(1, NULL) == NULL) {
    printf("teste_remover_voo_nulos PASSOU'\n");
  } else {
    printf("teste_remover_voo_nulos NÃO PASSOU'\n");
  }
}

//----------------------------------------------------------EDITAR VOO

void teste_editar_voo_validos(int voo) {
  if (voo == 1) {
    printf("teste_editar_voo_validos PASSOU.\n");
  } else {
    printf("teste_editar_voo_validos NÃO PASSOU.\n");
  }
}

void teste_editar_voos_invalidos(int voo1, int voo2, int voo3) {
  // id errado, dado nulo (?)
  if (voo1 == 0 || voo2 == 0 || voo3 == 0) {
    printf("teste_editar_voo_invalidos PASSOU.\n");
  } else {
    printf("teste_editar_voo_invalidos NÃO PASSOU.\n");
  }
}

void teste_editar_voo_nulos() {
  Voo *voo = NULL;
  Lista_Voo *lista_voo = NULL;
  char origem[50], destino[50];

  Lista_Voo *lista_voo_2 = criar_lista_voo();

  Voo *voo1 = criar_voo(3, "São Paulo", "Amapa");
  Voo *voo2 = criar_voo(1, "Manaus", "Fortal");
  Voo *voo3 = criar_voo(2, "Rio de Janeiro", "Russas");
  Voo *voo4 = criar_voo(4, "Paris", "Rio");

  No_voo *no1 = criar_no_voo(voo1);
  No_voo *no2 = criar_no_voo(voo2);
  No_voo *no3 = criar_no_voo(voo3);
  No_voo *no4 = criar_no_voo(voo4);

  inserir_voo(lista_voo, no1);
  inserir_voo(lista_voo, no2);
  inserir_voo(lista_voo, no3);
  inserir_voo(lista_voo, no4);
  if (editar_voo(voo, 3, "São Paulo", "Amapa", lista_voo_2) == 0) {
    if (editar_voo(voo1, 3, NULL, "Amapa", lista_voo_2) == 0) {
      if (editar_voo(voo1, 3, "São Paulo", NULL, lista_voo_2) == 0) {
        if (editar_voo(voo1, 3, "Beto", "Amapa", lista_voo) == 0) {
          printf("teste_editar_voo_nulos PASSOU\n");
        } else {
          printf("teste_editar_voo_nulos NÃO PASSOU\n");
        }
      } else {
        printf("teste_editar_voo_nulos NÃO PASSOU\n");
      }
    } else {
      printf("teste_editar_voo_nulos NÃO PASSOU\n");
    }
  } else {
    printf("teste_editar_voo_nulos NÃO PASSOU\n");
  }
}

void teste_acessar_voo_validos(Voo *voo1) {
  int codigo;
  char origem[50];
  char destino[50];

  acessar_voo(voo1, &codigo, origem, destino);
  if (codigo == 2 && strcmp(origem, "Nova York") == 0 &&
      strcmp(destino, "Washington DC") == 0) {
    printf("teste_acessa_voo_validos PASSOU.\n");
  } else {
    printf("teste_acessa_voo_validos NÃO PASSOU.\n");
  }
}

void teste_acessar_voo_nulos() {
  int codigo;
  char origem[50];
  char destino[50];

  Voo *voo1 = NULL;
  acessar_voo(voo1, &codigo, origem, destino);
  if (codigo == -1 && strcmp(origem, "NULL") == 0 &&
      strcmp("NULL", destino) == 0) {
    printf("teste_acessa_voo_nulos PASSOU.\n");
  } else {
    printf("teste_acessa_voo_nulos NÃO PASSOU. \n");
  }
}

//================================================ RESERVA
//================================================ RESERVA
//================================================ RESERVA

// data valida
void teste_criar_data_validos(Data *data) {
  if (data != NULL) {
    printf("teste_criar_data_validos PASSOU\n");
  } else {
    printf("teste_criar_data_validos NÃO PASSOU\n");
  }
}

// datas invalidas
void teste_criar_data_invalidos(Data *data1, Data *data2) {
  if (data1 == NULL) {
    if (data2 == NULL) {
      printf("teste_criar_data_invalidos PASSOU\n");
    } else {
      printf("teste_criar_data_invalidos NÃO PASSOU\n");
    }
  } else {
    printf("teste_criar_data_invalidos NÃO PASSOU\n");
  }
}

// dados válidos: código >= 0; voo != NULL; data_viagem != NULL
void teste_criar_reserva_dados_validos(Reserva *reserva) {
  // Reserva *criar_reserva(int codigo, Data *data_viagem, Passageiro
  // *passageiro, Voo *voo, Assento assento)
  if (reserva != NULL) {
    printf("teste_criar_reserva_dados_validos PASSOU.\n");
  } else {
    printf("teste_criar_reserva_dados_validos NÃO PASSOU.\n");
  }
}

// retorna NULL se não é possível criar a reserva (é o que esperamos)
void teste_criar_reserva_dados_invalidos(Reserva *reserva1, Reserva *reserva2,
                                         Reserva *reserva3, Reserva *reserva4,
                                         Reserva *reserva5) {
  // basta uma info inválida que a função retorna NULL

  if (reserva1 == NULL && reserva2 == NULL && reserva3 == NULL &&
      reserva4 == NULL && reserva5 == NULL) {
    printf("teste_criar_reserva_dados_invalidos PASSOU.\n");
  } else {
    printf("teste_criar_reserva_dados_invalidos NÃO PASSOU.\n");
  }
}

// esperamos que retorne NULL caso um dos parâmetros seja NULL
void teste_criar_reserva_dados_nulos(Reserva *reserva1, Reserva *reserva2,
                                     Reserva *reserva3) {
  if (reserva1 == NULL && reserva2 == NULL && reserva3 == NULL) {
    printf("teste_criar_reserva_dados_nulos PASSOU.\n");
  } else {
    printf("teste_criar_reserva_dados_nulos NÃO PASSOU.\n");
  }
}

//----------------------------------------------------------CRIAR AGENDA

void teste_criar_agenda(Agenda *agenda) {
  if (agenda != NULL) {
    printf("teste_criar_agenda PASSOU\n");
  } else {
    printf("teste_criar_agenda NÃO PASSOU\n");
  }
}

//----------------------------------------------------------BUSCAR AGENDA

void teste_buscar_reserva_dados_validos(Agenda *agenda, Reserva *reserva1,
                                        Reserva *reserva2, Reserva *reserva3,
                                        Reserva *reserva4) {
  inserir_agenda(agenda, reserva1);
  inserir_agenda(agenda, reserva2);
  inserir_agenda(agenda, reserva3);
  inserir_agenda(agenda, reserva4);
  if (buscar_reserva(agenda, 1) == reserva1 &&
      buscar_reserva(agenda, 3) == reserva3 &&
      buscar_reserva(agenda, 2) == reserva2 &&
      buscar_reserva(agenda, 4) == reserva4) {
    printf("teste_buscar_reserva_dados_validos PASSOU\n");
  } else {
    printf("teste_buscar_reserva_dados_validos NÃO PASSOU\n");
  }
}

void teste_buscar_reserva_dados_invalidos(Agenda *agenda, Reserva *reserva) {
  inserir_agenda(agenda, reserva);
  if (buscar_reserva(agenda, -1) == NULL) {
    if (buscar_reserva(agenda, 10) == NULL) {
      printf("teste_buscar_reserva_dados_invalidos PASSOU\n");
    } else {
      printf("teste_buscar_reserva_dados_invalidos NÃO PASSOU\n");
    }
  } else {
    printf("teste_buscar_reserva_dados_invalidos NÃO PASSOU\n");
  }
}

void teste_buscar_reserva_dados_nulos(Agenda *agenda) {
  if (buscar_reserva(agenda, 1) == NULL) {
    printf("teste_buscar_reserva_dados_nulos PASSOU\n");
  } else {
    printf("teste_buscar_reserva_dados_nulos NÃO PASSOU\n");
  }
}

//----------------------------------------------------------INSERIR RESERVA

void teste_inserir_agenda_dados_validos(Agenda *agenda, Reserva *reserva1,
                                        Reserva *reserva2, Reserva *reserva3,
                                        Reserva *reserva4) {
  inserir_agenda(agenda, reserva1);
  inserir_agenda(agenda, reserva2);
  inserir_agenda(agenda, reserva3);
  inserir_agenda(agenda, reserva4);
  if (buscar_reserva(agenda, 1) != NULL) {
    if (buscar_reserva(agenda, 2) != NULL) {
      if (buscar_reserva(agenda, 3) != NULL) {
        if (buscar_reserva(agenda, 4) != NULL) {
          printf("teste_inserir_agenda_dados_validos PASSOU\n");
        } else {
          printf("teste_inserir_agenda_dados_validos NÃO PASSOU\n");
        }
      } else {
        printf("teste_inserir_agenda_dados_validos NÃO PASSOU\n");
      }
    } else {
      printf("teste_inserir_agenda_dados_validos NÃO PASSOU\n");
    }
  } else {
    printf("teste_inserir_agenda_dados_validos NÃO PASSOU\n");
  }
}

void teste_inserir_agenda_dados_nulos(Agenda *agenda, Reserva *reserva) {
  inserir_agenda(agenda, reserva);
  if (inserir_agenda(NULL, reserva) == 0) {
    if (inserir_agenda(agenda, NULL) == 0) {
      printf("teste_inserir_agenda_dados_nulos PASSOU\n");
    } else {
      printf("teste_inserir_agenda_dados_nulos NÃO PASSOU\n");
    }
  } else {
    printf("teste_inserir_agenda_dados_nulos NÃO PASSOU\n");
  }
}

//----------------------------------------------------------REMOVER RESERVA

void teste_remove_agenda_dados_validos(Agenda *agenda, Reserva *reserva1,
                                       Reserva *reserva2, Reserva *reserva3,
                                       Reserva *reserva4) {
  inserir_agenda(agenda, reserva1);
  inserir_agenda(agenda, reserva2);
  inserir_agenda(agenda, reserva3);
  inserir_agenda(agenda, reserva4);
  if (remover_agenda(agenda, 2) != NULL) {
    if (remover_agenda(agenda, 4) != NULL) {
      if (remover_agenda(agenda, 3) != NULL) {
        if (remover_agenda(agenda, 1) != NULL) {
          printf("teste_remove_agenda_dados_validos PASSOU\n");
        } else {
          printf("teste_remove_agenda_dados_validos NÃO PASSOU2\n");
        }
      } else {
        printf("teste_remove_agenda_dados_validos NÃO PASSOU3\n");
      }
    } else {
      printf("teste_remove_agenda_dados_validos NÃO PASSOU4\n");
    }
  } else {
    printf("teste_remove_agenda_dados_validos NÃO PASSOU5\n");
  }
}

void teste_remove_agenda_dados_invalidos(Agenda *agenda) {
  if (remover_agenda(agenda, -1) == NULL) {
    printf("teste_remove_agenda_dados_invalidos PASSOU\n");
  } else {
    printf("teste_remove_agenda_dados_invalidos NÃO PASSOU\n");
  }
}

void teste_remove_agenda_dados_nulos() {
  if (remover_agenda(NULL, 1) == 0) {
    printf("teste_remove_agenda_dados_nulos PASSOU\n");
  } else {
    printf("teste_remove_agenda_dados_nulos NÃO PASSOU\n");
  }
}

//----------------------------------------------------------EDITAR RESERVA

//*editar_reserva(Reserva *reserva, int codigo, Data *data_viagem, Passageiro
//*passageiro, Voo *voo, Assento assento)

// if (codigo >= 0 && verifica_dias(data_viagem->dia, data_viagem->mes)
// &&passageiro != NULL && voo != NULL

void teste_editar_reserva_dados_validos(Agenda *agenda, Reserva *reserva,
                                        Passageiro *passageiro, Data *data,
                                        Voo *voo) {
  inserir_agenda(agenda, reserva);
  if (editar_reserva(reserva, 1, data, passageiro, voo, A1, agenda) == 1) {
    printf("teste_editar_reserva_dados_validos PASSOU\n");
  } else {
    printf("teste_editar_reserva_dados_validos NÃO PASSOU\n");
  }
}

// espera-se que a função retorne NULL - basta UM parâmetro INVÁLIDO
void teste_editar_reserva_dados_invalidos(Reserva *reserva, Data *data,
                                          Passageiro *passageiro, Voo *voo) {
  int reserva_editada =
      editar_reserva(reserva, 1, data, passageiro, voo, A1, NULL);
  // antes: Reserva *reserva_editada = editar_reserva(...)
  // editar_reserva retorna 0 quando alguem parametro é invalido e retorna 1
  // quando ocorre a edição

  if (reserva_editada == 0) {
    printf("teste_editar_reserva_dados_invalidos PASSOU.\n");
  } else {
    printf("teste_editar_reserva_dados_invalidos NÃO PASSOU.\n");
  }
}

// espera-se que a função retorne NULL - basta UM parâmetro NULL
void teste_editar_reserva_dados_nulos(Agenda *agenda, Reserva *reserva,
                                      Passageiro *passageiro, Voo *voo,
                                      Data *data) {
  inserir_agenda(agenda, reserva);

  int reserva_editada2 =
      editar_reserva(reserva, 1, NULL, passageiro, voo, A1, agenda);
  int reserva_editada3 =
      editar_reserva(reserva, 1, data, NULL, voo, A1, agenda);
  int reserva_editada4 =
      editar_reserva(reserva, 1, data, passageiro, NULL, A1, agenda);
  int reserva_editada5 =
      editar_reserva(reserva, 1, data, passageiro, voo, A1, NULL);

  if (reserva_editada2 == 0 && reserva_editada3 == 0 && reserva_editada4 == 0 &&
      reserva_editada5 == 0) {
    printf("teste_editar_reserva_dados_nulos PASSOU.\n");
  } else {
    printf("teste_editar_reserva_dados_nulos NÃO PASSOU.\n");
  }
}
//-------------------------------------BUSCA POR ID E COD DE VOO

void teste_busca_id_codigo_validos(Agenda *agenda, Reserva *reserva) {
  Reserva *aux = busca_id_codigo(agenda, 1, 2);
  if (aux == reserva) {
    printf("teste_busca_id_codigo_validos PASSOU\n");
  } else {
    printf("teste_busca_id_codigo_validos NÃO PASSOU\n");
  }
}

void teste_busca_id_codigo_invalidos(Agenda *agenda) {
  if (busca_id_codigo(agenda, -1, 2) == NULL &&
      busca_id_codigo(agenda, 1, -2) == NULL) {
    printf("teste_busca_id_codigo_invalidos PASSOU\n");
  } else {
    printf("teste_busca_id_codigo_invalidos NÃO PASSOU\n");
  }
}

void teste_busca_id_codigo_nulos() {
  if (busca_id_codigo(NULL, 1, 2) == NULL) {
    printf("teste_busca_id_codigo_nulos PASSOU\n");
  } else {
    printf("teste_busca_id_codigo_nulos NÃO PASSOU\n");
  }
}

// Tabela hash
// Tabela hash
// Tabela hash
// Tabela hash
// Tabela hash
// Tabela hash
// Tabela hash
// Tabela hash
// Tabela hash
// Tabela hash
// Tabela hash

void teste_inicializar_tabela_hash_dados_validos(Viagem **tabela_hash) {
  if (tabela_hash != NULL) {
    printf("teste_inicializar_tabela_hash_dados_validos PASSOU\n");
  } else {
    printf("teste_inicializar_tabela_hash_dados_validos NÂO PASSOU\n");
  }
}

void teste_inicializar_tabela_viagem_dados_validos(
    TabelaViagem *tabela_viagem) {
  if (tabela_viagem != NULL) {
    printf("teste_inicializar_tabela_Viagem_dados_validos PASSOU\n");
  } else {
    printf("teste_inicializar_tabela_Viagem_dados_validos NÂO PASSOU\n");
  }
}

void teste_criar_trecho_dados_validos(Trecho *trecho) {
  if (trecho != NULL) {
    printf("teste_criar_trecho_dados_validos PASSOU\n");
  } else {
    printf("teste_criar_trecho_dados_validos NÂO PASSOU\n");
  }
}
void teste_criar_trecho_dados_nulos(Trecho *trecho) {
  if (trecho == NULL) {
    printf("teste_criar_trecho_dados_nulos PASSOU\n");
  } else {
    printf("teste_criar_trecho_dados_nulos NÂO PASSOU\n");
  }
}

void teste_inserir_trecho_dados_validos(int aux) {
  if (aux == 1) {
    printf("teste_inserir_trechos_dados_validos PASSOU\n");
  } else {
    printf("teste_inserir_trechos_dados_validos NÃO PASSOU\n");
  }
}

void teste_inserir_trecho_dados_nulos() {
  Viagem *viagem_aux;
  Trecho *trecho_aux;
  // se pelo menos um parametro (viagem, trecho) for NULL, retorna 0
  if (inserir_trecho(NULL, trecho_aux) == 0 &&
      inserir_trecho(viagem_aux, NULL) == 0 &&
      inserir_trecho(NULL, NULL) == 0) {
    printf("teste_inserir_trechos_dados_nulos PASSOU\n");
  } else {
    printf("teste_inserir_trechos_dados_nulos NÃO PASSOU\n");
  }
}

void teste_verifica_trechos_dados_validos(int aux) {
  if (aux == 1) {
    printf("teste_verifica_trechos_dados_validos PASSOU\n");
  } else {
    printf("teste_verifica_trechos_dados_validos NÃO PASSOU\n");
  }
}

void teste_verifica_trechos_dados_invalidos(int aux) {
  if (aux == 0) {
    printf("teste_verifica_trechos_dados_invalidos PASSOU\n");
  } else {
    printf("teste_verifica_trechos_dados_invalidos NÃO PASSOU\n");
  }
}

void teste_busca_trecho_dados_validos(Trecho *trecho) {
  if (trecho != NULL) {
    printf("teste_busca_trechos_dados_validos PASSOU\n");
  } else {
    printf("teste_busca_trechos_dados_validos PASSOU\n");
  }
}

void teste_busca_trecho_dados_invalidos(Trecho *trecho) {
  if (trecho == NULL) {
    printf("teste_busca_trechos_dados_invalidos PASSOU\n");
  } else {
    printf("teste_busca_trechos_dados_invalidos PASSOU\n");
  }
}

void teste_remover_trecho_dados_validos(Trecho *trecho, Trecho *trecho2) {
  if (trecho == trecho2) {
    printf("teste_remover_trecho_dados_validos PASSOU\n");
  } else {
    printf("teste_remover_trecho_dados_validos NÃO PASSOU\n");
  }
}
void teste_remover_trecho_dados_invalidos(Trecho *trecho) {
  if (trecho == NULL) {
    printf("teste_remover_trecho_dados_invalidos PASSOU\n");
  } else {
    printf("teste_remover_trecho_dados_invalidos NÃO PASSOU\n");
  }
}

void teste_remover_trecho_dados_nulos() {
  Viagem *viagem_aux;
  int codigo = 1;
  if (remover_trecho(NULL, codigo) == NULL ||
      remover_trecho(viagem_aux, NULL) == NULL ||
      remover_trecho(NULL, NULL) == NULL) {
    printf("teste_remover_trecho_dados_nulos PASSOU\n");
  } else {
    printf("teste_remover_trecho_dados_nulos NÃO PASSOU\n");
  }
}
// void teste_
void teste_inserir_na_tabela_dados_validos(int aux) {
  if (aux == 1) {
    printf("teste_inserir_na_tabela_dados_validos PASSOU\n");
  } else {
    printf("teste_inserir_na_tabela_dados_validos PASSOU\n");
  }
}
void teste_inserir_na_tabela_dados_nulos(TabelaViagem *tabelaviagem
                                        ) {
  int aux2_inserir_nulo = inserir_na_tabela(tabelaviagem->tabela_hash, NULL);
  if (aux2_inserir_nulo == 0) {
    printf("teste_inserir_na_tabela_dados_nulos PASSOU\n");
  } else {
    printf("teste_inserir_na_tabela_dados_nulos NÃO PASSOU\n");
  }
}

void teste_remover_tabela_validos(TabelaViagem *tabela_viagem, Viagem *viagem) {
  Viagem *aux =
      remover_tabela(tabela_viagem->tabela_hash, calculo_chave(viagem));
  if (aux == viagem) {
    printf("teste_remover_tabela_validos PASSOU\n");
  } else {
    printf("teste_remover_tabela_validos NÃO PASSOU\n");
  }
};

// PROGRAMA PRINCIPAL
int main() {
  // TESTES PASSAGEIRO //20 funções
  printf("Testes funções do PASSAGEIRO:\n");
  printf("----------------------------\n");
  printf("\n \n");
  // criando passageiros, no_passageiros e lista
  char aux_nome[55] = "";
  char aux_endereco[55] = "";
  int i = 0;
  for (i = 0; i < 53; i++) {
    strcat(aux_nome, "N");
  }
  for (i = 0; i < 53; i++) {
    strcat(aux_endereco, "C");
  }
  Passageiro *passageiro1 = criar_passageiro(1, "João Lucas", "Russas");
  Passageiro *passageiro2 =
      criar_passageiro(-1, aux_nome, aux_endereco); // passageiro invalido
  Passageiro *passageiro3 = criar_passageiro(3, "Nicolas", "Russas");
  Passageiro *passageiro4 = criar_passageiro(2, "Fluvio", "Fortal");
  Passageiro *passageiro5 = criar_passageiro(5, "Julia", "Rio");
  Passageiro *passageiro6 = criar_passageiro(
      1, "Rocha", "Rio"); // passageiro com o mesmo id do passageiro1
  Passageiro *passageiro7 = criar_passageiro(21,"Meneses", "Calouros do Ar");

  No_passageiro *no1 = criar_no_passageiro(passageiro1);
  No_passageiro *no5 = criar_no_passageiro(passageiro5);
  No_passageiro *no4 = criar_no_passageiro(passageiro4);
  No_passageiro *no3 = criar_no_passageiro(passageiro3);
  No_passageiro *no6 = criar_no_passageiro(passageiro6);
  No_passageiro *no7 = criar_no_passageiro(passageiro7);
  
  Lista_Passageiro *lista = criar_lista_passageiro();

  teste_criar_passageiro_dados_validos(passageiro1);
  teste_criar_passageiro_dados_invalidos(passageiro2);
  teste_criar_passageiro_dados_nulos();
  printf("\n");
  teste_criar_no_passageiro_validos(no1);
  teste_criar_no_passageiro_nulos();
  teste_criar_lista_passageiro_validos(lista);
  printf("\n");

  // inserindo passageiros na lista
  int aux_passageiro1 = inserir_passageiro(lista, no1);
  int aux_passageiro2 = inserir_passageiro(lista, no6);
  inserir_passageiro(lista, no3);
  inserir_passageiro(lista, no4);
  inserir_passageiro(lista, no5);
  inserir_passageiro(lista, no7);
  // testando se o insere funciona

  teste_inserir_lista_passageiro_com_dados_validos(aux_passageiro1);
  teste_inserir_lista_passageiro_com_dados_invalidos(aux_passageiro2);
  teste_inserir_lista_passageiro_com_dados_nulos();

  printf("\n");
  Passageiro *passageiro_busca = buscar_passageiro(lista, 3);
  teste_busca_passageiro_validos(passageiro_busca, passageiro3);
  passageiro_busca = buscar_passageiro(lista, -1);
  teste_busca_passageiro_invalidos(passageiro_busca);
  teste_busca_passageiro_nulos();

  printf("\n");
  Passageiro *removido = remover_passageiro(lista, 1);
  teste_remove_passageiro_validos(removido, passageiro1);
  inserir_passageiro(lista, no1);
  removido = remover_passageiro(lista, -1);
  teste_remove_passageiro_invalidos(removido);
  teste_remove_passageiro_nulos();
  printf("\n");
  int aux_editar_passageiro =
      editar_passageiro(passageiro3, 3, "Nicolas", "Amapa", lista);
  int aux_editar_passageiro2 =
      editar_passageiro(passageiro4, 4, NULL, "Amapa", lista);
  int aux_editar_passageiro3 =
      editar_passageiro(passageiro4, 4, " Nicolas", NULL, lista);
  int aux_editar_passageiro4 =
      editar_passageiro(passageiro4, 3, " Nicolas", "Amapa", lista);
  teste_editar_passageiro_validos(aux_editar_passageiro);
  teste_editar_passageiro_invalidos(
      aux_editar_passageiro2, aux_editar_passageiro3, aux_editar_passageiro4);
  teste_editar_passageiro_nulos();

  teste_acessar_passageiro_validos(passageiro1);
  teste_acessar_passageiro_nulos();
  printf("\n \n \n");

  // TESTES VOO //20 funções
  printf("Testes funções do VOO:\n");
  printf("----------------------------\n");
  printf("\n \n");
  // criando voo, no_voo e lista_voo
  char origem_aux[55] = "";
  char destino_aux[55] = "";
  for (int i = 0; i < 53; i++) {
    strcat(origem_aux, "N");
  }
  for (int i = 0; i < 53; i++) {
    strcat(destino_aux, "C");
  }
  Voo *voo2 = criar_voo(-1, origem_aux, destino_aux); // voo inválido
  Voo *voo1 = criar_voo(1, "Fortaleza", "São Paulo");
  Voo *voo3 = criar_voo(2, "Nova York", "Washington DC");
  Voo *voo4 = criar_voo(3, "Paris", "Bordeaux");
  Voo *voo5 =
      criar_voo(1, "Rio", "Madagascar"); // voo com mesmo codigo que o voo1
  Voo *voo6 = criar_voo(4, "São Paulo", "Russas");
  Voo *voo7 = criar_voo(5, "Fortaleza", "São Paulo");
  Voo *voo8 = criar_voo(6, "Russas", "Natal");

  Voo *voo9 = criar_voo(9, "Fortaleza", "Albânia");
  Voo *voo10 = criar_voo(10, "Albânia", "Pequim");
  
  No_voo *no_voo3 = criar_no_voo(voo3);
  No_voo *no_voo1 = criar_no_voo(voo1);
  No_voo *no_voo4 = criar_no_voo(voo4);
  No_voo *no_voo5 = criar_no_voo(voo5);
  No_voo *no_voo6 = criar_no_voo(voo6);
  No_voo *no_voo7 = criar_no_voo(voo7);
  No_voo *no_voo8 = criar_no_voo(voo8);
  No_voo *no_voo9 = criar_no_voo(voo9);
  No_voo *no_voo10 = criar_no_voo(voo10);

  Lista_Voo *lista_voo = criar_lista_voo();

  teste_criar_voo_dados_validos(voo1);
  teste_criar_voo_dados_invalidos(voo2);
  teste_criar_voo_dados_nulos();

  teste_criar_no_voo_validos(no_voo1);
  teste_criar_no_voo_nulos();
  teste_criar_lista_voo_validos(lista_voo);
  printf("\n");
  // inserindo voos na lista voo
  int aux_voo1 = inserir_voo(lista_voo, no_voo1);
  int aux_voo2 = inserir_voo(lista_voo, no_voo5);
  inserir_voo(lista_voo, no_voo3);
  inserir_voo(lista_voo, no_voo4);
  inserir_voo(lista_voo, no_voo5);
  inserir_voo(lista_voo, no_voo9);
  inserir_voo(lista_voo, no_voo10);
  teste_inserir_lista_voo_com_dados_validos(aux_voo1);
  teste_inserir_lista_voo_com_dados_invalidos(aux_voo2);
  teste_inserir_lista_voo_com_dados_nulos();
  printf("\n");

  Voo *voo_busca = buscar_voo(3, lista_voo);
  teste_busca_voo_validos(voo_busca, voo3);
  voo_busca = buscar_voo(-1, lista_voo);
  teste_busca_voo_invalidos(voo_busca);
  teste_busca_voo_nulos();
  printf("\n");
  // removendo voos
  No_voo *removido_aux_voo = remover_voo(1, lista_voo);
  teste_remove_voo_dados_validos(removido_aux_voo, no_voo1);
  inserir_voo(lista_voo, no_voo1);
  removido_aux_voo = remover_voo(-1, lista_voo);
  teste_remove_voo_invalidos(removido_aux_voo);
  teste_remove_voo_dados_nulos();
  printf("\n");
  // editando voos
  int aux_editar_voo1 = editar_voo(voo1, 1, "São Paulo", "amazonas", lista_voo);
  int aux_editar_voo2 = editar_voo(voo1, 3, "São Paulo", "amazonas", lista_voo);
  int aux_editar_voo3 = editar_voo(voo1, 1, NULL, "amazonas", lista_voo);
  int aux_editar_voo4 = editar_voo(voo1, 1, "São Paulo", NULL, lista_voo);
  teste_editar_voo_validos(aux_editar_voo1);
  teste_editar_voos_invalidos(aux_editar_voo2, aux_editar_voo3,
                              aux_editar_voo4);
  teste_editar_voo_nulos();
  printf("\n");
  teste_acessar_voo_validos(voo3);
  teste_acessar_voo_nulos();
  printf("\n \n");

  // TESTES RESERVA
  Data *data1 = add_data(10, 3, 2002); // datas válidas
  Data *data2 = add_data(11, 5, 2022);
  Data *data3 = add_data(18, 6, 2012);
  Data *data4 = add_data(10, 2, 2001);
  Data *data5 = add_data(-1, 9, 2022);  // inválida
  Data *data6 = add_data(30, 02, 2022); // inválida
  Data *data7 = add_data(30, 03, 2022);
  Data *data8 = add_data(30, 04, 2022);
  Data *data9 = add_data(30, 05, 2022);
  Data *data10 = add_data(21, 10, 2022);
  Data *data11 = add_data(15, 11, 2022);
  
  Reserva *reserva1 =
      criar_reserva(1, data1, passageiro1, voo1, A1); // reservas válidas
  Reserva *reserva2 = criar_reserva(2, data2, passageiro3, voo3, A1);
  Reserva *reserva3 = criar_reserva(3, data3, passageiro4, voo4, A1);
  Reserva *reserva4 = criar_reserva(4, data4, passageiro5, voo6, A1);

  Reserva *reserva5 =
      criar_reserva(-1, data1, passageiro1, voo1, A0); // codigo inv.
  Reserva *reserva6 =
      criar_reserva(1, data5, passageiro1, voo1, A0); // data inv.
  Reserva *reserva7 =
      criar_reserva(1, data1, passageiro2, voo1, A0); // passag. inv.
  Reserva *reserva8 =
      criar_reserva(1, data1, passageiro1, voo2, A0); // voo inv.
  Reserva *reserva9 =
      criar_reserva(1, data1, passageiro1, voo1, -1); // assento inv.

  Reserva *reserva10 =
      criar_reserva(1, NULL, passageiro1, voo1, A0);            // data NULL
  Reserva *reserva11 = criar_reserva(1, data1, NULL, voo1, A0); // passag. NULL
  Reserva *reserva12 =
      criar_reserva(1, data1, passageiro1, NULL, A0); // voo NULL
  
  // voos com origens e destinos que coincidem e datas coerentes
  Reserva *reserva13 = criar_reserva(13, data4, passageiro1, voo7, A0);
  Reserva *reserva14 = criar_reserva(14, data1, passageiro1, voo6, A0);
  Reserva *reserva15 = criar_reserva(15, data3, passageiro1, voo8, A0);

  Reserva *reserva16 = criar_reserva(16, data7, passageiro2, voo7, A0);
  Reserva *reserva17 = criar_reserva(17, data8, passageiro2, voo6, A0);
  Reserva *reserva18 = criar_reserva(18, data9, passageiro2, voo8, A0);

  Reserva *reserva21 = criar_reserva(21, data10, passageiro7, voo9, C2);
  Reserva *reserva22 = criar_reserva(22, data11, passageiro7, voo10, C2);
  printf("Testes funções da RESERVA:\n");
  printf("----------------------------\n");
  printf("\n \n");

  teste_criar_data_validos(data1);
  teste_criar_data_invalidos(data5, data6);
  printf("\n");
  teste_criar_reserva_dados_validos(reserva1);
  teste_criar_reserva_dados_invalidos(reserva5, reserva6, reserva7, reserva8,
                                      reserva9);
  teste_criar_reserva_dados_nulos(reserva10, reserva11, reserva12);
  printf("\n");

  Agenda *agenda1 = criar_agenda();
  Agenda *agenda2 = NULL;

  teste_criar_agenda(agenda1);
  printf("\n");

  teste_buscar_reserva_dados_validos(agenda1, reserva1, reserva2, reserva3,
                                     reserva4);
  teste_buscar_reserva_dados_invalidos(agenda1, reserva1);
  teste_buscar_reserva_dados_nulos(agenda2);
  printf("\n");

  teste_inserir_agenda_dados_validos(agenda1, reserva1, reserva2, reserva3,
                                     reserva4);
  teste_inserir_agenda_dados_nulos(agenda1, reserva1);
  printf("\n");
  teste_remove_agenda_dados_validos(agenda1, reserva1, reserva2, reserva3,
                                    reserva4);
  teste_remove_agenda_dados_invalidos(agenda1);
  teste_remove_agenda_dados_nulos();
  printf("\n");
  teste_editar_reserva_dados_validos(agenda1, reserva1, passageiro1, data2,
                                     voo3);
  teste_editar_reserva_dados_invalidos(reserva1, data1, passageiro1, voo1);
  teste_editar_reserva_dados_nulos(agenda1, reserva1, passageiro1, voo1, data1);
  printf("\n \n");

  teste_busca_id_codigo_validos(agenda1, reserva1);
  teste_busca_id_codigo_invalidos(agenda1);
  teste_busca_id_codigo_nulos();
  printf("\n \n");

  printf("Testes funções da TABELA HASH:\n");
  printf("----------------------------\n");
  printf("\n \n");

  Viagem **tabela_hash = inicializar_tabela();
  teste_inicializar_tabela_hash_dados_validos(tabela_hash);

  TabelaViagem *tabela_Viagem = inicializar_tabela_Viagem(tabela_hash);
  teste_inicializar_tabela_viagem_dados_validos(tabela_Viagem);
  printf("\n");
  Viagem *viagem1 = criar_viagem();
  Viagem *viagem2 = criar_viagem();
  Viagem *viagem3 = criar_viagem();
  Viagem *viagem21 = criar_viagem();

  Trecho *trecho1 = criar_trecho(reserva13);
  Trecho *trecho2 = criar_trecho(reserva14);
  Trecho *trecho3 = criar_trecho(reserva15);
  Trecho *trecho4 = criar_trecho(NULL);
  Trecho *trecho5 = criar_trecho(reserva16);
  Trecho *trecho6 = criar_trecho(reserva17);
  Trecho *trecho7 = criar_trecho(reserva18);
  Trecho *trecho21 = criar_trecho(reserva21);
  Trecho *trecho22 = criar_trecho(reserva22);
  teste_criar_trecho_dados_validos(trecho1);
  teste_criar_trecho_dados_nulos(trecho4);
  printf("\n");
  int aux_inserir_trecho = inserir_trecho(viagem1, trecho1);
  teste_inserir_trecho_dados_validos(aux_inserir_trecho);
  teste_inserir_trecho_dados_nulos();

  printf("\n");
  
  int aux_verifica_trecho1 = verifica_trechos(viagem1, trecho2);
  
  inserir_trecho(viagem21, trecho21);
  inserir_trecho(viagem21, trecho22);
  teste_verifica_trechos_dados_validos(aux_verifica_trecho1);
  int aux_verifica_trecho2 = verifica_trechos(viagem1, trecho1);
  teste_verifica_trechos_dados_invalidos(aux_verifica_trecho2);
  printf("\n");
  inserir_trecho(viagem1, trecho2);

  Trecho *aux_busca_trecho = buscar_trecho(viagem1, 13);
  teste_busca_trecho_dados_validos(aux_busca_trecho);

  Trecho *aux2_busca_trecho = buscar_trecho(viagem1, 15);
  teste_busca_trecho_dados_invalidos(aux2_busca_trecho);
  printf("\n");

  inserir_trecho(viagem1, trecho3);
  inserir_trecho(viagem2, trecho5);
  inserir_trecho(viagem2, trecho6);
  inserir_trecho(viagem2, trecho7);

  Trecho *aux_remover_trecho = remover_trecho(viagem1, 15);
  teste_remover_trecho_dados_validos(aux_remover_trecho, trecho3);
  Trecho *aux_remover_trecho2 = remover_trecho(viagem1, 1);
  teste_remover_trecho_dados_invalidos(aux_remover_trecho2);
  teste_remover_trecho_dados_nulos();
  inserir_trecho(viagem1, trecho3);

  printf("\n");
  int aux_inserir_na_tabela1 = inserir_na_tabela(tabela_hash, viagem1);
  teste_inserir_na_tabela_dados_validos(aux_inserir_na_tabela1);
  TabelaViagem *tabela_viagem = (TabelaViagem *)malloc(sizeof(TabelaViagem));
  tabela_viagem->tamanho = M;
  tabela_viagem->tabela_hash = tabela_hash;
  teste_inserir_na_tabela_dados_nulos(tabela_viagem);
  printf("\n");
  printf("\n");
  teste_remover_tabela_validos(tabela_viagem,viagem1);
  
  inserir_na_tabela(tabela_hash, viagem21);

  printf("\n");
  printf("\n");
  printf("Mostrar itinerario\n");
  printf("----------------------------------------------------------\n");
  printf("\n");
  inserir_na_tabela(tabela_viagem->tabela_hash, viagem1);
  mostrar_itinerario(tabela_viagem, calculo_chave(viagem21));

  int tabela_hash_aux = tabela_viagem->tamanho;

  // int aux_chave=calculo_chave(viagem1);
  // void mostrar_itinerario(tabela_viagem , aux_chave);
}