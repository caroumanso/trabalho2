#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "lista.h"
#include "bitmap.h"
#include "compactador.h"
#define TAM 256
void inic_vet(int *vet, int tam);

int main(int argc, char** argv) {
    int vet[TAM];
    inic_vet(vet, TAM);
    char caminho[110];
    strcpy(caminho, argv[1]);
    FILE* arq;
    if ((arq = fopen(caminho, "rb")) == NULL) {
        printf("erro na abertura do arquivo de entrada\n");
        exit(1);
    }
    unsigned char* buffer = le_arq(arq);
    soma_freq(vet, buffer);
    Lista* lista = inic_lista();
    faz_lista(vet, TAM, lista);
    ordena_lista(lista);
    faz_arv_huffman(lista);
    int folhas = qtd_folhas(lista->ini->arvore);
    Chave vet_chave[folhas];
    faz_chave_busca(vet_chave, folhas, lista->ini->arvore, vet, TAM);
    compacta(vet_chave, folhas, buffer);
    libera_compacta(lista, buffer, vet_chave, folhas);
    return (EXIT_SUCCESS);
}

void inic_vet(int* vet, int tam) {
    int i;
    for (i = 0; tam > i; i++)
        vet[i] = 0;
}