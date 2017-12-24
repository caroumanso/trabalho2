#include "lista.h"
#ifndef DESCOMPACTADOR_H
#define DESCOMPACTADOR_H

char* getch_ext(FILE* arq);
char* concatena_saida(char* argv, char* extensao);
int retorna_freq_total(FILE* arq);
int insere_caracter_lista(FILE* arq, Lista* l);
void descompacta(Arv* huffman, FILE* saida, FILE* entrada);
int seguencia_eh_caracter(bitmap c, Arv* arv, FILE* saida, int posicao);
int bits_totais(int tam_compactado);
Lista* reconstroi_arv(FILE* entrada);
#endif /* DESCOMPACTADOR_H */

