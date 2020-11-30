#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define THREAD_NUM 10

void * func(void * arg) {
	sleep(5);
	if (arg != NULL) {
		printf("I recieved %f\n", *((double *) arg));
	}
	pthread_exit(NULL);
}

int main() {
	pthread_t id;
	int i;
	
	srand(time(NULL));
	for(i = 0; i < THREAD_NUM; i++) {
		double* r = (double *)malloc(sizeof(double));
		if (r != NULL) {
			*r = (int)rand();
			pthread_create(&id, NULL, func, (void *)r);
		}
	}
	pthread_exit(NULL);
	return 0;
}

