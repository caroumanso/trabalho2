#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"
#include "lista.h"
#include "bitmap.h"
#include "compactador.h"
#define TAM 256
void faz_lista(int *vet, int tam, Lista* l);
void inic_vet(int *vet, int tam);
void soma_freq(int *vet, unsigned char c);

int main(int argc, char** argv) {
    int vet[TAM];
    int i;
    inic_vet(vet, TAM);
    char caminho[110];
    //strcpy(caminho, argv[1]);
    FILE* arq = fopen("entrada.txt", "rb"); //trocar por caminho
    unsigned char* buffer = le_arq(arq);
    for (i = 0; strlen(buffer) > i; i++)
        soma_freq(vet, buffer[i]);
    free(buffer);
    Lista* lista = inic_lista();
    faz_lista(vet, TAM, lista);
    ordena_lista(lista);
    faz_arv_huffman(lista);
    
    return (EXIT_SUCCESS);
}

void faz_lista(int *vet, int tam, Lista* l) {
    int i;
    for (i = 0; TAM > i; i++) {
        if (vet[i] != 0) {
            Arv* carac = cria_arv(vet[i], cria_caracter(i, cria_arv_vazia(), cria_arv_vazia()), cria_arv_vazia());
            Celula* celula = nova_celula(carac);
            lista_insere(l, celula);
        }
    }
}

void inic_vet(int* vet, int tam) {
    int i;
    for (i = 0; tam > i; i++)
        vet[i] = 0;
}

void soma_freq(int* vet, unsigned char c) {
    return vet[(int) c]++;
}

