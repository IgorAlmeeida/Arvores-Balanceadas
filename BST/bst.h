#ifndef BST_H
#define BST_H

typedef struct no no;

struct no {
	int valor;
	no* esquerda;
	no* direita;
};

no* criar_no(int valor);
no* inserir_no(int valor, no* raiz);
void pre_order(no* raiz);
void in_order(no* raiz);
void pos_order(no* raiz);
int maior_aux(no* raiz);
int menor_aux(no* raiz);
void remover_no(no* raiz, int valor);
no* buscar_pai(no*raiz ,int valor);
no* buscar(no* raiz, int valor);
void sucessor(no* raiz, int valor_antecessor);
void antecessor(no* raiz, int valor_antecessor);
void buscarpai_final(no* raiz, int valor_filho);
int altura (no* raiz);


#endif

