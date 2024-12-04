#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

typedef struct Cliente {
    int pid;
    int hora_chegada;
    int prioridade;
    int paciencia;
    struct Cliente* prox;
} Cliente;

typedef struct Fila {
    Cliente* inicio;
    pthread_mutex_t lock;
} Fila;

void inicializar_fila(Fila* fila) {
    fila->inicio = NULL;
    pthread_mutex_init(&fila->lock, NULL);
}
