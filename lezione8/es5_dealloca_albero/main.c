#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    int key;
    double x;
    NODO* destra;
    NODO* sinistra;
} NODO;

void dealloca_albero(NODO **ppnodo) {
    if (ppnodo == NULL || *ppnodo == NULL) {
        return;
    }
    /* Cancellazione albero di sinistra */
    if ((*ppnodo)->sinistra != NULL) {
        dealloca_albero(&((*ppnodo)->sinistra));
    }

    if ((*ppnodo)->destra != NULL) {
        dealloca_albero(&((*ppnodo)->destra));
    }

    free(*ppnodo);
    *ppnodo = NULL;
}

int main() {
    NODO* root;
    return 0;
}