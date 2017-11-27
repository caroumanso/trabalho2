#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#define NUM 0
#define CAR 1

struct arvore {
    Arv* dir;
    Arv* esq;

    union {
        int freq;
        unsigned char caracter;
    };
};

Arv* cria_arvvazia() {
    return NULL;
}

int arv_vazia(Arv* a) {
    return a == NULL;
}

Arv* libera_arv(Arv* a) {
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

//a frequencia do caracter entra no ramo da direita

Arv* cria_caracter(unsigned char c, Arv* dir, Arv* esq) {
    Arv* novo = (Arv*) malloc(sizeof (Arv));
    novo->dir = dir;
    novo->esq = esq;
    novo->caracter = c;
    return novo;
}

int retorna_freq(Arv* a) {
    return a->dir->freq;
}

