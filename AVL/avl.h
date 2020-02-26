#ifndef BST_H
#define BST_H

typedef struct no_avl avl;

struct no_avl{
	int valor;
	int altura;
	avl* esquerda;
	avl* direita;
};

avl* inserir(int valor, avl* raiz);
void pre_order(avl* raiz);
avl* remover(int valor, avl* raiz, avl* pai);
avl* criar_no(int valor);
int fator_bal(int val_dir, int val_esq);
int balancear (avl* pivo);
int max_altura_no(int altura1, int altura2);
void att_altura(avl* raiz);
avl* rotacao_simples_direita(avl* pivo);
avl* rotacao_simples_esqueda(avl* pivo);
avl* rotacao_dupla_direita(avl* pivo);
avl* rotacao_dupla_esqueda(avl* pivo);
avl* inserir(int valor, avl* raiz);
int maior_aux(avl* raiz);
avl* remover(int valor, avl* raiz, avl* pai);




#endif
