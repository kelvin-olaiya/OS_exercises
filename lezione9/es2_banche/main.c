
#define _BSD_SOURCE /* usleep */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <inttypes.h>
#include "DBGpthread.h"
#include <unistd.h>

#define MICRO_IN_SECOND 100000000

#define NUM_BANCHE 3
#define NUM_THREAD_DEPOSITO 5
#define NUM_THREAD_PRELIEVO 4

/*Global variables*/
int T[NUM_BANCHE];
int N[NUM_BANCHE];
pthread_mutex_t mutex[NUM_BANCHE];

/*Thread deposito*/
void* thread_deposito(void* arg) {
    intptr_t indiceBanca = (intptr_t)arg;
    while(1) {
        sleep(1);
        DBGpthread_mutex_lock(&mutex[indiceBanca], "deposito");
        T[indiceBanca] += 10;
        N[indiceBanca]++;
        /*printf("deposito in banca n.%"PRIdPTR"\n", indiceBanca);*/
        DBGpthread_mutex_unlock(&mutex[indiceBanca], "deposito");
        usleep(0.1 * MICRO_IN_SECOND);
    }
    
    return NULL;
}

/*Thread prelievo*/
void* thread_prelievo(void* arg) {
    intptr_t indiceBanca = (intptr_t)arg;
    while(1) {
        sleep(1);
        DBGpthread_mutex_lock(&mutex[indiceBanca], "prelievo");
        T[indiceBanca] -= 9;
        N[indiceBanca]++;
        /*printf("prelievo in banca n.%"PRIdPTR"\n", indiceBanca);*/
        DBGpthread_mutex_unlock(&mutex[indiceBanca], "prelievo");
        usleep(0.1 * MICRO_IN_SECOND);
    }
    return NULL;
}

void* BancaDiItalia(void* arg) {
    while(1) {
        int i;
        int sommaTotali = 0;
        int sommaOperazioni = 0;

        for (i = 0; i < NUM_BANCHE; i++) {
            DBGpthread_mutex_lock(&mutex[i], "BancaDiItalia");
            sommaTotali += T[i];
            sommaOperazioni += N[i];
            DBGpthread_mutex_unlock(&mutex[i], "BancaDiItalia");
        }
        
        printf("[BancaDiItalia] Saldo: %d\n", sommaTotali);
        printf("[BancaDiItalia] Tot. Operazioni: %d\n", sommaOperazioni);
        sleep(30);
    }
}

int main() {
    pthread_t tid;
    intptr_t i, j;
    int err;

    
    /*Inizializzione variabili globali */
    for (i = 0; i < NUM_BANCHE; i++) {
        T[i] = 0;
        N[i] = 0;
    }
    /* Creazione dei thread ed inizializzazione mutex */
    for (j = 0; j < NUM_BANCHE; j++) {
        intptr_t indiceBanca = j;
        DBGpthread_mutex_init(&mutex[j], NULL, "Inizializzazione mutex");
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