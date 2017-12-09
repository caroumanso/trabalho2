#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compactador.h"
#include "bitmap.h"
#include "lista.h"

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

void codifica(bitmap *cod, unsigned char c, Arv* arv) {
}

void faz_chave_busca(bitmap* vet_bm, Arv* arv, int *vet, int tam) {
    int i;
    for (i = 0; tam > i; i++) {
        vet_bm[i] = bitmapInit(8);
        if (vet[i] != 0)
            codifica(&vet_bm[i], (unsigned char) i, arv);
    }
}

void compacta(bitmap* vet_bm, int qtd, unsigned char* buffer) {
    int i;
    FILE* saida;
    if ((saida = fopen("colocar_o_caminho.comp", "wb")) == NULL) {
        printf("erro na abertura do arquivo de saida\n");
        exit(1);
    }
    for (i = 0; strlen(buffer) > i; i++)
        fwrite(bitmapGetContents(vet_bm[buffer[i]]), sizeof (unsigned char), bitmapGetLength(vet_bm[buffer[i]]), saida);
    fclose(saida);
}

void libera_compacta(Lista* l, unsigned char* buffer, bitmap *vet_bm) {
    int i;
    for (i = 0; strlen(buffer) > i; i++)
        free(vet_bm[i].contents);
    libera_lista(l);
    free(buffer);
}