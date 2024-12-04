#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void* recepcao_thread(void* args) {
    Fila* fila = (Fila*)args;
    int n = 10;
    int x = 1000;

    srand(time(NULL));
    for (int i = 0; i < n || n == 0; i++) {
        Cliente* novo_cliente = (Cliente*)malloc(sizeof(Cliente));
        novo_cliente->pid = i + 1;
        novo_cliente->hora_chegada = (int)time(NULL);
        novo_cliente->prioridade = rand() % 2;
        novo_cliente->paciencia = (novo_cliente->prioridade == 1) ? x / 2 : x;
        novo_cliente->prox = NULL;

        pthread_mutex_lock(&fila->lock);
        if (!fila->inicio) {
            fila->inicio = novo_cliente;
        } else {
            Cliente* atual = fila->inicio;
            while (atual->prox) {
                atual = atual->prox;
            }
            atual->prox = novo_cliente;
        }
        pthread_mutex_unlock(&fila->lock);

        printf("Recepção: Cliente %d criado com prioridade %d e paciência %d ms\n",
               novo_cliente->pid, novo_cliente->prioridade, novo_cliente->paciencia);

        usleep(100000);
    }
    return NULL;
}
