#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif

#include "printerror.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <pthread.h>
#include "DBGpthread.h"

#define NUM_SOBRI 4
#define NUM_UBRIACHI 2
#define POSTI_FUNIVIA 2
#define POSTO_LIBERO -1



/* global variables */
intptr_t passeggeri[POSTI_FUNIVIA];
int passeggeriSobri;
int passeggeriUbriachi;
int funiviaFaiWait;
int salite;

/* sincro variables */
pthread_cond_t condFuniviaParti, condPasseggeriScesi, condFineGiro,condPassegeriSalite;

pthread_mutex_t mutex;

int funiviaInWait = 0;

void* sobrio(void* arg) {
    
    intptr_t mioIndice = (intptr_t)arg;
    char Slabel[128];
	sprintf(Slabel,"S%"PRIiPTR,mioIndice);
    
    while(1) {
        DBGpthread_mutex_lock(&mutex, Slabel);
        while (salite == 0 || passeggeriUbriachi > 0 || passeggeriSobri >= POSTI_FUNIVIA) {
            printf("%s Aspetto il prossimo giro\n", Slabel);
            fflush(stdout);
            DBGpthread_cond_wait(&condPassegeriSalite, &mutex, Slabel);
        }

        passeggeri[passeggeriSobri] = mioIndice;
        passeggeriSobri++;

        printf("Sono salito %s\n", Slabel);
        if (passeggeriSobri == POSTI_FUNIVIA) {
            funiviaFaiWait = 0;
            salite = 0;
            printf("Dico alla funivia di partire %s\n", Slabel);
            DBGpthread_cond_signal(&condFuniviaParti, Slabel);
        }
        DBGpthread_cond_wait(&condFineGiro, &mutex,Slabel);
        passeggeriSobri--;
        printf("Sono sceso %s\n", Slabel);
        if (passeggeriSobri == 0) {
            funiviaFaiWait = 1;
            DBGpthread_cond_signal(&condPasseggeriScesi, Slabel);
        }
        DBGpthread_mutex_unlock(&mutex, Slabel);
    }
}

void *ubriaco(void* arg) {
    intptr_t mioIndice = (intptr_t)arg;
    char Ulabel[128];
    sprintf(Ulabel, "U%"PRIiPTR, mioIndice);
    while(1) {
        DBGpthread_mutex_lock(&mutex, Ulabel);
        while(salite == 0 || passeggeriSobri > 0 || passeggeriUbriachi > 0) {
            printf("Aspetto il prossimo turno %s\n", Ulabel);
            DBGpthread_cond_wait(&condPassegeriSalite, &mutex, Ulabel);
        }
        passeggeriUbriachi++;
        salite = 0;
        funiviaFaiWait = 0;
        printf("Sono ubriaco %s, funivia parti\n", Ulabel);
        DBGpthread_cond_signal(&condFuniviaParti,Ulabel);
        DBGpthread_cond_wait(&condFineGiro, &mutex, Ulabel);

        passeggeriUbriachi--;
        printf("L'ubriaco %s scende\n", Ulabel);
        funiviaFaiWait=1;
        DBGpthread_cond_signal(&condPasseggeriScesi, Ulabel);
        DBGpthread_mutex_unlock(&mutex, Ulabel);
    }
}



void* funivia(void* arg) {
    char Flabel[128];
    sprintf(Flabel, "Funivia");
    while(1) {
        DBGpthread_mutex_lock(&mutex, Flabel);
        if (funiviaFaiWait) {
            printf("Aspetto che entrino i passeggeri\n");
            DBGpthread_cond_wait(&condFuniviaParti, &mutex, Flabel);
        }
        /*printf("Sto portando a bordo [%"PRIiPTR",%"PRIiPTR"]\n\n", passeggeri[0], passeggeri[1]);*/
        printf("Flotta composta da (%d sobri, %d ubriachi)\n\n", passeggeriSobri, passeggeriUbriachi);
        DBGpthread_mutex_unlock(&mutex, Flabel);
        sleep(1);
        printf("Sono arrivato in cima\n");
        sleep(1);

        printf("Sono arrivato a destinazione\n");
        DBGpthread_mutex_lock(&mutex, Flabel);
        DBGpthread_cond_broadcast(&condFineGiro, Flabel);
        printf("Aspetto che scendano i passeggeri\n");

        DBGpthread_cond_wait(&condPasseggeriScesi, &mutex, Flabel);

        printf("Passeggeri entrate\n");
        DBGpthread_cond_broadcast(&condPassegeriSalite, Flabel);
        salite = 1;
        printf("Ora potete salire\n\n\n");
        DBGpthread_mutex_unlock(&mutex, Flabel);

    }
}

int main() {
    intptr_t i;
    pthread_t tid;
    int rc;

    salite = 1;
    funiviaFaiWait = 1;
    passeggeriSobri = 0;

    DBGpthread_mutex_init(&mutex, NULL, "mutex");
    
    DBGpthread_cond_init(&condPasseggeriScesi, NULL, "discesa");
    
    DBGpthread_cond_init(&condFuniviaParti, NULL, "funiviaParti");
    
    DBGpthread_cond_init(&condFineGiro, NULL, "FineGiro");
    
    DBGpthread_cond_init(&condPassegeriSalite, NULL, "PasseggeriSalite");

    
    for (i = 0; i < NUM_SOBRI; i++) {
        passeggeri[i] = POSTO_LIBERO;
        rc = pthread_create(&tid, NULL, sobrio, (void*)i);
        if (rc) {
            printf("Errore nella creazione del thread\n");
            exit(0);
        }
    }

    for (i = 0; i < NUM_UBRIACHI; i++) {
        /*passeggeri[i] = POSTO_LIBERO;*/
        rc = pthread_create(&tid, NULL, ubriaco, (void*)i);
        if (rc) {
            printf("Errore nella creazione del thread\n");
            exit(0);
        }
    }
    rc = pthread_create(&tid, NULL, funivia, NULL);
    if (rc) {
        printf("Errore nella creazione del thread\n");
        exit(0);
    }
    
    
    pthread_exit(NULL);
}


