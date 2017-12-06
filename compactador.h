#ifndef COMPACTADOR_H
#define COMPACTADOR_H

typedef struct chave Chave;
int tam_arq(FILE* file);
unsigned char* le_arq(FILE* file);
void soma_freq(int *vet, unsigned char* buffer);

#endif /* COMPACTADOR_H */

