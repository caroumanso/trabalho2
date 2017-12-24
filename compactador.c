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

unsigned char* le_arq(char* argv) {
    FILE* arq;
    arq = fopen(argv, "rb");
    if (arq == NULL) {
        printf("erro na abertura do arquivo de entrada\n");
        exit(1);
    }
    unsigned char* buffer = (unsigned char*) malloc((tam_arq(arq)) * sizeof (unsigned char));
    fread(buffer, sizeof (unsigned char), tam_arq(arq), arq);
    fclose(arq);
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
    int i, tam_bitmap = arv_altura(arv);
    for (i = 0; tam > i; i++) {
        vet_bm[i] = bitmapInit(tam_bitmap);
        if (vet[i] != 0) {
            codifica(&vet_bm[i], i, arv);
            vet_bm[i] = inverte_bm(&vet_bm[i]);
        }
    }
}

void compacta(int qtd, unsigned char* buffer, Arv* arv, int* vet_freq, char* argv) {
    bitmap vet_bm[qtd];
    faz_chave_busca(vet_bm, arv, vet_freq, qtd);
    FILE* saida;
    char arq_saida[100];
    concatena_saida(arq_saida, argv);
    saida = fopen(arq_saida, "wb");
    if (saida == NULL) {
        printf("erro na abertura do arquivo de saida\n");
        exit(1);
    }
    char ext[10];
    extensao(ext, argv);
    int tam_extensao = strlen(ext);
    fwrite(&tam_extensao, sizeof (int), 1, saida);
    fwrite(ext, sizeof (char), tam_extensao, saida);
    int freq_total = arv_freq(arv);
    fwrite(&freq_total, sizeof (int), 1, saida);
    imprime_caracter_freq(arv, saida);
    escreve_tam_arq_compactado(vet_bm, buffer, saida);
    escreve_compacta(vet_bm, buffer, saida);
    libera_compacta(buffer, vet_bm);
    fclose(saida);
}

void libera_compacta(unsigned char* buffer, bitmap * vet_bm) {
    int i;
    for (i = 0; 256 > i; i++)
        free(bitmapGetContents(vet_bm[i]));
    free(buffer);
}

void escreve_bm(bitmap bm, FILE * saida) {
    if (bitmapGetLength(bm) % 8 == 0)
        fwrite(bitmapGetContents(bm), sizeof (unsigned char), bitmapGetLength(bm) / 8, saida);
    else
        fwrite(bitmapGetContents(bm), sizeof (unsigned char), (bitmapGetLength(bm) / 8) + 1, saida);
}

bitmap inverte_bm(bitmap * bm) {
    int i;
    bitmap aux = bitmapInit(bitmapGetMaxSize(*bm));
    for (i = 0; bitmapGetLength(*bm) > i; i++) {
        bitmapAppendLeastSignificantBit(&aux, bitmapGetBit(*bm, bitmapGetLength(*bm) - 1 - i));
    }
    free(bitmapGetContents(*bm));
    return aux;
}

void escreve_compacta(bitmap *vet_bm, unsigned char* buffer, FILE* saida) {
    int i, k;
    bitmap vet_saida = bitmapInit(12 * 1024 * 1024);
    for (i = 0; strlen(buffer) > i; i++) {
        for (k = 0; bitmapGetLength(vet_bm[buffer[i]]) > k; k++) {
            if (bitmapGetMaxSize(vet_saida) == bitmapGetLength(vet_saida)) {
                escreve_bm(vet_saida, saida);
                free(bitmapGetContents(vet_saida));
                vet_saida = bitmapInit(5 * 1024 * 1024);
            }
            bitmapAppendLeastSignificantBit(&vet_saida, bitmapGetBit(vet_bm[buffer[i]], k));
        }
    }
    if (bitmapGetLength(vet_saida) > 0) {
        escreve_bm(vet_saida, saida);
        free(bitmapGetContents(vet_saida));
    }
}

void concatena_saida(char* destino, char* argv) {
    int i;
    for (i = strlen(argv); i >= 0; i--) {
        if (argv[i] == '.')
            break;
    }
    char aux[100];
    strcpy(aux, argv);
    aux[i + 1] = '\0';
    sprintf(destino, "%s%s", aux, "comp");
}

void escreve_tam_arq_compactado(bitmap *vet_bm, unsigned char* buffer, FILE* saida) {
    int i, k;
    long int tam = 0;
    for (i = 0; strlen(buffer) > i; i++) {
        for (k = 0; bitmapGetLength(vet_bm[buffer[i]]) > k; k++)
            tam++;
    }
    fwrite(&tam, sizeof (long int), 1, saida);
}

void extensao(char* ext, char* origem) {
    int i, k;
    for (i = strlen(origem); i >= 0; i--) {
        if (origem[i] == '.')
            break;
    }
    i++;
    for (k = 0; origem[i] != '\0'; k++) {
        ext[k] = origem[i];
        i++;
    }
    ext[k + 1] = '\0';
}

void imprime_caracter_freq(Arv* arv, FILE* saida) {
    if(eh_no_de_folha(arv)){
        unsigned char c = retorna_caracter(arv);
        fwrite(&c, sizeof(unsigned char), 1, saida);
        int freq = arv_freq(arv);
        fwrite(&freq, sizeof(int), 1, saida);
    }
    else if(!arv_vazia(arv)){
        imprime_caracter_freq(retorna_arv_esq(arv), saida);
        imprime_caracter_freq(retorna_arv_dir(arv), saida);
    }
}