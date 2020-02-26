#ifndef RB_H
#define RB_H


enum cor {VERMELHO, PRETO, DUPLO_PRETO};

typedef enum cor cores;

typedef struct no_rb rb;

struct no_rb {
	int valor;
	cores cr;
	rb* pai;
	rb* direita;
	rb* esquerda;
};

void inserir(rb** raiz, int valor);
void ajustar_inserir(rb* pivo);
void remover(rb** raiz, int valor);
void pre_order(rb* raiz);
rb* criar_no (int valor, rb* pai);
rb* criar_no_null (rb* pai);
int cor(rb* no);
int eh_esquerdo(rb* no);
rb* tio (rb* no);
void rotacao_simples_esquerda(rb* pivo, rb** raiz);
void rotacao_dupla_esqueda(rb* pivo, rb** raiz);
void rotacao_simples_direita(rb* pivo, rb** raiz);
void rotacao_dupla_direita(rb* pivo, rb** raiz);
void ajustar(rb* pivo, rb** raiz);
int maior(rb* no);
void rotacao_esqueda_remover(rb** raiz, rb*pivo);
void rotacao_direita_remover(rb** raiz, rb*pivo);
void reajustar(rb** raiz, rb* no);


#endif
