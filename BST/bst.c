#include "bst.h" 
#include <stdlib.h>
#include <stdio.h>

no* criar_no(int valor){
	no* novoNo = (no*) malloc(sizeof(no));
	novoNo->esquerda = NULL;
	novoNo->direita = NULL;
	novoNo->valor = valor;

	return novoNo;
}

no* inserir_no(int valor, no* raiz){
	if (raiz == NULL){
		return criar_no(valor);
	}
	else {
		if(valor > raiz->valor){
			raiz->direita = inserir_no(valor, raiz->direita);
		}
		else {
			raiz->esquerda = inserir_no(valor, raiz->esquerda);
			
		}
		return raiz;
 
	}

}

void pre_order(no* raiz){
	if(raiz != NULL){
		printf("[%d]",raiz->valor);
		pre_order(raiz->esquerda);
		pre_order(raiz->direita);
	}
}

void in_order(no* raiz){
		if(raiz != NULL){
		in_order(raiz->esquerda);
		printf("[%d]",raiz->valor);
		in_order(raiz->direita);
	}
}

void pos_order(no* raiz){
	if(raiz != NULL){
		pos_order(raiz->esquerda);
		pos_order(raiz->direita);
		printf("[%d]",raiz->valor);
	}

}

int maior_aux(no* raiz){
	if (raiz->direita != NULL){
		return maior_aux (raiz->direita);
	}
	else{
		return raiz->valor;
	}
}


int menor_aux(no* raiz){
	if (raiz->esquerda != NULL){
		return menor_aux(raiz->esquerda); 
	}
	else{
		return raiz->valor;
	}
}



void remover_no(no* raiz, int valor){
	no* remover = buscar(raiz, valor);
	no* pai;
	no* maior_equerda;
	int valor_maior_esq;
	int aux;


	if(remover != NULL){
		if((remover->direita == NULL) && (remover->esquerda == NULL)){
			pai = buscar_pai(raiz, remover->valor);
			if(pai->esquerda == remover){
				pai->esquerda = NULL;
			}
			else {
				pai->direita = NULL;
			}
			free(remover);
			remover = NULL;
		}
		else if((remover->direita != NULL) && (remover->esquerda != NULL)){
			valor_maior_esq = maior_aux(remover->esquerda);
			maior_equerda = buscar(remover, valor_maior_esq);
			aux = maior_equerda->valor;
			remover_no(raiz, maior_equerda->valor);
			remover->valor = aux;

		}

		else {
			if(remover->direita != NULL){
				pai = buscar_pai(raiz, remover->valor);
				if(pai != NULL){
					if (pai->direita == remover){
						pai->direita = remover->direita;
					}
					else{
						pai->esquerda = remover->direita;
					}
				}
				else{
					if (raiz->direita == remover){
						raiz->direita = remover->direita;
					}
					else{
						raiz->esquerda = remover->direita;
					}
				}
			}
			else{
				pai = buscar_pai(raiz, remover->valor);
				if(pai != NULL){
					if (pai->direita == remover){
						pai->direita = remover->esquerda;
					}
					else{
						pai->esquerda = remover->esquerda;
					}
				}
				else{
					if (raiz->direita == remover){
						raiz->direita = remover->esquerda;
					}
					else{
						raiz->esquerda = remover->esquerda;
					}
				}
			}
			free(remover);
			remover = NULL;
		}
		
	}
	
}

no* buscar(no* raiz, int valor){
	if(raiz->valor == valor){
		return raiz;
	}
	else if ((raiz->valor < valor) && (raiz->direita !=NULL)){
		return buscar(raiz->direita, valor);

	}
	else if((raiz-> valor > valor) && (raiz->esquerda != NULL)){
		return buscar(raiz->esquerda, valor);
	}
	else{
		return NULL;
	}

}

no* buscar_pai(no*raiz, int valor_filho){
	if(((raiz->direita != NULL) && (raiz->direita->valor == valor_filho)) || (raiz->esquerda != NULL) && (raiz->esquerda->valor == valor_filho)){
		return raiz;
	}
	else{
		if((raiz->valor < valor_filho) && (raiz->direita != NULL)){
			return buscar_pai(raiz->direita, valor_filho);
		}
		else if ((raiz->valor > valor_filho) && (raiz->esquerda != NULL)){
			return buscar_pai(raiz->esquerda, valor_filho);
		}
		else{
			return NULL;
		}
	}
}

void buscarpai_final(no* raiz, int valor_filho){
	no* filho = buscar(raiz, valor_filho);
	if (filho != NULL){
		no* pai = buscar_pai(raiz, valor_filho);
		if(pai != NULL){
			printf("%d\n",pai->valor);
		}
		else{
			printf("-1\n");
		}
	}
	else{
		printf("-1\n");
	}	
}

int altura (no* raiz) {
   if (raiz == NULL){
      return 0;
   }
   else {
      int altura_direita = altura (raiz->direita);
      int altura_esqueda = altura (raiz->esquerda);
      if (altura_direita < altura_esqueda){
      	return altura_esqueda + 1;
      } 	
      else{
      	return altura_direita + 1;
      }
   }
}

no* minimo_sub_arvore(no* raiz){
	if(raiz != NULL){
		if(raiz->esquerda != NULL){
			return minimo_sub_arvore(raiz->esquerda);
		}
		else{
			return raiz;
		}
	}
	else{
		return NULL;
	}
}

no* achar_pai_esquedo (no* raiz, int informacao){
	no* seguinte = buscar_pai(raiz, informacao);
	if((seguinte != NULL) && (seguinte -> esquerda != NULL) && (seguinte->esquerda->valor == informacao)){
		return seguinte;
	}
	else if ((seguinte != NULL) && (seguinte->direita != NULL)&&(seguinte->direita->valor == informacao)){
		return achar_pai_esquedo(raiz, seguinte->valor);
	}
	else{
		return NULL;
	}

}

no* achar_pai_direito (no* raiz, int informacao){
	no* seguinte = buscar_pai(raiz, informacao);
	if((seguinte != NULL) && (seguinte -> direita != NULL) && (seguinte->direita->valor == informacao)){
		return seguinte;
	}
	else if ((seguinte != NULL) && (seguinte->esquerda != NULL)&&(seguinte->esquerda->valor == informacao)){
		return achar_pai_direito(raiz, seguinte->valor);
	}
	else{
		return NULL;
	}

}

void sucessor(no* raiz, int valor_antecessor){
	no* antecessor = buscar(raiz, valor_antecessor);
	no* seguinte = NULL;
	if(antecessor != NULL){
		seguinte = minimo_sub_arvore(antecessor->direita);
		if(seguinte != NULL){
			printf("%d\n", seguinte->valor);
		}
		else{
			seguinte = achar_pai_esquedo(raiz, valor_antecessor);
			if (seguinte != NULL){
				printf("%d\n",seguinte->valor);
			}
			else{
				printf("-1\n");
			}
		}
	}
	else{
		printf("-1\n");
	}
}

no* maximo (no* raiz){
	if (raiz != NULL){
		if (raiz->direita != NULL){
			return maximo (raiz);
	}
		else{
			return raiz;
		}
	}
	else{
		return NULL;
	}

}

void antecessor (no* raiz, int valor_sucessor){
	no* sucessor = buscar (raiz,  valor_sucessor);
	no* antecessor = NULL;
	if (sucessor != NULL){
		antecessor = maximo(sucessor->esquerda);
		if (antecessor != NULL){
			printf("%d\n", antecessor->valor);
		}
		else {
			antecessor = achar_pai_direito(raiz, valor_sucessor);
			if (antecessor != NULL){
				printf("%d\n", antecessor->valor);
			}
			else{
				printf("-1\n");
			}

		}
	} 
	else {
		printf("-1\n");
	}

}

