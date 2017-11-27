#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "lista.h"
#define TAM 256
void faz_lista(int *vet, int tam, Lista* l);
void inic_vet(int *vet, int tam);
void soma_freq(int *vet, unsigned char c);

int main(int argc, char** argv) {
    int vet[TAM];
    inic_vet(vet, TAM);
    unsigned char c;
    FILE* arquivo = fopen("entrada.txt", "r");
    while (fscanf(arquivo, "%c", &c) == 1)
        soma_freq(vet, c);
    Lista* lista = inic_lista();
    faz_lista(vet, TAM, lista);
    ordena_lista(lista);
    return (EXIT_SUCCESS);
}

void faz_lista(int *vet, int tam, Lista* l) {
    int i;
    for (i = 0; TAM > i; i++ ) {
        if (vet[i] != 0) {
            Arv* carac = cria_caracter(i, cria_arv(vet[i], cria_arvvazia(), cria_arvvazia()), cria_arvvazia());
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