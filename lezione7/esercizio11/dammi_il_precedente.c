#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int dammi_il_precedente(unsigned int numero) {
	static unsigned int prev = 0;
	unsigned int temp = prev;
	prev = numero;
	printf("Numero passato: %u, precedente: %u\n", numero, temp);
	return temp;
}

int main() {
	srand(time(NULL));
	while(dammi_il_precedente(rand()) % 10 != 3);
	return 0;
}
