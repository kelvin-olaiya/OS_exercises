#include <stdio.h>
#include <stdlib.h>

typedef struct nodolista {    int key;    struct nodolista *next;  } NODOLISTA;

void aggiungi_in_testa( int KEY, NODOLISTA* *proot        )
{
NODOLISTA *ptr;
ptr=(NODOLISTA*)malloc(sizeof(NODOLISTA));
ptr->next=*proot;
ptr->key=KEY;
*proot=ptr;
}

void stampa(NODOLISTA *ptr)
{
	printf("\n");
	while(ptr)
	{
		printf("%d ", ptr->key);
		ptr=ptr->next;
	}
	printf("\n");
}

int head_delete(NODOLISTA** proot) {
	if(proot == NULL || *proot == NULL)
		return 0;
		
	NODOLISTA* tmp = *proot;
	*proot = tmp->next;
	free(tmp);
	return 1;
}

int node_delete(NODOLISTA* n) {
	if(n == NULL)
		return 0;
	
	NODOLISTA* tmp = n->next;
	n->next = tmp->next;
	free(tmp);
	return 1;
}

/* FUNZIONE DA IMPLEMENTARE !!!!!! */
int  elimina( int KEY, NODOLISTA** proot )
{
	if(proot == NULL || *proot == NULL)
		return 0;
	
	/*Verifico se è in testa*/
	if((*proot)->key == KEY)
		return head_delete(proot);
	
	NODOLISTA* tmp = *proot;
	while(tmp->next != NULL && tmp->next->key != KEY) {
		tmp = tmp->next;
	}
	if (tmp->next != NULL && tmp->next->key == KEY) {
		return node_delete(tmp);
	}
	return 0;
}


int main()
{
	NODOLISTA *root;
	root=NULL;

	/* codice aggiunto per fare la prova */
	aggiungi_in_testa( 111, &root );
	aggiungi_in_testa( 4,   &root );
	aggiungi_in_testa( 111, &root );
	aggiungi_in_testa( 71,  &root );
	stampa(root);

	elimina(   4 , &root );
	stampa(root);
	elimina( 111 , &root );
	stampa(root);
	elimina(  53 , &root );
	stampa(root);
	elimina(  71 , &root );
	stampa(root);
	elimina( 111 , &root );
	stampa(root);
	/* cerco di eliminare un elemento che non esiste */
	elimina(  10 , &root );
	stampa(root);

	return(0);
}

