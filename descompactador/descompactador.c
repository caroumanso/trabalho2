#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "descompactador.h"

char* getch_ext(FILE* arq) {
    int tam_ext;
    fread(&tam_ext, sizeof (int), 1, arq);
    char *extensao = (char*) malloc(tam_ext * sizeof (char));
    fread(extensao, sizeof (char), tam_ext, arq);
    return extensao;
}

char* concatena_saida(char* argv, char* extensao) {
    int i, k = 0;
    for (i = strlen(argv); i >= 0; i--) {
        if (argv[i] == '.')
            break;
    }
    char aux[strlen(argv) + 4];
    strcpy(aux, argv);
    for (i = i + 1; extensao[k] != '\0'; i++) {
        aux[i] = extensao[k];
        k++;
    }
    aux[i] = '\0';
    char *caminho_saida = (char*) malloc(strlen(aux) * sizeof (char));
    strcpy(caminho_saida, aux);
    free(extensao);
    return caminho_saida;
}

int retorna_freq_total(FILE* arq) {
    int total;
    fread(&total, sizeof (int), 1, arq);
    return total;
}

int insere_caracter_lista(FILE* arq, Lista* l) {
    unsigned char caracter;
    int freq;
    fread(&caracter, sizeof (unsigned char), 1, arq);
    fread(&freq, sizeof (int), 1, arq);
    Arv* nova_arv = cria_arv(freq, cria_caracter(caracter, cria_arv_vazia(), cria_arv_vazia()), cria_arv_vazia());
    Celula* nova_cel = nova_celula(nova_arv);
    lista_insere(l, nova_cel);
    return freq;
}

Lista* reconstroi_arv(FILE* entrada) {
    int count_freq = 0;
    Lista* lista = inic_lista();
    int freq_total = retorna_freq_total(entrada);
    while (freq_total != count_freq)
        count_freq += insere_caracter_lista(entrada, lista);
    ordena_lista(lista);
    ordena_lista_caracter(lista);
    faz_arv_huffman(lista);
    return lista;
}

void descompacta(Arv* arv, FILE* saida, FILE* entrada) {
    bitmap c = bitmapInit(arv_altura(arv));
    int tam_compactado, qtd_lidos = 0, i, k;
    fread(&tam_compactado, sizeof  (long int), 1, entrada);
    int qtd_bytes = (bits_totais(tam_compactado)) / 8;
    unsigned char bytes[qtd_bytes];
    fread(bytes, sizeof (unsigned char), qtd_bytes, entrada);
    fclose(entrada);
    for (k = 0; qtd_bytes > k && qtd_lidos < tam_compactado; k++) {
        for (i = 7; 0 <= i && qtd_lidos < tam_compactado; i--) {
            int bit = (bytes[k] >> i) & 0x01;
            bitmapAppendLeastSignificantBit(&c, bit);
            qtd_lidos++;
            if (seguencia_eh_caracter(c, arv, saida, 0)) {
                free(bitmapGetContents(c));
                c = bitmapInit(arv_altura(arv));
            }
        }
    }
    if (bitmapGetLength(c) > 0)
        free(bitmapGetContents(c));
    fclose(saida);
}

int bits_totais(int tam_compactado) {
    int tam_real = tam_compactado;
    while (tam_real % 8 != 0)
        tam_real++;
    return tam_real;
}

int seguencia_eh_caracter(bitmap c, Arv* arv, FILE* saida, int posicao) {
    if (posicao == bitmapGetLength(c)) {
        if (eh_no_de_folha(arv)) {
            unsigned char c = retorna_caracter(arv);
            fwrite(&c, sizeof (unsigned char), 1, saida);
            return 1;
        } else
            return 0;
    }
    if (bitmapGetBit(c, posicao) == 1)
        seguencia_eh_caracter(c, retorna_arv_dir(arv), saida, ++posicao);
    else
        seguencia_eh_caracter(c, retorna_arv_esq(arv), saida, ++posicao);
}