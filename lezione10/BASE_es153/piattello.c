/* file:  piattello.c */

#ifndef _THREAD_SAFE
	#define _THREAD_SAFE
#endif
#ifndef _POSIX_C_SOURCE
	#define _POSIX_C_SOURCE 200112L
#endif

/* la   #define _POSIX_C_SOURCE 200112L   e' dentro printerror.h */
#ifndef _BSD_SOURCE
#define _BSD_SOURCE     /* per random e srandom */
#endif


/* messo prima perche' contiene define _POSIX_C_SOURCE */
#include "printerror.h"

#include <unistd.h>   /* exit() etc */
#include <stdlib.h>     /* random  srandom */
#include <stdio.h>
#include <string.h>     /* per strerror_r  and  memset */
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h> /*gettimeofday() struct timeval timeval{} for select()*/
#include <time.h> /* timespec{} for pselect() */
#include <limits.h> /* for OPEN_MAX */
#include <errno.h>
#include <assert.h>
#include <stdint.h>     /* uint64_t intptr_t */
#include <inttypes.h>   /* per PRIiPTR */
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

#include "DBGpthread.h"

#define NUMTIRATORI 10
#define DELAYTRADUEPIATTELLI8sec 8

/* dati da proteggere */
int inAria;

/* variabili per la sincronizzazione */
pthread_cond_t lancioPiattello;
pthread_mutex_t mutex;

void attendi( int min, int max) {
	int secrandom=0;
	if( min > max ) return;
	else if ( min == max ) 
		secrandom = min;
	else
		secrandom = min + ( random()%(max-min+1) );
	do {
		/* printf("attendi %i\n", secrandom);fflush(stdout); */
		secrandom=sleep(secrandom);
		if( secrandom>0 ) 
			{ printf("sleep interrupted - continue\n"); fflush(stdout); }
	} while( secrandom>0 );
	return;
}

void *Tiratore (void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;

	indice=(intptr_t)arg;
	sprintf(Plabel,"Tiratore%" PRIiPTR "",indice);

	/*  da completare  */
	DBGpthread_mutex_lock(&mutex, "tiratore");
	while ( 1 ) {		
		/* il tiratore  attende l'inizio del volo del piattello */
		printf("tiratore %s attende piattello \n", Plabel);
	        fflush(stdout);
		DBGpthread_cond_wait(&lancioPiattello, &mutex, "tiratore");
		
		printf("tiratore %s mira e .... \n", Plabel);
	        fflush(stdout);
		DBGpthread_mutex_unlock(&mutex, "tiratore");

		/* il tiratore si prepara a sparare impiegando da 2 a 4 secondi */
		attendi( 2, 4 );
		/*	da completare  */
		DBGpthread_mutex_lock(&mutex, "tiratore");
		if (inAria == 0) {
			printf("AAAAAAh!!! %s\n",Plabel);
		} else {
			inAria = 0;
		}

		/* il tiratore finisce il tentativo di sparare al piattello in volo */
		printf("tiratore %s ha sparato o e' arrivato tardi\n", Plabel);
	        fflush(stdout);
	}
	pthread_exit(NULL); 
}


void *Piattello (void *arg) 
{ 
	char Plabel[128];
	intptr_t indice;

	indice=(intptr_t)arg;
	sprintf(Plabel,"Piattello%" PRIiPTR "",indice);
	DBGpthread_mutex_lock(&mutex, "piattello");
	inAria = 1;
	printf("piattelo %s inizia volo\n", Plabel);
        fflush(stdout);
	DBGpthread_cond_broadcast(&lancioPiattello, "piattello");
	DBGpthread_mutex_unlock(&mutex, "piattello");
	/* il piattello vola per tre secondi */
	attendi( 3, 3 );


	DBGpthread_mutex_lock(&mutex, "piattello");
	inAria = 0;
	DBGpthread_mutex_unlock(&mutex, "piattello");
	
	printf("piattelo %s finisce volo e termina\n", Plabel);
       	fflush(stdout);

	/*  da completare  */


	pthread_exit(NULL); 
}


int main ( int argc, char* argv[] ) 
{ 
	pthread_t    th; 
	int  rc;
	uintptr_t i=0;
	int seme;
	/* aggiungete eventuali vostre variabili */

	seme=time(NULL);
        srandom(seme);

	/* INIZIALIZZATE LE VOSTRE VARIABILI CONDIVISE e tutto quel che serve - fate voi */
	inAria = 0;
	DBGpthread_mutex_init(&mutex, NULL, "main");
	DBGpthread_cond_init(&lancioPiattello, NULL, "main");


	/* all'inizio non c'e' nessun piattello in volo */


	/* CREAZIONE PTHREAD dei tiratori */
	for(i=0;i<NUMTIRATORI;i++) {
		rc=pthread_create(&th,NULL,Tiratore,(void*)i); 
		if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	/* CREAZIONE NUOVO PIATTELLO OGNI 8 secondi */
	i=0;
	while(1) {
			/* un nuovo piattello ogni 8 secondi */
			attendi( DELAYTRADUEPIATTELLI8sec, DELAYTRADUEPIATTELLI8sec );
			i++;

			rc = pthread_create(&th, NULL, Piattello, NULL);
			if(rc) PrintERROR_andExit(rc,"pthread_create failed");
	}

	pthread_exit(NULL);
	return(0); 
} 
  
