#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int count = 0;
	srand(time(NULL));
	while(++count && (rand() % 10 == 3));
	printf("Numero di chiamate random: %d\n", count);
	return 0;
}
