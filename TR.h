#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_T 50

typedef struct tiporesidencia{
    long int id;
    char bairro[30];
    char tipo[30];
    char rua[50];
    int numero;
    double preco_total;
    double preco_m2;
    char descricao[2500];
    int cep;
    char latitude[20];
    char longitude[20];
}TR;

typedef struct listatr{
    TR *info;
    struct listatr *prox;
}TLSE_TR;

typedef struct arvbm{
    int folha;
    int nchaves;
    char prox[30];
    TR *chaves;
    char **filhos;
}TABM;
