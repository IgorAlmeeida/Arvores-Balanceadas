#include "avl.h" 
#include <stdlib.h>
#include <stdio.h>

avl* criar_no(int valor){
	avl* no = (avl*) malloc(sizeof(avl));
	no->esquerda = NULL;
	no->direita = NULL;
	no->altura = 1;
	no->valor = valor;
}

int fator_bal(int val_dir, int val_esq){
	return val_dir - val_esq;
}

int balancear (avl* pivo){
	int fb;
	if (pivo->esquerda == NULL && pivo->direita == NULL){
		return 0;
	}
	else{
		if(pivo->esquerda != NULL && pivo->direita != NULL){
			fb = fator_bal(pivo->direita->altura, pivo->esquerda->altura);
		}
		else if (pivo->esquerda != NULL){
			fb = fator_bal(0, pivo->esquerda->altura);
		}
		else{
			fb = fator_bal(pivo->direita->altura, 0);
		}
	}
	return fb;
}

int max_altura_no(int altura1, int altura2){
	if (altura1 > altura2){
		return altura1;
	}
	return altura2;
}

void att_altura(avl* raiz){
	if((raiz->esquerda != NULL && raiz->direita == NULL) || (raiz->esquerda == NULL && raiz->direita != NULL)){
		if(raiz->esquerda !=NULL){
			raiz->altura =raiz->esquerda->altura + 1;
		}
		else{
			raiz->altura =raiz->direita->altura + 1;
		}
	}
	else{
		if(raiz->esquerda != NULL && raiz->direita != NULL){
			raiz->altura = max_altura_no(raiz->esquerda->altura, raiz->direita->altura) + 1;
		}
		else{
			raiz->altura = 1;
		}
		
	}
}

avl* rotacao_simples_direita(avl* pivo){
	avl* p = pivo;
	avl* u = p->esquerda;
	avl* t2 = u->direita;

	u->direita = p;
	p->esquerda = t2;

	att_altura(p);
	att_altura(u);
	

	return u;
}

avl* rotacao_simples_esqueda(avl* pivo){
	avl* p = pivo;
	avl* u = p->direita;
	avl* t2 = u->esquerda;

	u->esquerda = p;
	p->direita = t2;

	att_altura(p);
	att_altura(u);

	return u;
}

avl* rotacao_dupla_direita(avl* pivo){
	avl* p = pivo;
	avl* u = pivo->esquerda;
	avl* v = u->direita;
	avl* t2 = v->esquerda;
	avl* t3 = v->direita;

	v->esquerda = u;
	v->direita = p;
	u->direita = t2;
	p->esquerda = t3;

	att_altura(p);
	att_altura(u);
	att_altura(v);

	return v;
}

avl* rotacao_dupla_esqueda(avl* pivo){
	avl* p = pivo;
	avl* u = p->direita;
	avl* v = u->esquerda;
	avl* t2 = v->esquerda;
	avl* t3 = v->direita;

	v->esquerda = p;
	v->direita = u;
	p->direita = t2;
	u->esquerda = t3;

	att_altura(p);
	att_altura(u);
	att_altura(v);

	return v;
}

avl* inserir(int valor, avl* raiz){
	int fb;
	if (raiz == NULL){
		return criar_no(valor);
	}
	else{
		if(raiz->valor > valor){
			raiz->esquerda = inserir(valor, raiz->esquerda);
			att_altura(raiz);
			fb = balancear(raiz);
			switch (fb){
				case -2:
					if(balancear(raiz->esquerda) < 0){
						raiz = rotacao_simples_direita(raiz);
					}
					else {
						raiz = rotacao_dupla_direita(raiz);
					}
					break;
				case 2: 
					if(balancear(raiz->direita)< 0){
						raiz = rotacao_dupla_esqueda(raiz);
					}
					else{
						raiz = rotacao_simples_esqueda(raiz);
					}
					break;
			}
		}
		else{
			raiz->direita = inserir(valor, raiz->direita);
			att_altura(raiz);
			fb = balancear(raiz);
			switch (fb){
				case 2:
					if(balancear(raiz->direita) > 0){
						raiz = rotacao_simples_esqueda(raiz);
					}
					else {
						raiz = rotacao_dupla_esqueda(raiz);
					}
					break;
				case -2:
					if (balancear(raiz->esquerda) > 0){
						raiz = rotacao_dupla_direita(raiz);
					}
					else{
						raiz = rotacao_simples_direita(raiz);
					}
					break;
			}	
		}

	}
	return raiz;
}

int maior_aux(avl* raiz){
	if (raiz->direita != NULL){
		return maior_aux (raiz->direita);
	}
	else{
		return raiz->valor;
	}
}

avl* remover(int valor, avl* raiz, avl* pai){
	if(raiz != NULL){
		if (raiz->valor == valor){
			if (raiz->esquerda == NULL && raiz->direita == NULL){
				if(pai != NULL){
					if(pai->esquerda == raiz){
						pai->altura = 1;
						free(raiz);
						raiz = NULL;
				}
					else{
						pai->altura = 1;
						free(raiz);
						raiz = NULL;
					}
				}
				else{
					free(raiz);
					raiz = NULL;
				}
			}
			else{
				
				if ((raiz->esquerda != NULL && raiz->direita == NULL) || raiz->direita != NULL && raiz->esquerda == NULL){
					if (pai != NULL){
						if(pai->esquerda->valor == raiz->valor){
						if (raiz->esquerda != NULL){
							pai->esquerda = raiz->esquerda;
							free(raiz);
							raiz = raiz->esquerda;
						}
						else{
							pai->esquerda = raiz->direita;
							free(raiz);
							raiz = raiz->direita;
						}
					}
					else{
						if(raiz->esquerda != NULL){
							pai->direita = raiz->esquerda;
							free(raiz);
							raiz = raiz->esquerda;
						}
						else {
							pai->direita = raiz->direita;
							free(raiz);
							raiz = raiz->direita;
						}
					}
				}
				else{
					if (raiz->esquerda != NULL){
						raiz->valor = raiz->esquerda->valor;
						free(raiz->esquerda);
						raiz->esquerda = NULL;
					}
					else{
						raiz->valor = raiz->direita->valor;
						free(raiz->direita);
						raiz->direita = NULL;
					}
				}
			}
					
				else {
					int fb;
					raiz->valor = maior_aux(raiz->esquerda);
					remover(raiz->valor, raiz->esquerda, raiz);
					att_altura(raiz);
					fb = balancear(raiz);
					switch (fb){
						case -2:
							if(balancear(raiz->esquerda) <= 0){
								raiz = rotacao_simples_direita(raiz);
							}
							else {
								raiz = rotacao_dupla_direita(raiz);
							}
							break;
						case 2: 
							if(balancear(raiz->direita)< 0){
								raiz = rotacao_dupla_esqueda(raiz);
							}
							else{
								raiz = rotacao_simples_esqueda(raiz);
							}
							break;
						case 0:
						if(raiz ->esquerda != NULL && raiz->direita != NULL){

							if (balancear (raiz->esquerda) == -1 && raiz->esquerda->direita == NULL && balancear(raiz->direita) == 1 && raiz->direita->esquerda == NULL){
								raiz = rotacao_simples_direita(raiz);
								raiz-> direita = rotacao_simples_esqueda(raiz->direita);
								att_altura(raiz);
							}
						}
						break;
					}

				}
			}
		}
		else{
			int fb;
			if (raiz->valor > valor){
				raiz->esquerda = remover(valor, raiz->esquerda, raiz);
				att_altura(raiz);
				fb = balancear(raiz);
				switch (fb){
					case -2:
						if(balancear(raiz->esquerda) <= 0){
							raiz = rotacao_simples_direita(raiz);
						}
						else {
							raiz = rotacao_dupla_direita(raiz);
						}
						break;
					case 2: 
						if(balancear(raiz->direita)< 0){
							raiz = rotacao_dupla_esqueda(raiz);
						}
						else{
							raiz = rotacao_simples_esqueda(raiz);
						}
						break;
					case 0:
						if(raiz ->esquerda != NULL && raiz->direita != NULL){

							if (balancear (raiz->esquerda) == -1 && raiz->esquerda->direita == NULL && balancear(raiz->direita) == 1 && raiz->direita->esquerda == NULL){
								raiz = rotacao_simples_direita(raiz);
								raiz-> direita = rotacao_simples_esqueda(raiz->direita);
								att_altura(raiz);
							}
						}
						break;
				}
				
			}
			else{
				raiz->direita = remover(valor, raiz->direita, raiz);
				att_altura(raiz);
				fb = balancear(raiz);
				switch (fb){
					case -2:
						if(balancear(raiz->esquerda) <= 0){
							raiz = rotacao_simples_direita(raiz);
						}
						else {
							raiz = rotacao_dupla_direita(raiz);
						}
						break;
					case 2: 
						if(balancear(raiz->direita)< 0){
							raiz = rotacao_dupla_esqueda(raiz);
						}
						else{
							raiz = rotacao_simples_esqueda(raiz);
						}
						break;
					case 0:
						if(raiz ->esquerda != NULL && raiz->direita != NULL){
							if (balancear (raiz->esquerda) == -1 && raiz->esquerda->direita == NULL && balancear(raiz->direita) == 1 && raiz->direita->esquerda == NULL){
								raiz = rotacao_simples_direita(raiz);
								raiz-> direita = rotacao_simples_esqueda(raiz->direita);
								att_altura(raiz);
							}
						}
						break;
				}
			}
		}
	}
	return raiz;
}
	

void pre_order(avl* raiz){
	if(raiz != NULL){
		printf("[%d,%d]",raiz->valor, balancear(raiz));
		pre_order(raiz->esquerda);
		pre_order(raiz->direita);
	}
}


