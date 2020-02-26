#include <stdlib.h>
#include <stdio.h>
#include "rb.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLACK    "\x1b[30m"
#define ESQ 2
#define DIR 3

rb* criar_no (int valor, rb* pai){
	rb* novo = (rb*) malloc(sizeof(rb));
	novo->valor = valor;
	novo->esquerda = NULL;
	novo->direita = NULL;
	novo->cr = VERMELHO;
	novo->pai = pai;

	return novo;
}

rb* criar_no_null (rb* pai){
	rb* novo = (rb*) malloc(sizeof(rb));
	novo->esquerda = NULL;
	novo->direita = NULL;
	novo->cr = DUPLO_PRETO;
	novo-> pai = pai;

	return novo;
}

int cor(rb* no){
	if (no == NULL || no->cr == PRETO)
		return 1;
	else
		return 0;
}

int eh_esquerdo(rb* no) {
    if(no == no->pai->esquerda) 
        return 1;
    else
        return 0;
}

rb* tio (rb* no) {
    if(eh_esquerdo(no->pai))
        return no->pai->pai->direita;
    else
        return no->pai->pai->esquerda;   
}

void rotacao_simples_esquerda(rb* pivo, rb** raiz){
	rb* p = pivo;
	rb* u = p->direita;
	rb* t2 = u->esquerda;

	if (pivo->pai != NULL){
		rb* pai = pivo->pai;
		if (pivo == pai->esquerda){
			pai->esquerda = u;
		}
		else{
			pai->direita = u;
		}
	}

	u->pai = p->pai;
	u->esquerda = p;
	p->pai = u;
	p->direita = t2;

	if (t2 != NULL){
		t2->pai = p;
	}

	if (u-> pai == NULL){
		*raiz = u;
	}

	p->cr = VERMELHO;
	u->cr = PRETO;

	return;
}

void rotacao_dupla_esqueda(rb* pivo, rb** raiz){
	rb* p = pivo;
	rb* u = p->direita;
	rb* v = u->esquerda;
	rb* t2 = v->esquerda;
	rb* t3 = v->direita;

	if (pivo->pai != NULL){
		rb* pai = pivo->pai;
		if (pivo == pai->esquerda){
			pai->esquerda = v;
		}
		else{
			pai->direita = v;
		}
	}

	v->esquerda = p;
	v->direita = u;
	v->pai = p->pai;


	p->direita = t2;
	p->pai = v;

	u->esquerda = t3;
	u->pai = v;

	v->cr = PRETO;
	u->cr = VERMELHO;
	p->cr = VERMELHO;

	if (t2 != NULL){
		t2->pai = p;
	}

	if (t3 != NULL){
		t3->pai = u;
	}

	if (v->pai == NULL){
		*raiz = v;
	}

	return;
}

void rotacao_simples_direita(rb* pivo, rb** raiz){
	rb* p = pivo;
	rb* u = p->esquerda;
	rb* t2 = u->direita;

	if (pivo->pai != NULL){
		rb* pai = pivo->pai;
		if (pivo == pai->esquerda){
			pai->esquerda = u;
		}
		else{
			pai->direita = u;
		}
	}

	u->direita = p;
	p->esquerda = t2;

	u->pai = p->pai;
	p->pai = u;
	
	if (t2 != NULL){
		t2->pai = p;
	}

	if(u->pai == NULL){
		*raiz = u;
	}

	u->cr = PRETO;
	p->cr = VERMELHO;

	return;
}

void rotacao_dupla_direita(rb* pivo, rb** raiz){
	rb* p = pivo;
	rb* u = pivo->esquerda;
	rb* v = u->direita;
	rb* t2 = v->esquerda;
	rb* t3 = v->direita;

	if (pivo->pai != NULL){
		rb* pai = pivo->pai;
		if (pivo == pai->esquerda){
			pai->esquerda = v;
		}
		else{
			pai->direita = v;
		}
	}

	v->esquerda = u;
	v->direita = p;
	v->pai = p->pai;

	u->direita = t2;
	p->esquerda = t3;

	u->pai = v;
	p->pai = v;

	v->cr = PRETO;
	u->cr = VERMELHO;
	p->cr = VERMELHO;

	if (t2 != NULL){
		t2->pai = u;
	}

	if (t3 != NULL){
		t3->pai = p;
	}

	if (v->pai == NULL){
		*raiz = v;
	}
	
	return;
}


void ajustar(rb* pivo, rb** raiz){
	//caso raiz
	if (pivo->pai == NULL){
		pivo->cr = PRETO;
		return;
	}

	rb* pai = pivo->pai;
	if (pai->cr == VERMELHO){
		//caso preto avô
		if (cor(tio(pivo)) == VERMELHO){
			//printf("Recolorir\n");
			tio(pivo)->cr = PRETO;
			pai -> cr = PRETO;
			pai->pai -> cr = VERMELHO;
			ajustar(pai->pai, raiz);
		}

		else if (cor(tio(pivo))== PRETO){
			if (eh_esquerdo(pivo) && eh_esquerdo(pai)){
				//printf("RSD\n");
				rotacao_simples_direita(pivo->pai->pai, raiz);
			}
			else if (eh_esquerdo(pivo) && !eh_esquerdo(pivo->pai)){
				rotacao_dupla_esqueda(pivo->pai->pai, raiz);
				//printf("RDE\n");
			}
			else if (eh_esquerdo(pivo->pai) && !eh_esquerdo(pivo)){
				//printf("RDD\n");
				rotacao_dupla_direita(pivo->pai->pai, raiz);
			}
			else if (!eh_esquerdo(pivo) && !eh_esquerdo(pivo->pai)){
				//printf("RSE\n");
				rotacao_simples_esquerda(pivo->pai->pai, raiz);
			}
		}
	}


	return;
}

void inserir (rb** raiz, int valor){
	rb* temp = *raiz;
	rb* aux;
	rb* pai = NULL;

	int control = 0;

	while(temp != NULL){

		if (valor < temp->valor){
			pai = temp;
			temp = temp->esquerda;
			control = ESQ;
		}

		else{
			pai = temp;
			temp = temp->direita;
			control = DIR;
		}
	}

	if(pai == NULL){
		temp = criar_no(valor, pai);
		*raiz = temp;
	}

	else{
		temp = criar_no(valor, pai);
		if (control == ESQ)
			pai->esquerda = temp;
		else
			pai->direita = temp;
	}

	ajustar(temp, raiz);
}

int maior(rb* no){
	while (no->direita != NULL){
		no = no->direita;
	}
	return no->valor;
}

void rotacao_esqueda_remover(rb** raiz, rb*pivo){
	rb* p = pivo;
	rb* u = p->direita;
	rb* t2 = u->esquerda;

	if (pivo->pai != NULL){
		rb* pai = pivo->pai;
	if (pivo == pai->esquerda){
			pai->esquerda = u;
		}
		else{
			pai->direita = u;
		}
	}

	u->pai = p->pai;
	u->esquerda = p;
	p->pai = u;
	p->direita = t2;

	if (t2 != NULL){
		t2->pai = p;
	}

	if (u-> pai == NULL){
		*raiz = u;
	}
	return;
}

void rotacao_direita_remover(rb** raiz, rb*pivo){
	rb* p = pivo;
	rb* u = p->esquerda;
	rb* t2 = u->direita;

	if (pivo->pai != NULL){
		rb* pai = pivo->pai;
		if (pivo == pai->esquerda){
			pai->esquerda = u;
		}
		else{
			pai->direita = u;
		}
	}

	u->direita = p;
	p->esquerda = t2;

	u->pai = p->pai;
	p->pai = u;
	
	if (t2 != NULL){
		t2->pai = p;
	}

	if(u->pai == NULL){
		*raiz = u;
	}

	return;
}

void reajustar(rb** raiz, rb* no){
	//caso 1
	if(no->pai == NULL){
		//printf("Caso 1\n");
		if(no != NULL){
			no->cr = PRETO;
		}
		else {
			*raiz = NULL;
		}
		return;
	}
	//caso 2
	if (no->pai->direita != NULL && no->pai->esquerda != NULL){
		rb* p;
		rb* s;
		rb* x;
		rb* y;
		int control;
		if(no->pai->esquerda != NULL && no->pai->esquerda != no){
			control = ESQ;
			p = no->pai;
			s = p->esquerda;
			x = s->direita;
			y = s->esquerda;
		}

		else if (no->pai->direita != NULL && no->pai->direita != no){
			control = DIR;
			p = no->pai;
			s = p->direita;
			x = s->esquerda;
			y = s->direita;
		}

		if(cor(p) == PRETO && cor(s) == VERMELHO && cor(x) == PRETO && cor(y) == PRETO){
			if (control == DIR){
		//		printf("Caso 2 D\n");
				rotacao_esqueda_remover(raiz, p);
				p->cr = VERMELHO;
				s->cr = PRETO;
			}
			else{
		//		printf("Caso 2 E\n");
				rotacao_direita_remover(raiz, p);
				p->cr = VERMELHO;
				s->cr =PRETO;
			}
			reajustar(raiz, no);
			return;
		}

		//caso 3
		if(cor(p) == PRETO && cor(s) == PRETO && cor(x) == PRETO && cor(y) == PRETO){
		//	printf("Caso 3\n");
			s->cr = VERMELHO;
			p->cr = DUPLO_PRETO;
			if(no-> esquerda == NULL && no->direita == NULL){
				if(no->pai != NULL){
					if(eh_esquerdo(no)){
						no->pai->esquerda = NULL;
					}
					else{
						no->pai->direita = NULL;
					}
				}
				else{
					*raiz = NULL;
				}
			}
			else{
				no->cr = PRETO;
			}
		
			//no = NULL;

			reajustar(raiz, p);
			return;
		}

		//caso 4
		if(cor(p) == VERMELHO && cor(s) == PRETO && cor(x) == PRETO && cor(y) == PRETO){
		//	printf("Caso 4\n");
			s->cr = VERMELHO;
			p->cr = PRETO;
			if(no-> esquerda == NULL && no->direita == NULL){
				if(no->pai != NULL){
					if(eh_esquerdo(no)){
						no->pai->esquerda = NULL;
					}
					else{
						no->pai->direita = NULL;
					}
				}
				else{
					*raiz = NULL;
				}
			}
			else{
				no->cr = PRETO;
			}
			//no = NULL;
			return;
		}

		//caso 5
		if (cor(x) == VERMELHO){
			if(control == DIR){
		//		printf("Caso 5 D\n");
				rotacao_direita_remover(raiz, s);
				x->cr = PRETO;
				s->cr = VERMELHO;
			}
			else{
		//		printf("Caso 5 E\n");
				rotacao_esqueda_remover(raiz, s);
				x->cr = PRETO;
				s->cr = VERMELHO;
			}
			reajustar(raiz, no);
			return;
		}

		if(cor(s) == PRETO && cor(y) == VERMELHO){
		//	printf("Caso 6\n");

			if (control == DIR){
		//		printf("Caso 6 D\n");
				rotacao_esqueda_remover(raiz, p);
				s->cr = p->cr;
				y->cr = PRETO;
				p->cr = PRETO;
				if(no-> esquerda == NULL && no->direita == NULL){
					if(no->pai != NULL){
						if(eh_esquerdo(no)){
							no->pai->esquerda = NULL;
						}
						else{
							no->pai->direita = NULL;
						}
					}
					else{
						*raiz = NULL;
					}
				}
				else{
					no->cr = PRETO;
				}
				//	no = NULL;
				return;
			}
			else{
		//		printf("Caso 6 E\n");
				rotacao_direita_remover(raiz, p);
				s->cr = p->cr;
				y->cr = PRETO;
				p->cr = PRETO;
				if(no-> esquerda == NULL && no->direita == NULL){
					if(no->pai != NULL){
						if(eh_esquerdo(no)){
							no->pai->esquerda = NULL;
						}
						else{
							no->pai->direita = NULL;
						}
					}
					else{
						*raiz = NULL;
					}
				}
				else{
					no->cr = PRETO;
				}
				//no = NULL;
				return;
			}
		}
			
	}

}



void remover(rb** raiz, int valor){
	rb* temp = *raiz;
	rb* pai = NULL;

	//printf("Deletando %d\n",valor);

	while(temp != NULL){
		if(temp->valor == valor)
			break;
		else{
			if(valor < temp->valor){
				pai = temp;
				temp = temp->esquerda;
			}
			else{
				pai = temp;
				temp = temp->direita;
			}
		}

	}

	if (temp == NULL){
		 return;
	}

    if(temp-> esquerda == NULL && temp->direita == NULL && temp->pai == NULL){
        *raiz = NULL;
        return;	
    }

	if (temp-> esquerda != NULL && temp->direita != NULL){
		int var = maior(temp->esquerda);
		remover(&temp, var);
		temp->valor = var;
		return;
	}

	if (temp ->esquerda != NULL && temp->direita == NULL){
		if (pai != NULL){
			if (eh_esquerdo(temp)){
				pai->esquerda = temp-> esquerda;
				temp->esquerda->pai = temp->pai;
				temp->esquerda->cr = PRETO;
			}
			else{
				pai->direita = temp->esquerda;
				temp->esquerda->pai = temp->pai;
				temp->esquerda->cr = PRETO; 
			}			
		}
		else {
			*raiz = temp->esquerda;
			temp->esquerda->pai = NULL;
			temp->esquerda->cr = PRETO;
		}
		free(temp);
		return;
	}

	if (temp->esquerda == NULL && temp->direita != NULL){
		if (pai != NULL){
			if (eh_esquerdo(temp)){
				pai->esquerda = temp->direita;
				temp->direita->pai = temp->pai;
				temp->direita->cr = PRETO;
			}
			else{
				pai->direita = temp->direita;
				temp->direita->pai = temp->pai;
				temp->direita->cr = PRETO;
			}
		}
		else{
			*raiz = temp->direita;
			temp->direita->pai = NULL;
			temp->direita->cr = PRETO;
		}
		free(temp);
		return;
	}

	if (cor(temp) == VERMELHO){
		if(pai != NULL){
			if (eh_esquerdo(temp)){
				temp->pai->esquerda = NULL;
			}
			else
				temp->pai->direita = NULL;
		}
		return;
	}

	rb* no_null = criar_no_null(temp->pai);

	if(eh_esquerdo(temp)){
		temp->pai->esquerda = no_null;
	}
	else{
		temp->pai->direita = no_null;
	}
	//printf("reajustarx\n");

	reajustar(raiz, no_null);

}

void pre_order(rb* no){
	if(no != NULL){
		if(no->cr == VERMELHO){
			printf(ANSI_COLOR_RED "[%d]" ANSI_COLOR_RESET ,no->valor);
		} 
		else{
			printf(ANSI_COLOR_BLACK "[%d]" ANSI_COLOR_RESET ,no->valor);
		}
		pre_order(no->esquerda);
		pre_order(no->direita);
	}
}
