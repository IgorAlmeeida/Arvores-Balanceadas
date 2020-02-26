#include <stdlib.h>
#include <stdio.h>
#include "rb.h"

int main(int argc, char const *argv[])
{
	int opcao;
	int valor;
	rb* raiz = NULL;

	while (1 == 1){

		scanf("%d", &opcao);

		switch(opcao){
			case 1:
				scanf("%d", &valor);
				inserir(&raiz, valor);
				break;
			case 2:
				pre_order(raiz);
				printf("\n");
				break;
			case 3:
				scanf("%d", &valor);
				remover(&raiz, valor);
				break;
			case 999:
				exit(0);
		}
	}

	return 0;
}
