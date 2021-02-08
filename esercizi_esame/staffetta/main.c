#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <pthread.h>
#include "printerror.h"
#include "DBGpthread.h"

#define ATLETI_ALFA 5
#define ATLETI_BETA 4
#define ALFA 0
#define BETA 1

int giriALFA[ATLETI_ALFA];
int giriBETA[ATLETI_BETA];
int primoGiro;

int numInCorsa;
int tipoCorridore;

pthread_mutex_t mutex;
pthread_cond_t condAttesaTestimone;
pthread_cond_t condPassaggioTestimone;
typedef struct {
    int tipo;
    int indice;
} atleta;

int puoFareGiro(int tipo, int indice) {
    int i;
    int max = tipo ? ATLETI_BETA : ATLETI_ALFA;
    int giri = tipo ? giriBETA[indice] : giriALFA[indice];
    for (i = 0; i < max; i++) {
        if (i != indice) {
            if ((tipo == ALFA && giriALFA[i] < giri)
                || (tipo == BETA && giriBETA[i] < giri)) {
                    /*printf("tipo: %d, indice %d, giri %d\n", tipo, indice, giri);*/
                    return 0;
            }
                
        }
    }
    return 1;
}

void fineGiro(int tipo,int indice) {
    tipo ? giriBETA[indice]++ : giriALFA[indice]++;
}

void *corridore(void* arg) {
    char Clabel[128];
    int indice = ((atleta*)arg)->indice;
    int tipo = ((atleta*)arg)->tipo;
    free(arg);
    sprintf(Clabel, "Corridore%s%d", tipo ? "BETA" : "ALFA", indice); 
    
    while(1) {
        DBGpthread_mutex_lock(&mutex, Clabel);
        while ((primoGiro && tipo != ALFA) 
            || tipoCorridore == tipo
            || numInCorsa == 1 
            || !puoFareGiro(tipo, indice)) {
            DBGpthread_cond_wait(&condAttesaTestimone, &mutex, Clabel);
        }
        if (!primoGiro) {
            /* posso prendere il testimone */
            DBGpthread_cond_signal(&condPassaggioTestimone, Clabel);
            /* aspetto che l'altro lasci */
            printf("[%s] afferrato testimone\n", Clabel);
            numInCorsa++;
            DBGpthread_cond_wait(&condPassaggioTestimone, &mutex, Clabel);
        } else {
            numInCorsa++;
        }
        /* ha lasciato posso correre */
        tipoCorridore = tipo;
        primoGiro = 0;
        printf("[%s] inizio a correre\n", Clabel);
        DBGpthread_mutex_unlock(&mutex, Clabel);
        sleep(1);

        DBGpthread_mutex_lock(&mutex, Clabel);
        /* avviso i corridori */
        printf("[%s] consegno testimone\n", Clabel);
        numInCorsa--;
        DBGpthread_cond_broadcast(&condAttesaTestimone, Clabel);
        /* aspetto che uno afferri */
        DBGpthread_cond_wait(&condPassaggioTestimone, &mutex, Clabel);
        /* avviso che ho lasciato */ 
        DBGpthread_cond_signal(&condPassaggioTestimone, Clabel);
        fineGiro(tipo, indice);
        printf("[%s] lascio testimone\n\n\n", Clabel);
        DBGpthread_mutex_unlock(&mutex, Clabel);
        /* mi rimetto in fila */

    }
}

int main() {
    pthread_t tid;
    int rc, i;
    primoGiro = 1;
    tipoCorridore = -1;
    numInCorsa = 0;

    DBGpthread_mutex_init(&mutex, NULL, "Mutex");
    DBGpthread_cond_init(&condAttesaTestimone, NULL, "AttesaTestimone");
    DBGpthread_cond_init(&condPassaggioTestimone, NULL, "PassaggioTestimone");

    for (i = 0; i < ATLETI_ALFA; i++) {
        atleta* a = (atleta*)malloc(sizeof(atleta));
        a->tipo = ALFA;
        a->indice = i;
        giriALFA[i] = 0;
        rc = pthread_create(&tid, NULL, corridore, (void *)a);
        if (rc)
            PrintERROR_andExit(rc, "Errore nella creazione del thread");    
    }

    for (i = 0; i < ATLETI_BETA; i++) {
        atleta* a = (atleta*)malloc(sizeof(atleta));
        a->tipo = BETA;
        a->indice = i;
        giriBETA[i] = 0;
        rc = pthread_create(&tid, NULL, corridore, (void *)a);
        if (rc)
            PrintERROR_andExit(rc, "Errore nella creazione del thread");    
    }
    pthread_exit(NULL);
    return 0;
}