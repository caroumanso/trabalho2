#include "arvore.h"
#ifndef LISTA_H
#define LISTA_H

typedef struct celula Celula;
typedef struct lista Lista;

Lista* inic_lista();
Celula* nova_celula(Arv* arv);
void retira_2_prim(Lista* l);
void libera_celula(Celula* c);
void lista_insere(Lista* l, Celula* nova);
void ordena_lista(Lista* l);
void troca_arv(Celula* p, Celula* q);
int tam_lista(Lista* l);
void faz_arv_huffman(Lista* lista);
void faz_lista(int *vet, int tam, Lista* l);
void libera_lista(Lista* l);
Arv* retorna_arv(Lista* l);
void ordena_lista_caracter(Lista* l);

#endif /* LISTA_H */

