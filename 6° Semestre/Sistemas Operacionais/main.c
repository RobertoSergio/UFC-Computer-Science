#include "fila.h"
#include <pthread.h>

extern void* recepcao_thread(void* args);
extern void* atendimento_thread(void* args);

int main() {
    Fila fila;
    inicializar_fila(&fila);

    pthread_t recepcao, atendimento;

    pthread_create(&recepcao, NULL, recepcao_thread, &fila);
    pthread_create(&atendimento, NULL, atendimento_thread, &fila);

    pthread_join(recepcao, NULL);
    pthread_join(atendimento, NULL);

    return 0;
}
