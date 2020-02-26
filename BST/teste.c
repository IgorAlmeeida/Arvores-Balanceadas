#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

int main(int argc, char const *argv[])
{
	int opcao;
	int valor;
	no* raiz = NULL;

	while (1 == 1){


		scanf("%d", &opcao);

		switch(opcao){
			case 1:
				scanf("%d", &valor);
				raiz = inserir_no(valor, raiz);
				break;
			case 2:
				pre_order(raiz);
				printf("\n");
				break;
			case 3:
				in_order(raiz);
				printf("\n");
				break;
			case 4:
				pos_order(raiz);
				printf("\n");
				break;
			case 5:
				scanf("%d", &valor);
				remover_no(raiz,valor);
				break;
			case 6:
				printf("[%d]\n",maior_aux(raiz));
				break;
			case 7:
				printf("[%d]\n",menor_aux(raiz));
				break;
			case 8:
				printf("%d\n",altura(raiz));
				break;
			case 9:
				scanf("%d", &valor);
				buscarpai_final(raiz, valor);
				break;
			case 10:
				scanf("%d", &valor);
				sucessor(raiz, valor);
				break;
			case 11:
				scanf("%d", &valor);
				antecessor(raiz, valor);
				break;
			case 999:
				exit(0);
		}
	}

	return 0;
}