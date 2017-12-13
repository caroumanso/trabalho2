#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "bitmap.h"

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

int eh_no_de_folha(Arv* arv) {
    return (arv->dir->dir == NULL && arv->dir->esq == NULL);
}

unsigned char retorna_caracter(Arv* arv) {
    return arv->dir->caracter;
}

void faz_caminho_arv(Arv* arv, FILE* saida, bitmap bm_arv) {
    if (bitmapGetMaxSize(bm_arv) == bitmapGetLength(bm_arv)) {
        escreve_bm(bm_arv, saida);
        libera_bm(bm_arv);
        bm_arv = bitmapInit(2048);
    }
    if (eh_no_de_folha(arv)) {
        fprintf(saida, "1");
        fprintf(saida, "%d", retorna_caracter(arv));
    }
    else if (!arv_vazia(arv)) {
        fprintf(saida, "0");
        faz_caminho_arv(arv->esq, saida, bm_arv);
        faz_caminho_arv(arv->dir, saida, bm_arv);
    }
}