#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compactador.h"
#include "bitmap.h"

struct chave {
    unsigned char c;
    bitmap bin;
};

int tam_arq(FILE* file) {
    fseek(file, 0, SEEK_END);
    int tam = ftell(file);
    rewind(file);
    return tam;
}

unsigned char* le_arq(FILE* file) {
    char* buffer = (char*) malloc((tam_arq(file)) * sizeof (unsigned char));
    fread(buffer, sizeof (char), tam_arq(file), file);
    fclose(file);
    return buffer;
}

void soma_freq(int* vet, unsigned char* buffer) {
    int i;
    for (i = 0; strlen(buffer) > i; i++)
        vet[(int) buffer[i]]++;
}

void codifica(Chave cod, unsigned char c, Arv* arv) {
    if (arv->dir == NULL && arv->esq == NULL) {

    }
}

void faz_chave_busca(Chave* vet_chave, int folhas, Arv* arv, int vet, int qtd_char) {
    int i, count = 0;
    for (i = 0; folhas > i; i++)
        vet_chave[i].bin = bitmapInit(8);
    for (i = 0; qtd_char > i; i++) {
        if (vet[i] != 0) {
            codifica(vet_chave[count], (unsigned char) qtd_char, arv);
            count++;
        }
    }
    ordena_por_caracter(vet_chave, folhas);
}

void compacta(Chave* vet_chave, int qtd, unsigned char* buffer) {
    int i;
    FILE* saida;
    if ((saida = fopen("colocar_o_caminho.comp", "wb")) == NULL) {
        printf("erro na abertura do arquivo de saida\n");
        exit(1);
    }
    for (i = 0; strlen(buffer) > i; i++)
        fwrite(retorna_chave(buffer[i], vet_chave, qtd), sizeof (), 1, saida);
    fclose(saida);
}

void libera_compacta(Lista* l, unsigned char* buffer, Chave* vet_chave, int qtd) {
    libera_lista(l);
    free(buffer);
    libera_bm(vet_chave, qtd);
}

void libera_bm(Chave* vet_chave, int qtd) {
    int i;
    for (i = 0; qtd > i; i++)
        free(vet_chave[i].bin.contents);
}

void ordena_por_caracter(Chave* vet_chave, int qtd) {
    int i, j;
    for (i = 0; qtd > i; i++) {
        for (j = i + 1; qtd > i; j++) {
            if (vet_chave[i].c > vet_chave[j].c) {
                unsigned char aux = vet_chave[i].c;
                vet_chave[i].c = vet_chave[j].c;
                vet_chave[j].c = aux;
            }
        }
    }
}

