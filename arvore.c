#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "bitmap.h"
#include "compactador.h"

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
    return;
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

Arv* retorna_arv_esq(Arv* arv) {
    return arv->esq;
}

Arv* retorna_arv_dir(Arv* arv) {
    return arv->dir;
}

static int max2(int a, int b) {
    return (a > b) ? a : b;
}

int arv_altura(Arv* a) {
    if (arv_vazia(a))
        return -1;
    else
        return 1 + max2(arv_altura(a->esq),
            arv_altura(a->dir));
}