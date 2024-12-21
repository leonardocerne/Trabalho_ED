#include "TR.h"

TLSE_TR *TLSE_TR_insere(TLSE_TR *l, TR *tr){
    TLSE_TR *novo = (TLSE_TR*)malloc(sizeof(TLSE_TR));
    novo->info = tr;
    novo->prox = l;
    l = novo;
    return l;
}

void imprime_id(TLSE_TR *l){
    if(!l) return;
    TLSE_TR *p = l;
    while(p){
        printf("bairro:%s, id=%ld\n", p->info->bairro, p->info->id);
        p = p->prox;
    }
}