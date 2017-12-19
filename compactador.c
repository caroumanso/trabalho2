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
    for (i = 0; strlen(buffer) > i; i++)
        vet[(int) buffer[i]]++;
}

int codifica(bitmap *cod, unsigned char c, Arv* arv) {
    if (eh_no_de_folha(arv)) {
        if (retorna_caracter(arv) == c)
            return 1;
        else
            return 0;
    }
    if (codifica(cod, c, retorna_arv_esq(arv))) {
        bitmapAppendLeastSignificantBit(cod, 0);
        return 1;
    } else if (codifica(cod, c, retorna_arv_dir(arv))) {
        bitmapAppendLeastSignificantBit(cod, 1);
        return 1;
    }
}

void faz_chave_busca(bitmap* vet_bm, Arv* arv, int *vet, int tam) {
    int i;
    for (i = 0; tam > i; i++) {
        vet_bm[i] = bitmapInit(10);
        if (vet[i] != 0) {
            codifica(&vet_bm[i], i, arv);
            inverte_bm(&vet_bm[i]);
        }
    }
}

    void compacta(bitmap* vet_bm, int qtd, unsigned char* buffer, Arv* arv, int* vet_freq) {
        int i;
        FILE* saida;
        if ((saida = fopen("colocar_o_caminho.comp", "w")) == NULL) {
            printf("erro na abertura do arquivo de saida\n");
            exit(1);
        }
        for (i = 0; 256 > i; i++){
            if(vet_freq[i] != 0){
                fprintf(saida, "%d %d ", i, vet_freq[i]);
            }

        }


        for (i = 0; strlen(buffer) > i; i++)
            escreve_bm(vet_bm[buffer[i]], saida);
        fclose(saida);
    }

    void libera_compacta(Lista* l, unsigned char* buffer, bitmap * vet_bm) {
        int i;
        for (i = 0; 256 > i; i++)
            libera_bm(vet_bm[i]);
        libera_lista(l);
        free(buffer);
    }

    void libera_bm(bitmap bm) {
        //if (bitmapGetContents(bm) != NULL)
            //free(bm.contents);
    }

    void escreve_bm(bitmap bm, FILE * saida) {
        
        fwrite(bitmapGetContents(bm), sizeof (unsigned char), bitmapGetLength(bm), saida);
    }

    void inverte_bm(bitmap *bm) {
        int i;
        bitmap aux = bitmapInit(bitmapGetMaxSize(*bm));
        aux.length = bitmapGetLength(*bm);
        aux.contents = bitmapGetContents(*bm);
        for(i = 0; bitmapGetLength(*bm)>i;i++)
            bitmapSetBit(bm, i, bitmapGetBit(aux, bitmapGetLength(aux)-1-i));
        libera_bm(aux);
    }