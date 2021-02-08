#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <pthread.h>
#include "printerror.h"
#include "DBGpthread.h"

#define NUM_MARTELLI 2

int martelloFinito[NUM_MARTELLI];
int contaPali[NUM_MARTELLI];

int martellare;
int martelliTenuti;

pthread_mutex_t mutex;

pthread_cond_t condInizioMartello;
pthread_cond_t condFineMartello;

int martelliFinito() {
    return martelloFinito[0] && martelloFinito[1];
}

int nessunoHaIniziato() {
    return !martelloFinito[0] && !martelloFinito[1];
}

void *TienePalo(void* arg) {
    int i, faiRiposo;
    char Tlabel[128];
    sprintf(Tlabel, "TienePalo");
    while(1) {
        faiRiposo = 0;
        printf("\n\nPresi pali\n");
        sleep(1);
        printf("martellare!\n\n");
        /* avviso i martelli */
        DBGpthread_mutex_lock(&mutex, Tlabel);
        martellare = 1;
        DBGpthread_cond_broadcast(&condInizioMartello, Tlabel);
        while (!martelliFinito()) {
            DBGpthread_cond_wait(&condFineMartello, &mutex, Tlabel);
        }
        /* i due martelli hanno finito */
        for (i = 0; i < NUM_MARTELLI; i++) {
            martelloFinito[i] = 0;
        }
        martellare = 0;
        martelliTenuti++;
        faiRiposo = martelliTenuti % 5 == 0; 
        DBGpthread_mutex_unlock(&mutex, Tlabel);
        if (faiRiposo) {
            sleep(3);
        }
    }
}

void *Martello(void* arg) {
    int indice = *((int*)arg);
    int faiRiposo;
    char Mlabel[128];
    sprintf(Mlabel, "Martello%d", indice);
    while(1) {
        faiRiposo = 0;
        DBGpthread_mutex_lock(&mutex, Mlabel);
        if (!martellare || martelloFinito[indice]) {
            /*printf("Aspetta %d, martellare %d\n", aspetta, martellare);*/
            DBGpthread_cond_wait(&condInizioMartello, &mutex, Mlabel);
        }
        printf("%s inizia\n", Mlabel);
        DBGpthread_mutex_unlock(&mutex, Mlabel);
        
        sleep(1);

        DBGpthread_mutex_lock(&mutex, Mlabel);
        printf("%s finisce\n", Mlabel);
        martelloFinito[indice] = 1;
        DBGpthread_cond_signal(&condFineMartello, Mlabel);
        contaPali[indice]++;
        faiRiposo = contaPali[indice] % 4 == 0;
        DBGpthread_mutex_unlock(&mutex, Mlabel);
        if (faiRiposo) {
            switch (indice)
            {
            case 0:
                sleep(5);
                break;
            case 1:
                sleep(7);
            default:
                break;
            } 
        }
    }
}


int main() {
    pthread_t tid;
    int rc, i;

    martelliTenuti = 0;
    martellare = 0;

    DBGpthread_mutex_init(&mutex, NULL, "Mutex");
    DBGpthread_cond_init(&condInizioMartello, NULL, "InizioMartello");
    DBGpthread_cond_init(&condFineMartello, NULL, "FineMartello");

    rc = pthread_create(&tid, NULL, TienePalo, NULL);
    if (rc) {
        PrintERROR_andExit(rc, "Errore nella creazione del thread");
    }
    for(i = 0; i < NUM_MARTELLI; i++) {
        int *p = (int*)malloc(sizeof(int));
        *p = i;
        contaPali[i] = 0;
        martelloFinito[i] = 0;
        rc = pthread_create(&tid, NULL, Martello, (void*)p);
        if (rc) {
            PrintERROR_andExit(rc, "Errore nella creazione del thread");
        }
    }
    
    pthread_exit(NULL);
    return 0;
}