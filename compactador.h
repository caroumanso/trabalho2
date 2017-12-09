#ifndef COMPACTADOR_H
#define COMPACTADOR_H
#include "bitmap.h"
#include "arvore.h"
#include "lista.h"

int tam_arq(FILE* file);
unsigned char* le_arq(FILE* file);
void soma_freq(int *vet, unsigned char* buffer);
void codifica(bitmap* vet_chave, unsigned char c, Arv* arv);
void faz_chave_busca(bitmap* vet_bm, Arv* arv, int *vet, int tam);
void compacta(bitmap* vet_bm, int qtd, unsigned char* buffer);
void ordena_por_caracter(bitmap* vet_chave, int qtd);
bitmap retorna_bm(unsigned char c, bitmap* vet_chave, int qtd);

#endif /* COMPACTADOR_H */

