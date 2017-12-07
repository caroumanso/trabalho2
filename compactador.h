#ifndef COMPACTADOR_H
#define COMPACTADOR_H

typedef struct chave Chave;
int tam_arq(FILE* file);
unsigned char* le_arq(FILE* file);
void soma_freq(int *vet, unsigned char* buffer);
void codifica(Chave* vet_chave, unsigned char c, Arv* arv);
void faz_chave_busca(Chave* vet_chave, int folhas, Arv* arv, int vet, int qtd_char);
void compacta(Chave* vet_chave, int qtd, unsigned char* buffer);
void libera_compacta(Lista* l, unsigned char* buffer, Chave* vet_chave, int qtd);
void ordena_por_caracter(Chave* vet_chave, int qtd);
bitmap retorna_bm(unsigned char c, Chave* vet_chave, int qtd);

#endif /* COMPACTADOR_H */

