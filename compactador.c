#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compactador.h"

struct chave{
    unsigned char c;
    bitmap bin;
};


int tam_arq(FILE* file){
    fseek(file,0,SEEK_END);
    int tam = ftell(file);
    rewind(file);
    return tam;
}

unsigned char* le_arq(FILE* file){
    char* buffer = (char*)malloc((tam_arq(file))*sizeof(char));
    fread(buffer, sizeof(char), tam_arq(file), file);
    fclose(file);
    return buffer;
}

void soma_freq(int* vet, unsigned char* buffer) {
    int i;
    for (i = 0; strlen(buffer) > i; i++)
        vet[(int)buffer[i]]++;
}

void init_chave_busca(Chave* vet_chave, int qtd){
    int i;
    for(i = 0; qtd>i; i++)
        vet_chave[i].bin = bitmapInit(8);
    /* ai a partir de agr colocaria cada folha(caracter) no vetor 
     * e seu respectivo caminho no bit map
     esse vetor funcionaria como uma chave de busca
     ai dps e so ler o buffer dnv e fazer o arquivo de saida*/
}