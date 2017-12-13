#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compactador.h"
#include "bitmap.h"
#include "lista.h"
#include "arvore.h"

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
    for (i = 0; strlen(buffer) - 1 > i; i++)
        vet[(int) buffer[i]]++;
}

void codifica(bitmap cod, unsigned char c, Arv* arv) {
    if(eh_no_de_folha(arv) && retorna_caracter(arv) == c)
        return;
    else if(!arv_vazia(arv)){
        bitmapAppendLeastSignificantBit(&cod, 0);
        codifica(cod, c, retorna_arv_esq(arv));
        bitmapSetBit(&cod, (bitmapGetLength(cod) - 1),1);
        codifica(cod, c, retorna_arv_dir(arv));
    }
}

void faz_chave_busca(bitmap* vet_bm, Arv* arv, int *vet, int tam) {
    int i;
    for (i = 0; tam > i; i++) {
        vet_bm[i] = bitmapInit(8);
        if (vet[i] != 0)
            codifica(vet_bm[i], (unsigned char) i, arv);
    }
}

void compacta(bitmap* vet_bm, int qtd, unsigned char* buffer, Arv* arv) {
    int i;
    FILE* saida;
    if ((saida = fopen("colocar_o_caminho.txt", "w")) == NULL) {
        printf("erro na abertura do arquivo de saida\n");
        exit(1);
    }
    bitmap bm_arv = bitmapInit(2048);
    faz_caminho_arv(arv, saida, bm_arv);
    escreve_bm(bm_arv, saida);
    libera_bm(bm_arv);
    for (i = 0; strlen(buffer) - 1 > i; i++)
        escreve_bm(vet_bm[buffer[i]], saida);
    fclose(saida);
}

void libera_compacta(Lista* l, unsigned char* buffer, bitmap *vet_bm) {
    int i;
    for (i = 0; 256 > i; i++)
        libera_bm(vet_bm[i]);
    libera_lista(l);
    free(buffer);
}

void libera_bm(bitmap bm) {
    if (bitmapGetContents(bm) != NULL)
        free(bitmapGetContents(bm));
}

void escreve_bm(bitmap bm, FILE* saida) {
    if (bitmapGetLength(bm) != 0)
        fwrite(bitmapGetContents(bm), sizeof (unsigned char), bitmapGetLength(bm), saida);
}