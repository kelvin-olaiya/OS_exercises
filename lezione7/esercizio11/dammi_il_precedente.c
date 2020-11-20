#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int dammi_il_precedente(unsigned int numero) {
	static int count = 0;
	static int prev;
	printf("Chiamata n %d, numero passato: %u, precedente: %u\n", count+1, numero, prev);
	if (count == 0) {
		prev = numero;
		return count++;
	} else {
		unsigned int ret = prev;
		prev = numero;
		return count++, ret;
	}
	return 0;
}

int main() {
	srand(time(NULL));
	while(dammi_il_precedente(rand()) % 10 != 3);
	return 0;
}
