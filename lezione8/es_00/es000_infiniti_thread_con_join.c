/* con_trucco.c  */

/* messi nella riga di comando del compilatore 
#define _THREAD_SAFE
#define _REENTRANT
#define _POSIX_C_SOURCE 200112L
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>	/* uintptr_t */
#include <inttypes.h> /* PRIiPTR */
#include <pthread.h>
#include <string.h>

#define NUM_THREADS 1000

int N=-1;

void *PrintHello(void *arg)
{
	/* sleep(4); */
	printf("\n %"  PRIiPTR ": Hello World! N=%d\n", (intptr_t)arg, N ); fflush(stdout);
	pthread_exit (NULL);
}

int main()
{
	pthread_t tids[NUM_THREADS];
	int rc;
	intptr_t t;
	
	while(1) {
		for(t=0;t < NUM_THREADS;t++) {
			printf("Creating thread %" PRIiPTR "\n", t);
			rc = pthread_create (&tids[t], NULL, PrintHello, (void*)t);
			if (rc){
				char buf[1024];
				strerror_r(rc, buf, 1024);
				printf("ERROR; return code from pthread_create() is %s\n", buf); fflush(stdout);
				exit(1);
			}
		}
		
		for(t=0;t < NUM_THREADS;t++) {
			int error;
			void *ptr;
			/* attendo la terminazione del thread t-esimo  */
			error=pthread_join( tids[t] , &ptr );
			if(error!=0){
				char buf[1024];
				strerror_r(error, buf, 1024);
				printf("pthread_join() failed: error=%s\n",  buf); fflush(stdout);
				exit(-1);
			}
			else {
				printf("pthread %d-esimo ID=%d restituisce\n", (int)t, (int) tids[t]); fflush(stdout);
				/* dealloco la struttura in cui mi e' stato passato il risultato */
				/*free(ptr);*/
			}
		}
	}
	
	pthread_exit (NULL);
	return(0);
}
