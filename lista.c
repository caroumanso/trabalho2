#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "arvore.h"

struct lista {
    Celula* fim;
    Celula* ini;
};

struct celula {
    Arv* arvore;
    Celula* prox;
};

int lista_vazia(Lista* l) {
    return l->ini == NULL;
}

void libera_celula(Celula* c) {
    free(c);
}

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

Celula* lista_retira_prim(Lista* l) {
    Celula* aux;
    if (!lista_vazia(l)) {
        aux = l->ini;
        if (l->ini->prox == NULL)
            l->ini = NULL;
        else
            l->ini = l->ini->prox;
        return aux;
    }
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
    Celula *p = l->ini;
    Celula *q = p->prox;
    while(p!=NULL){
        while(q!= NULL){
            if(retorna_freq(q->arvore)<retorna_freq(p->arvore))
                troca_arv(p, q);
            q = q->prox;
        }
        p = p->prox;
    }
}
   
void troca_arv(Celula* p, Celula* q){
    Arv* aux = p->arvore;
    p->arvore = q->arvore;
    q->arvore = aux;
}