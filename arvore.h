#ifndef ARVORE_H
#define ARVORE_H
typedef struct arvore Arv;

Arv* cria_arv(int num, Arv* dir, Arv* esq);
Arv* cria_caracter(unsigned char c, Arv* dir, Arv* esq);
Arv* cria_arv_vazia();
int arv_vazia(Arv* a);
void libera_arv(Arv* a);
int arv_freq(Arv* a);
int qtd_folhas(Arv* arv);
int eh_folha(Arv* arv);
Arv* retorna_ramoEsq(Arv* arv);
Arv* retorna_ramoDir(Arv* arv);

#endif /* ARVORE_H */
