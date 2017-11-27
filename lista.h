#include "arvore.h"
#ifndef LISTA_H
#define LISTA_H

typedef struct lista Lista;
typedef struct celula Celula;

Lista* inic_lista();
Celula* nova_celula(Arv* arv);
Celula* lista_retira_prim(Lista* l);
int lista_vazia(Lista* l);
void libera_celula(Celula* c);
void lista_insere(Lista* l, Celula* nova);
void ordena_lista(Lista* l);
void troca_arv(Celula* p, Celula* q);

#endif /* LISTA_H */

