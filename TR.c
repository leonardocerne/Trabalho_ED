#include "TR.h"

void substituir_virgula_por_ponto(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
}

void copia(TABM *origem, TABM *destino, int t) {
    destino->folha = origem->folha;
    destino->nchaves = origem->nchaves;
    strcpy(destino->prox, origem->prox);
    for (int i = 0; i < origem->nchaves; i++) {
        destino->chaves[i].id = origem->chaves[i].id;
        strcpy(destino->chaves[i].bairro, origem->chaves[i].bairro);
        strcpy(destino->chaves[i].tipo, origem->chaves[i].tipo);
        strcpy(destino->chaves[i].rua, origem->chaves[i].rua);
        destino->chaves[i].numero = origem->chaves[i].numero;
        destino->chaves[i].preco_total = origem->chaves[i].preco_total;
        destino->chaves[i].preco_m2 = origem->chaves[i].preco_m2;
        strcpy(destino->chaves[i].descricao, origem->chaves[i].descricao);
        destino->chaves[i].cep = origem->chaves[i].cep;
        strcpy(destino->chaves[i].latitude, origem->chaves[i].latitude);
        strcpy(destino->chaves[i].longitude, origem->chaves[i].longitude);
    }
    for (int i = 0; i <= 2 * t; i++) {
        strcpy(destino->filhos[i], origem->filhos[i]);
    }
}

TABM *TABM_cria_no(int t){
    TABM *novo = (TABM*)malloc(sizeof(TABM));
    novo->nchaves = 0;
    novo->chaves = (TR*)malloc(sizeof(TR) * (t*2)-1);
    novo->filhos = (char**)malloc(sizeof(char**) * t * 2);
    for(int i = 0; i < 2 * t; i++){
        novo->filhos[i] = (char*)malloc(sizeof(char) * 30);
    }
    return novo;
}

TABM *arq2TABM(char *arq, int t){
    FILE *fp = fopen(arq, "rb");
    if(!fp) exit(1);
    TABM *resp = TABM_cria_no(t);
    fread(resp, sizeof(TABM), 1, fp);
    fclose(fp);
    return resp;
}

void TABM_imprime_chaves(char *raiz, int t){
    TABM *a = arq2TABM(raiz, t);
    if(!a->folha){
        TABM_imprime_chaves(a->filhos[0], t);
    }
    int c = 0;
    while(a){
        int i;
        printf("no %d:\n", c);
        for(i = 0; i < a->nchaves; i++) printf("%ld\n", a->chaves[i].id);
        printf("\n");
        a = arq2TABM(a->prox, t);
    }
    printf("\n");
}

char *TABM_busca(char *arq, long id, int t){
    TABM *a = arq2TABM(arq, t);
    int i = 0;
    while((i < a->nchaves) && (id > a->chaves[i].id)) i++;
    if((i < a->nchaves) && (a->folha) && (id == a->chaves[i].id)) return arq;
    if(a->folha) return "NULL";
    if(a->chaves[i].id == id) i++;
    return TABM_busca(a->filhos[i], id, t);
}

TABM *divisao(TABM *x, int i, TABM *y, int t, int *cont){
    TABM *z = TABM_cria_no(t);
    char *z_nome_arq = (char*)malloc(sizeof(char) * 6);
    TABM_cria(t, cont, &z_nome_arq);
    z->folha = y->folha;
    int j;
    if(!y->folha){
        z->nchaves = t-1;
        for(j = 0; j < t-1; j++) z->chaves[j] = y->chaves[j + t];
        for(j = 0; j < t; j++){
            strcpy(z->filhos[j], y->filhos[j + t]);
            strcpy(y->filhos[j+t], "NULL");
        }
    }
    else{
        z->nchaves = t;
        for(j = 0; j < t; j++) z->chaves[j] = y->chaves[j + t - 1];
        strcpy(z->prox, y->prox);
        strcpy(y->prox, z_nome_arq);
    }
    y->nchaves = t-1;
    for(j = x->nchaves; j >=i; j--) strcpy(x->filhos[j+1],x->filhos[j]);
    strcpy(x->filhos[i],z_nome_arq);
    for(j = x->nchaves; j >= i; j--) x->chaves[j] = x->chaves[j-1];
    x->chaves[i-1] = y->chaves[t-1];
    x->nchaves++;
    FILE *fp = fopen(z_nome_arq, "wb");
    TABM zcopia;
    copia(z, &zcopia, t);
    fwrite(&zcopia, sizeof(TABM), 1, fp);
    fclose(fp);
    free(z_nome_arq);
    free(z);
    return x;
}

TLSE_TR *TLSE_TR_insere(TLSE_TR *l, TR *r){
    TLSE_TR *novo = (TLSE_TR*)malloc(sizeof(TLSE_TR));
    novo->info = r;
    novo->prox = l;
    l = novo;
    return l;
}

void le_dados(char * arquivo, char ** raiz, int t, int* cont){
    FILE * fp = fopen(arquivo, "r");
    if(!fp) exit(1);
    TR *tr = (TR*)malloc(sizeof(TR));
    char tmp[70];
    char preco[20], precom2[20], id[16];
    fgets(tmp, sizeof(tmp), fp);
    printf("%s\n", tmp);
    while(fscanf(fp, "%15[^;];%30[^;];%30[^;];%50[^;];%d;%19[^;];%19[^;];%2499[^;];%d;%19[^;];%19[^\n]\n", id, tr->bairro, tr->tipo, tr->rua, &tr->numero, preco, precom2, tr->descricao, &tr->cep, tr->latitude, tr->longitude) == 11){
        substituir_virgula_por_ponto(preco);
        substituir_virgula_por_ponto(precom2);
        tr->preco_total = atof(preco);
        tr->preco_m2 = atof(precom2);
        tr->id = atol(&id[1]);
        strcpy((*raiz),TABM_insere(tr, t, raiz, cont));
    }
    fclose(fp);
    free(tr);
    return;
}

TLSE_TR *ledados(char *arq, TLSE_TR *l) {
    FILE *fp = fopen(arq, "r");
    if (!fp) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    char tmp[200];
    if (fgets(tmp, sizeof(tmp), fp) != NULL) {
        printf("Cabeçalho: %s\n", tmp); // Leitura do cabeçalho
    }
    //ID;BAIRRO;TIPO;RUA;NUMERO;PRECO;R$/m2;DESC;CEP;latitude;longitude
    while (1){
        TR *tr = (TR*)malloc(sizeof(TR));
        char preco[20], precom2[20], id[16];
        if(fscanf(fp, "%15[^;];%30[^;];%30[^;];%50[^;];%d;%19[^;];%19[^;];%2499[^;];%d;%19[^;];%19[^\n]\n", id, tr->bairro, tr->tipo, tr->rua, &tr->numero, preco, precom2, tr->descricao, &tr->cep, tr->latitude, tr->longitude) != 11) break;
        substituir_virgula_por_ponto(preco);
        substituir_virgula_por_ponto(precom2);
        tr->preco_total = atof(preco);
        tr->preco_m2 = atof(precom2);
        tr->id = atol(&id[1]);
        l = TLSE_TR_insere(l, tr);
    }
    fclose(fp);
    return l;
}

void TLSE_TR_imprime(TLSE_TR *l){
    TLSE_TR *p = l;
    while(p){
        printf("%d\n", p->info->cep);
        p = p->prox;
    }
}