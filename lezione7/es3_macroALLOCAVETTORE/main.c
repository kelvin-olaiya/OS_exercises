#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
	int* vettore;
	int i;

	MEMORY_ALLOC(vettore);
	if (vettore == NULL ) {
		printf("Allocazione non riuscita\n");
		exit(1);
	} else {
		printf("Allocazione avvenuta con successo\n");
	}
	for (i = -19; i <= -10; i++) {
		printf("Cambio %d con %d\n", vettore[i + 19], i);
		vettore[i + 19] = i;
	}
	free(vettore);
	return 0;
}
