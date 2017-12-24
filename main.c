#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "lista.h"
#include "compactador.h"
#define TAM 256
void inic_vet(int *vet, int tam);

int main(int argc, char** argv) {
    int vet[TAM];
    inic_vet(vet, TAM);
    unsigned char* buffer = le_arq(argv[1]);
    soma_freq(vet, buffer);
    Lista* lista = inic_lista();
    faz_lista(vet, TAM, lista);
    ordena_lista(lista);
    ordena_lista_caracter(lista);
    faz_arv_huffman(lista);
    compacta(TAM, buffer, retorna_arv(lista), vet, argv[1]);
    libera_lista(lista);
    return (EXIT_SUCCESS);
}

void inic_vet(int* vet, int tam) {
    int i;
    for (i = 0; tam > i; i++)
        vet[i] = 0;
}