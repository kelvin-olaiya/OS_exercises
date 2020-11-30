#define _BSD_SOURCE
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>

typedef struct {
	pthread_t t;
	int index;
} arg_struct;

void * func(void * arg) {
	pthread_t th;
	arg_struct* a;
	int rc, rj;
	if (arg != NULL) {
		arg_struct* recieved = (arg_struct *)arg;
		printf("My index is %d\n", recieved->index);
		usleep(1000);
		a = (arg_struct*)malloc(sizeof(arg_struct));
		if (a != NULL) {
			a->index = recieved->index + 1;
			a->t = pthread_self();
			rc = pthread_create(&th, NULL, func, (void *)a);
			if(rc) {
				printf("[ERROR] in creating thread %d\n", rc);
			} else {
				printf("Created thread with error %d\n", rc);
			}
		} 
		rj = pthread_join(recieved->t, NULL);
		if(rj) {
			printf("[ERROR] in waiting for father %d\n", rj);
		} else {
			printf("Waiting for father %d\n", rj);
		}
		pthread_exit(NULL);
		free(arg);
	}
	return NULL;
}

int main() {
	pthread_t t;
	arg_struct* a;
	usleep(1000);
	a = (arg_struct*)malloc(sizeof(arg_struct));
	if (a != NULL) {
		a->index = 1;
		a->t = pthread_self();
		pthread_create(&t, NULL, func, (void *)a);
	}
	pthread_exit(NULL);
	return 0;
}
