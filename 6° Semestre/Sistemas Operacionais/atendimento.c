#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void* atendimento_thread(void* args) {
    Fila* fila = (Fila*)args;
    FILE* lng = fopen("LNG.txt", "w");
    if (!lng) {
        perror("Erro ao abrir arquivo LNG");
        return NULL;
    }

    while (1) {
        pthread_mutex_lock(&fila->lock);
        Cliente* cliente = fila->inicio;

        if (cliente) {
            fila->inicio = cliente->prox;
        }
        pthread_mutex_unlock(&fila->lock);

        if (cliente) {
            printf("Atendente: Atendendo cliente %d...\n", cliente->pid);
            usleep(cliente->paciencia * 1000);
            fprintf(lng, "PID: %d\n", cliente->pid);
            fflush(lng);

            int tempo_espera = ((int)time(NULL) - cliente->hora_chegada) * 1000;
            int satisfeito = (tempo_espera <= cliente->paciencia);
            printf("Cliente %d %s\n", cliente->pid, satisfeito ? "Satisfeito" : "Insatisfeito");

            free(cliente);
        } else {
            printf("Atendente: Nenhum cliente na fila. Aguardando...\n");
            sleep(1);
        }
    }
    fclose(lng);
    return NULL;
}
