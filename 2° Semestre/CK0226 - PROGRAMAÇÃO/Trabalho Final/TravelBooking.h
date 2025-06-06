enum cod_assento {
  A0,
  B0,
  C0,
  A1,
  B1,
  C1,
  A2,
  B2,
  C2,
  A3,
  B3,
  C3,
  A4,
  B4,
  C4,
  A5,
  B5,
  C5,
  A6,
  B6,
  C6,
  A7,
  B7,
  C7,
  A8,
  B8,
  C8,
  A9,
  B9,
  C9
};

typedef enum cod_assento Assento;
typedef struct data Data;
typedef struct voo Voo;
typedef struct no_voo No_voo;
typedef struct lista_voo Lista_Voo;
typedef struct passageiro Passageiro;
typedef struct no_passageiro No_passageiro;
typedef struct lista_passageiro Lista_Passageiro;
typedef struct reserva Reserva;
typedef struct agenda Agenda;
typedef struct trecho Trecho;
typedef struct viagem Viagem;
typedef struct tabela_viagem TabelaViagem;
typedef struct lista_aux_viagem ListaAuxViagem;

// GERENCIAMENTO DE VOOS

// Rebece os campos <codigo,origem,destino> e retorna uma voo com
// com esses valores ou NULL caso codigo<0, codigo nao seja numerico,
// origem=NULL e destino=NULL
int verif_parametros2(int codigo, char *origem, char *destino);

int comp_voo(No_voo *voo1, Voo *voo2);

Voo *criar_voo(int codigo, char *origem, char *destino);

No_voo *criar_no_voo(Voo *voo);

// Inicia e retorna uma lista_voo
Lista_Voo *criar_lista_voo();

// Verifica se existe um voo com o codigo inserido, retorna NULL se o
// codigo não existir, a lista for vazia ou se a lista for NULL
Voo *buscar_voo(int codigo, Lista_Voo *lista_voo);

No_voo *remover_voo(int codigo, Lista_Voo *lista_voo); // void ou retorno

int editar_voo(Voo *voo, int codigo, char *origem, char *destino,
               Lista_Voo *lista_voo);

void acessar_voo(Voo *voo, int *codigo, char *origem, char *destino);

// GERENCIAMENTO DE PASSAGEIROS

int lis_pas_libera(Lista_Passageiro **lista_passageiro);

void pas_libera(Passageiro **passageiro);

int verif_parametros(int id, char *nome, char *endereco);
// Recebe os campos <id,nome,endereco> e retorna uma passageiro com
// com esses valores ou NULL caso id<0, nome=NULL e endereco=NULL
Passageiro *criar_passageiro(int id, char *nome, char *endereco);

// Cria e retorna um No com um passageiro dentro
No_passageiro *criar_no_passageiro(Passageiro *passageiro);

// Inicia e retorna uma lista_passageiro
Lista_Passageiro *criar_lista_passageiro();

// Verifica se existe um passageiro com o id inserido, retorna NULL se o
// id não existir, a lista for vazia ou se a lista for NULL
Passageiro *buscar_passageiro(Lista_Passageiro *lista_passageiro, int id);

// insere um novo no_passageiro a lista, retorna 1 se for possivel
// adicionar, retorna 0 caso a lista seja NULL ou já exista o id do
// passageiro
int inserir_passageiro(Lista_Passageiro *lista_passageiro,
                       No_passageiro *no_passageiro);

// retorna 1 se dois passageiros forem iguais e 0 caso forem diferentes
int comp_passageiros(Passageiro *passageiro1, Passageiro *passageiro2);

// remove e retorna no_passageiro com id inserido, retorna NULL caso id não seja
// encontrado, a lista esteja vazia ou seja NULL
Passageiro *remover_passageiro(Lista_Passageiro *lista_passageiro, int id);

// modifica dados de um passageiro dentro da lista inserida
// retorna 1 caso tenha sido possivel realizar a modificação
// retorna 0 caso a lista seja NULL, a lista seja vazia,
// o passageiro não seja encontrado ou as novas informações não
// sejam coerentes com o formato exigido ou o novo id já exista na lista
int editar_passageiro(Passageiro *passageiro, int id, char *nome,
                      char *endereco, Lista_Passageiro *lista_passageiro);

// recupera <id,nome,endereco> de um passageiro, caso passageiro seja
// NULL recupera <-1,'NULL','NULL'>
void acessar_passageiro(Passageiro *passageiro, int *id, char *nome,
                        char *endereco);

// GERENCIAMENTO RESERVA

// Recebe os campos <dia,mes,ano> e retorna uma data com
// com esses valores ou NULL caso dia, mes, ano nao sejam validos
Data *add_data(int dia, int mes, int ano);

Reserva *criar_reserva(int codigo, Data *data_viagem, Passageiro *passageiro,
                       Voo *voo, Assento assento);

// Aloca memoria para uma agenda
Agenda *criar_agenda();

int inserir_agenda(Agenda *agenda, Reserva *reserva);

// busca o pai da reserva com o codigo inserido
Agenda *busca_pai(Agenda *agenda, Agenda *aux_agenda);

// Retorna NULL caso a agenda seja NULL, remove o nó com o código fornecido da
// agenda e retorna a agenda atualizada
Agenda *remover_agenda(Agenda *agenda, int codigo);

Agenda *buscar_agenda(Agenda *agenda, int codigo);

Reserva *buscar_reserva(Agenda *agenda, int codigo);

Agenda *min(Agenda *agenda);

Agenda *max(Agenda *agenda);

Agenda *sucessor(Agenda *agenda);

Agenda *antecessor(Agenda *agenda);

// modifica dados de uma agenda
// retorna 1 caso tenha sido possivel realizar a modificação
// retorna 0 caso a agenda seja NULL,
// o passageiro não seja encontrado ou as novas informações não
// sejam coerentes com o formato exigido ou o novo id já exista na lista
int editar_agenda(Agenda *agenda, Reserva *reserva);

int editar_reserva(Reserva *reserva, int codigo, Data *data_viagem,
                   Passageiro *passageiro, Voo *voo, Assento assento,
                   Agenda *agenda);

Reserva *busca_id(Agenda *agenda, int id);

void busca_codigo(Agenda *agenda, Agenda *agenda_codigo, int codigo);

Reserva *busca_id_codigo(Agenda *agenda, int id, int codigo);

void busca_data(Agenda *agenda, Agenda *agenda_data, Data *data);

Reserva *busca_id_data(Agenda *agenda, int id, Data *data);
//--------------------------------------------------TABELA
Trecho* criar_trecho(Reserva* reserva);

Viagem *criar_viagem();

Trecho *ult_trecho(Viagem *viagem);

int verifica_trechos(Viagem *viagem, Trecho *trecho);

int inserir_trecho(Viagem *viagem, Trecho *trecho);

Trecho *buscar_trecho(Viagem *viagem, int codigo);

Trecho *buscar_ant(Viagem *viagem, int codigo);

Trecho *remover_trecho(Viagem *viagem, int codigo);

Viagem **inicializar_tabela();

TabelaViagem *inicializar_tabela_Viagem();

int inserir_na_tabela(Viagem **tabela_hash, Viagem *viagem);

Data *prim_data(Viagem *viagem);

Data *ult_data(Viagem *viagem);

int verifica_cronologia(ListaAuxViagem *lista, Viagem *viagem);

ListaAuxViagem *busca_tabela_id(Viagem **tabela_hash, int id);

Viagem *buscar_chave(Viagem **tabela_hash, int chave);

Viagem *remover_tabela(Viagem **tabela_hash, int hash_id);

int inserir_na_tabela(Viagem **tabela_hash, Viagem *viagem);

int calculo_chave(Viagem *viagem);

int calculo_chave_aux(Trecho *aux);

void mostrar_assento(Assento assento);

void mostrar_itinerario(TabelaViagem *tabela_viagem, int chave);