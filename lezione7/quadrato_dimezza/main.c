#include <stdio.h>
#include "quadrato.h"
#include "dimezza.h"

static double salva;
int  main() {
	salva = quadrato(dimezza(13.17));
	printf("Il quadrato del meta del coseno di 13.17 è: %f\n", salva);
	return 0;
}
