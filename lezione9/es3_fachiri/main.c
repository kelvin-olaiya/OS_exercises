#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <inttypes.h>
#include "DBGpthread.h"
#include <unistd.h>
#include <string.h>
#include "printerror.h"

#define NUM_SPADE 10
#define NUM_FACHIRI 2
/*Global variables*/
pthread_mutex_t mutex[NUM_SPADE];

/* Thread fachiro */
void* fachiro(void* arg) {
    intptr_t numFachiro = (intptr_t)arg;
    while(1) {
        int i;
        for (i = 0; i < NUM_SPADE; i++) {
            DBGpthread_mutex_lock(&mutex[i], "fachiro");
        }
        printf("AAAAAAAH fachiro %"PRIdPTR"\n", numFachiro);
        for (i = NUM_SPADE - 1; i >= 0; i--) {
            DBGpthread_mutex_unlock(&mutex[i], "fachiro");
        }
    }
    return NULL;
}

int main() {
    pthread_t tid;
    int err;
    intptr_t i;
    for (i = 1; i <= NUM_FACHIRI; i++) {
        err = pthread_create(&tid, NULL, fachiro, (void *)i);
        if(err)
            PrintERROR_andExit(err, "Errore creazione thread");
    }
    pthread_exit(NULL);
    return 0;
}