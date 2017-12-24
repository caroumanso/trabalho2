#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arvore.h"

struct celula {
    Arv* arvore;
    Celula* prox;
};

struct lista {
    Celula* fim;
    Celula* ini;
};

Lista* inic_lista() {
    Lista* sentinela = (Lista*) malloc(sizeof (Lista));
    sentinela->fim = NULL;
    sentinela->ini = NULL;
    return sentinela;
}

Celula* nova_celula(Arv* arv) {
    Celula* cel = (Celula*) malloc(sizeof (Celula));
    cel->arvore = arv;
    cel->prox = NULL;
    return cel;
}

void retira_2_prim(Lista* l) {
    Celula* p = l->ini;
    Celula* q = l->ini->prox;
    if (q->prox == NULL)
        l->ini = NULL;
    else
        l->ini = q->prox;
    free(p);
    free(q);
}

void lista_insere(Lista* l, Celula* nova) {
    if (l->ini == NULL) {
        l->ini = nova;
        l->fim = nova;
    } else {
        l->fim->prox = nova;
        l->fim = nova;
    }
}

void ordena_lista(Lista* l) {
    Celula *p, *q;
    for (p = l->ini; p != NULL; p = p->prox) {
        for (q = p->prox; q != NULL; q = q->prox) {
            if (arv_freq(q->arvore) < arv_freq(p->arvore))
                troca_arv(p, q);
        }
    }
}

void ordena_lista_caracter(Lista* l){
    Celula* p, *q;
    for(p = l->ini; p != NULL; p = p->prox){
        for(q = p->prox; q!=NULL; q= q->prox){
            if(arv_freq(q->arvore) == arv_freq(p->arvore)){
                if(retorna_caracter(q->arvore) > retorna_caracter(p->arvore))
                    troca_arv(p, q);
            }
        }
    }
}

void troca_arv(Celula* p, Celula* q) {
    Arv* aux = p->arvore;
    p->arvore = q->arvore;
    q->arvore = aux;
}

int tam_lista(Lista* l) {
    int aux = 0;
    Celula* p = l->ini;
    while (p != NULL) {
        aux++;
        p = p->prox;
    }
    return aux;
}

void faz_arv_huffman(Lista* lista) {
    while (tam_lista(lista) != 1) {
        Celula* p = lista->ini;
        Arv* novo_ramo = cria_arv((arv_freq(p->arvore) + arv_freq(p->prox->arvore)), lista->ini->prox->arvore, lista->ini->arvore);
        Celula* nova_cel = nova_celula(novo_ramo);
        retira_2_prim(lista);
        lista_insere(lista, nova_cel);
        ordena_lista(lista);
    }
}

void faz_lista(int *vet, int tam, Lista* l) {
    int i;
    for (i = 0; tam > i; i++) {
        if (vet[i] != 0) {
            Arv* carac = cria_arv(vet[i], cria_caracter(i, cria_arv_vazia(), cria_arv_vazia()), cria_arv_vazia());
            Celula* celula = nova_celula(carac);
            lista_insere(l, celula);
        }
    }
}

void libera_lista(Lista* l) {
    libera_arv(l->ini->arvore);
    free(l->ini);
    free(l);
}

Arv* retorna_arv(Lista* l) {
    return l->ini->arvore;
}