#include <stdio.h>
#include <stdlib.h>
#include "compactador.h"

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

