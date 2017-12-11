#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

struct arvore {
    Arv* dir;
    Arv* esq;

    union {
        int freq;
        unsigned char caracter;
    };
};

Arv* cria_arv_vazia() {
    return NULL;
}

int arv_vazia(Arv* a) {
    return a == NULL;
}

void libera_arv(Arv* a) {
    if (!arv_vazia(a)) {
        libera_arv(a->dir);
        libera_arv(a->esq);
        free(a);
    }
    return NULL;
}

Arv* cria_arv(int num, Arv* dir, Arv* esq) {
    Arv* nova = (Arv*) malloc(sizeof (Arv));
    nova->dir = dir;
    nova->esq = esq;
    nova->freq = num;
    return nova;
}

Arv* cria_caracter(unsigned char c, Arv* dir, Arv* esq) {
    Arv* novo = (Arv*) malloc(sizeof (Arv));
    novo->dir = dir;
    novo->esq = esq;
    novo->caracter = c;
    return novo;
}

int arv_freq(Arv* a) {
    return a->freq;
}

int qtd_folhas(Arv* arv) {
    if (arv == NULL)
        return 0;
    if (arv->dir == NULL && arv->esq == NULL)
        return 1;
    else return (qtd_folhas(arv->dir) + qtd_folhas(arv->esq));
}
int eh_folha(Arv* arv){
    return (arv->dir == NULL && arv->esq == NULL);
}

Arv* retorna_ramoEsq(Arv* arv){
    return arv->esq;
}

Arv* retorna_ramoDir(Arv* arv){
    return arv->dir;
}
