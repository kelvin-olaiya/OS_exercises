#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <pthread.h>
#include "printerror.h"
#include "DBGpthread.h"

pthread_mutex_t mutex;

int SoccorritoreArrivato;
int SoccorritoreTerminato;
int rischiestaSoccorso;


pthread_cond_t condInizioIntervento;
pthread_cond_t condFineIntervento;
pthread_cond_t condRiechiestaSoccorso;

void *soccorritore(void *arg) {
    char Plabel[128];
    char Olabel[128];
    int indice = *((int*)arg);
    free(arg);
    sprintf(Plabel, indice ? "Medico" : "Esorcista");
    sprintf(Olabel, indice ? "Esorcista" : "Medico");

    while(1) {
        DBGpthread_mutex_lock(&mutex, Plabel);
        /* attendo una richiesta di soccorso */
        if (!rischiestaSoccorso) {
            printf("[%s] Mi metto in attesa di una richiesta di soccorso\n", Plabel);
            DBGpthread_cond_wait(&condRiechiestaSoccorso, &mutex, Plabel);
        }
        /* ricevuta richiesta soccorso controllo se e arrivato anche l'esorcista */
        printf("[%s] Pronto per iniziare l'intervento\n", Plabel);
        if (!SoccorritoreArrivato) {
            SoccorritoreArrivato = 1;
            /* aspetto l'esorcista */
            printf("[%s] Aspetto che arrivi %s\n", Plabel, Olabel);
            DBGpthread_cond_wait(&condInizioIntervento, &mutex, Plabel);
        } else {
            /* senno lo avviso che possiamo iniziare */
            printf("[%s] Sono arrivato, iniziamo!\n", Plabel);
            DBGpthread_cond_signal(&condInizioIntervento, Plabel);
        }
        rischiestaSoccorso = 0;
        DBGpthread_mutex_unlock(&mutex, Plabel);

        /* intervento */
        sleep(2);

        DBGpthread_mutex_lock(&mutex, Plabel);
        if (SoccorritoreTerminato) {
            /* L'intervento e terminato che puo rialzarzi */
            printf("[%s] L'intervento è terminato\n", Plabel);
            DBGpthread_cond_broadcast(&condFineIntervento, Plabel);
        } else {
            SoccorritoreTerminato = 1;
            /* aspetto che anche l'esorcista termini */
            printf("[%s] Aspetto che %s termini\n", Plabel, Olabel);
            DBGpthread_cond_wait(&condFineIntervento, &mutex, Plabel);
        }
        /* l'intervento e terminato */
        SoccorritoreTerminato = 0;
        SoccorritoreArrivato = 0;
        DBGpthread_mutex_unlock(&mutex, Plabel);
    }

}

void *professore(void *arg) {
    char Plabel[128];
    sprintf(Plabel, "Professore");
    while(1) {
        /* richiedo aiuto */
        DBGpthread_mutex_lock(&mutex, Plabel);
        printf("Sono caduto dalle scale\n");
        rischiestaSoccorso =  1;
        /* avviso i soccorritori */
        DBGpthread_cond_broadcast(&condRiechiestaSoccorso, Plabel);
        printf("Aspetto che mi soccorrano\n");
        DBGpthread_cond_wait(&condFineIntervento, &mutex, Plabel);

        printf("Grazie tante ai miei soccorritori, vado a fare lezione\n\n\n");
        DBGpthread_mutex_unlock(&mutex, Plabel);

        /* faccio lezione */
        sleep(4);
    }
}

int main() {
    pthread_t tid;
    int rc, i;
    SoccorritoreArrivato = 0;
    SoccorritoreTerminato = 0;
    rischiestaSoccorso = 0;

    DBGpthread_mutex_init(&mutex, NULL, "mutex");
    DBGpthread_cond_init(&condInizioIntervento, NULL, "condInizioIntervento");
    DBGpthread_cond_init(&condFineIntervento, NULL, "condFineIntervento");
    DBGpthread_cond_init(&condFineIntervento, NULL, "condRichiestaSoccorso");

    rc = pthread_create(&tid, NULL, professore, NULL);
    if (rc) {
        printf("Errore nella creazione del thread\n");
    }
    
    for (i = 0; i < 2; i++) {
        int *p = (int*)malloc(sizeof(int));
        *p = i;
        rc = pthread_create(&tid, NULL, soccorritore, (void *)p);
        if (rc) {
            printf("Errore nella creazione del thread\n");
        }
    }
    
    pthread_exit(NULL);
    return 0;
}