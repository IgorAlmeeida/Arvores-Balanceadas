#include <stdlib.h>
#include <stdio.h>
#include "avl.h"

int main(int argc, char const *argv[])
{
	int opcao;
	int valor;
	avl* raiz = NULL;

	while (1 == 1){


		scanf("%d", &opcao);

		switch(opcao){
			case 1:
				scanf("%d", &valor);
				raiz = inserir(valor, raiz);
				break;
			case 2:
				pre_order(raiz);
				printf("\n");
				break;
			case 3:
				scanf("%d", &valor);
				raiz = remover(valor, raiz, NULL);
				break;
			case 999:
				exit(0);
		}
	}

	return 0;
}
