#include <stdio.h>
#include "define.h"
#include "variabiliglobali.h"

extern int conta(void);
extern int var1;

int main() {
	printf("NUM = %d, conta = %d, var1 = %d\n", NUM, conta(), var1);
	return 0;
}
