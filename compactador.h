#ifndef COMPACTADOR_H
#define COMPACTADOR_H
#include "bitmap.h"
#include "arvore.h"
#include "lista.h"

int tam_arq(FILE* file);
unsigned char* le_arq(char* arqv);
void soma_freq(int *vet, unsigned char* buffer);
int codifica(bitmap *cod, unsigned char c, Arv* arv);
void faz_chave_busca(bitmap* vet_bm, Arv* arv, int *vet, int tam);
void compacta(int qtd, unsigned char* buffer, Arv* arv, int* vet_freq, char* argv);
void ordena_por_caracter(bitmap* vet_chave, int qtd);
bitmap retorna_bm(unsigned char c, bitmap* vet_chave, int qtd);
void libera_compacta(unsigned char* buffer, bitmap *vet_bm);
void escreve_bm(bitmap bm, FILE* saida);
bitmap inverte_bm(bitmap *bm);
void escreve_compacta(bitmap *vet_bm, unsigned char* buffer, FILE* saida);
void concatena_saida(char* destino, char* argv);
void escreve_tam_arq_compactado(bitmap *vet_bm, unsigned char* buffer, FILE* saida);
void extensao(char* ext, char* origem);
void imprime_caracter_freq(Arv* arv, FILE* saida);
#endif /* COMPACTADOR_H */

