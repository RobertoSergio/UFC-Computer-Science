#include <stdio.h>
#include <stdlib.h>
#include <fila.h>
#include <pthread.h>

void inicializar_fila(Fila* fila) {
    fila->inicio = NULL;
    pthread_mutex_init(&fila->lock, NULL);
}

int encontrar_max_prioridade(Cliente* cliente) {
    int max = cliente->prioridade;
    while (cliente) {
        if (cliente->prioridade > max)
            max = cliente->prioridade;
        cliente = cliente->prox;
    }
    return max;
}

void radix_sort(Fila* fila) {
    int exp, max;
    Cliente *bucket[10], *atual;
    Cliente *temp[10] = { NULL };

    pthread_mutex_lock(&fila->lock);
    
    max = encontrar_max_prioridade(fila->inicio);
    
    for (exp = 1; max / exp > 0; exp *= 10) {
        for (int i = 0; i < 10; i++)
            bucket[i] = NULL;

        atual = fila->inicio;
        while (atual) {
            int index = (atual->prioridade / exp) % 10;
            if (!bucket[index]) {
                bucket[index] = atual;
                temp[index] = atual;
            } else {
                temp[index]->prox = atual;
                temp[index] = atual;
            }
            atual = atual->prox;
        }

        fila->inicio = NULL;
        Cliente* ultimo = NULL;
        for (int i = 9; i >= 0; i--) {
            if (bucket[i]) {
                if (!fila->inicio) {
                    fila->inicio = bucket[i];
                } else {
                    ultimo->prox = bucket[i];
                }
                ultimo = temp[i];
            }
        }
        if (ultimo)
            ultimo->prox = NULL;
    }

    pthread_mutex_unlock(&fila->lock);
}


void adicionar_cliente(Fila* fila, Cliente* novo_cliente) {
    pthread_mutex_lock(&fila->lock);
    novo_cliente->prox = fila->inicio;
    fila->inicio = novo_cliente;
    pthread_mutex_unlock(&fila->lock);

    radix_sort(fila);
}

Cliente* remover_cliente(Fila* fila) {
    pthread_mutex_lock(&fila->lock);
    Cliente* cliente_removido = fila->inicio;
    if (fila->inicio) {
        fila->inicio = fila->inicio->prox;
    }
    pthread_mutex_unlock(&fila->lock);
    return cliente_removido;
}
