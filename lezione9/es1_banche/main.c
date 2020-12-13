
#define _BSD_SOURCE /* usleep */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <inttypes.h>
#include "DBGpthread.h"
#include <unistd.h>

#define MICRO_IN_SECOND 1000000

#define NUM_BANCHE 3
#define NUM_THREAD_DEPOSITO 5
#define NUM_THREAD_PRELIEVO 4

/*Global variables*/
int T[NUM_BANCHE];
int N[NUM_BANCHE];
pthread_mutex_t mutex;

/*Thread deposito*/
void* thread_deposito(void* arg) {
    intptr_t indiceBanca = (intptr_t)arg;
    while(1) {
        sleep(1);
        DBGpthread_mutex_lock(&mutex, "deposito");
        T[indiceBanca] += 10;
        N[indiceBanca]++;
        /*printf("deposito in banca n.%"PRIdPTR"\n", indiceBanca);*/
        DBGpthread_mutex_unlock(&mutex, "deposito");
        usleep(0.1 * MICRO_IN_SECOND);
    }
    
    return NULL;
}

/*Thread prelievo*/
void* thread_prelievo(void* arg) {
    intptr_t indiceBanca = (intptr_t)arg;
    while(1) {
        sleep(1);
        DBGpthread_mutex_lock(&mutex, "prelievo");
        T[indiceBanca] -= 9;
        N[indiceBanca]++;
        /*printf("prelievo in banca n.%"PRIdPTR"\n", indiceBanca);*/
        DBGpthread_mutex_unlock(&mutex, "prelievo");
        usleep(0.1 * MICRO_IN_SECOND);
    }
    return NULL;
}

void* BancaDiItalia(void* arg) {
    while(1) {
        int i;
        int sommaTotali = 0;
        int sommaOperazioni = 0;
        DBGpthread_mutex_lock(&mutex, "BancaDiItalia");
        for (i = 0; i < NUM_BANCHE; i++) {
            sommaTotali += T[i];
            sommaOperazioni += N[i];
        }
        printf("[BancaDiItalia] Saldo: %d\n", sommaTotali);
        printf("[BancaDiItalia] Tot. Operazioni: %d\n", sommaOperazioni);
        DBGpthread_mutex_unlock(&mutex, "BancaDiItalia");
        sleep(30);
    }
}

int main() {
    pthread_t tid;
    intptr_t i, j;
    int err;

    DBGpthread_mutex_init(&mutex, NULL, "Inizializzazione mutex");
    /* Creazione dei thread */
    for (j = 0; j < NUM_BANCHE; j++) {
        intptr_t indiceBanca = j;
        for(i = 0; i < NUM_THREAD_DEPOSITO; i++) {
            err = pthread_create(&tid, NULL, thread_deposito, (void *)indiceBanca);
            if (err) {
                printf("thread err: %d", err);
            }
        }

        for(i = 0; i < NUM_THREAD_PRELIEVO; i++) {
            err = pthread_create(&tid, NULL, thread_prelievo, (void *)indiceBanca);
            if (err) {
                printf("thread err: %d", err);
            }
        }
    }
    pthread_create(&tid, NULL, BancaDiItalia, NULL);
    pthread_exit(NULL);
    return 0;
}