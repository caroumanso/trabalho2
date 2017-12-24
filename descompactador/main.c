#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "descompactador.h"
#include "lista.h"
int main(int argc, char** argv) {
    FILE* entrada;
    entrada = fopen(argv[1], "rb");
    if(entrada == NULL){
        printf("nao foi possivel abrir arquivo compactado\n");
        exit (1);
    }
    char *caminho_saida = concatena_saida(argv[1], getch_ext(entrada));
    Lista* lista = reconstroi_arv(entrada);
    FILE *saida;
    saida = fopen(caminho_saida, "wb");
    free(caminho_saida);
    if(saida == NULL){
        printf("nao foi possivel abrir o arquivo descompactado\n");
        exit (1);
    }
    descompacta(retorna_arv(lista), saida, entrada);
    libera_lista(lista);
    return (EXIT_SUCCESS);
}

