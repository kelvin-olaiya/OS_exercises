#include "quadrato.h"

static double salva;

double quadrato(double x) {
	salva = x * x;
	return salva;
}

