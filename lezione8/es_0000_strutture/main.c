#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "strutture.h"

#define NUM_THREADS 7
/*
 *  Non finito, mancano la gestione dei return values
 *  Liberazione della memoria...
 */
void* threadFunc(void * arg) {
    sleep(1);
    if (arg != NULL) {
        int i, err;
        pthread_t* tids;
        Struttura struttura = *((Struttura*)arg);
        int M = struttura.N;

        tids = M > 1 ? (pthread_t *)malloc((M - 1) * sizeof(pthread_t)) : NULL;
        if (tids ==  NULL) {
            pthread_exit(NULL);
        }
        for (i = 0; i < M - 1; i++) {
            Struttura* s = (Struttura*)malloc(sizeof(Struttura));
            if (s == NULL) {
                printf("Si è verificato un errore nell'allocazione di memoria\n");
                exit(1);
            }
            s->N = M-1;
            s->Indice = i;
            err = pthread_create(&tids[i], NULL, threadFunc, (void*)s);
            if (err != 0) {
                char str[200];
                printf("Si è verificato un errore nella creazione di un thread\n");
                strerror_r(err, str, 200);
                printf("%s\n", str);
                exit(1);
            }
            printf("Creato un thread N: %d, Indice: %d\n", s->N, s->Indice);
        }

        for (i = 0; i < M - 1; i++) {
            err = pthread_join(tids[i], NULL);
            if (err != 0) {
                printf("Si è verificato un errore nella join di un thread\n");
                exit(1);
            }
            printf("Join di un thread\n");
        }
    }
    return NULL;
}

int main() {
    pthread_t tids[NUM_THREADS];
    Struttura* struttura;
    int i, err;

    for (i = 0; i < NUM_THREADS; i++) {
        struttura = (Struttura*)malloc(sizeof(Struttura));
        if (struttura == NULL) {
            printf("Si è verificato un errore nell'allocazione di memoria\n");
            exit(1);
        }
        struttura->N = NUM_THREADS;
        struttura->Indice = i;
        err = pthread_create(&tids[i], NULL, threadFunc, (void*)struttura);
        if (err != 0) {
            printf("Si è verificato un errore nella creazione di un thread\n");
            exit(1);
        }
        printf("Creato un thread N: %d, Indice: %d\n", struttura->N, struttura->Indice);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        err = pthread_join(tids[i], NULL);
        if (err != 0) {
            printf("Si è verificato un errore nella join di un thread\n");
            exit(1);
        }
        printf("Join di un thread\n");
    }
    return 0;
}