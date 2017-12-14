#include "bitmap.h"

#ifndef ARVORE_H
#define ARVORE_H
typedef struct arvore Arv;

Arv* cria_arv(int num, Arv* dir, Arv* esq);
Arv* cria_caracter(unsigned char c, Arv* dir, Arv* esq);
Arv* cria_arv_vazia();
int arv_vazia(Arv* a);
void libera_arv(Arv* a);
int arv_freq(Arv* a);
int eh_no_de_folha(Arv* arv);
unsigned char retorna_caracter(Arv* arv);
void faz_caminho_arv(Arv* arv, FILE* saida, bitmap *bm_arv);
Arv* retorna_arv_esq(Arv* arv);
Arv* retorna_arv_dir(Arv* arv);

#endif /* ARVORE_H */
