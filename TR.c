#include "TR.h"

void substituir_virgula_por_ponto(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
}

void TABMtoTABM(TABM *origem, TABM *destino, int t) {
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
    if(!fp) return NULL;
    TABM *resp = TABM_cria_no(t);
    fread(resp, sizeof(TABM), 1, fp);
    fclose(fp);
    return resp;
}

TR TRtoTR(TR aux, TR T) {
    aux.id = T.id;
    strcpy(aux.bairro, T.bairro);
    strcpy(aux.tipo, T.tipo);
    strcpy(aux.rua, T.rua);
    aux.numero = T.numero;
    aux.preco_total = T.preco_total;
    aux.preco_m2 = T.preco_m2;
    strcpy(aux.descricao, T.descricao);
    aux.cep = T.cep;
    strcpy(aux.latitude, T.latitude);
    strcpy(aux.longitude, T.longitude);
    return aux;
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
        c++;
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

void copia_no(TABM *x, char *arq, int t){
    FILE *fp = fopen(arq, "wb");
    if(!fp) exit(1);
    TABM aux;
    TABMtoTABM(x, &aux, t);
    fwrite(&aux, sizeof(TABM), 1, fp);
    fclose(fp);
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
    copia_no(x, z_nome_arq, t);
    free(z_nome_arq);
    free(z);
    return x;
}

void TABM_escreve(char* arquivo, TABM* no, int t) {
    FILE* fp = fopen(arquivo, "wb");
    if (!fp) exit(1); // Saia do programa em caso de erro na abertura
    fwrite(no, sizeof(TABM), 1, fp);
    fclose(fp);
}

TABM *insere_nao_completo(TABM *x, TR *r, int t, int *cont){
    int i = x->nchaves-1;
    if(x->folha){
        while((i>=0) && (r->id < x->chaves[i].id)){
            x->chaves[i+1] = x->chaves[i];
            i--;
        }
        x->chaves[i+1] = *r;
        x->nchaves++;
        return x;
    }
    while((i>=0) && (r->id < x->chaves[i].id)) i--;
    i++;
    TABM *z = arq2TABM(x->filhos[i], t);
    if(z->nchaves == ((2*t)-1)){
        x = divisao(x, (i+1), z, t, cont);
        if(r->id > x->chaves[i].id) i++;
        copia_no(z, x->filhos[i], t);
    }
    z = arq2TABM(x->filhos[i], t);
    z = insere_nao_completo(z, r, t, cont);
    copia_no(z, x->filhos[i], t);
    free(z);
    return x;
}


char* TABM_insere(TR *residencia, int t, char **raiz, int *cont) {
    if (!*raiz || !arq2TABM(*raiz, t)) {
        TABM_cria(t, cont, raiz);
        TABM *T = TABM_cria_no(t);
        T->chaves[0] = *residencia;
        T->nchaves = 1;
        TABM aux;
        TABMtoTABM(T, &aux, t);
        TABM_escreve(*raiz, &aux, t);
        TABM_libera_no(T);
        return *raiz;
    }

    char ver[20];
    strcpy(ver, TABM_busca(*raiz, residencia->id, t));
    if (strcmp(ver, "NULL") != 0) {
        TABM *a = arq2TABM(ver, t);
        int i;
        for (i = 0; a->chaves[i].id != residencia->id; i++);
        a->chaves[i] = TRtoTR(a->chaves[i], *residencia);
        TABM aux;
        TABMtoTABM(a, &aux, t);
        TABM_escreve(ver, &aux, t);
        TABM_libera_no(a);
        return *raiz;
    }
    TABM *T = arq2TABM(*raiz, t);

    if (T->nchaves == (2 * t) - 1) {
        char *S_arq = (char *)malloc(sizeof(char) * 30);
        TABM_cria(t, cont, &S_arq);
        TABM *S = arq2TABM(S_arq, t);
        S->nchaves = 0;
        S->folha = 0;
        strcpy(S->filhos[0], *raiz);
        S = divisao(S, 1, T, t, cont);
        TABM aux_3;
        TABMtoTABM(T, &aux_3, t);
        TABM_escreve(*raiz, &aux_3, t);
        S = insere_nao_completo(S, residencia, t, cont);
        TABM aux;
        TABMtoTABM(S, &aux, t);
        TABM_escreve(S_arq, &aux, t);

        TABM_libera_no(T);
        TABM_libera_no(S);
        strcpy(*raiz, S_arq);
        free(S_arq);
        return *raiz;
    }
    T = insere_nao_completo(T, residencia, t, cont);
    TABM aux;
    TABMtoTABM(T, &aux, t);
    TABM_escreve(*raiz, &aux, t);
    TABM_libera_no(T);
    return *raiz;
}

TLSE_TR *TLSE_TR_insere(TLSE_TR *l, TR *r){
    TLSE_TR *novo = (TLSE_TR*)malloc(sizeof(TLSE_TR));
    novo->info = r;
    novo->prox = l;
    l = novo;
    return l;
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

char *remocao(char *no, long id, int t){
    TABM *a = arq2TABM(no, t);
    char busca[20];
    strcpy(busca, TABM_busca(no, id, t));
    if((!a) || (strcmp(busca, "NULL") == 0)) return no; // Verificacao precisa acontecer em toda chamada
    int i;
    for(i = 0; i < a->nchaves && a->chaves[i].id < id; i++);
    if((i < a->nchaves) && (id == a->chaves[i].id) && (a->folha)){
        printf("\nCASO 1\n");
        int j;
        for(j=i; j<a->nchaves - 1; j++) a->chaves[j] = a->chaves[j+1];
        a->nchaves--;
        if(!a->nchaves) {
            free(a);
            remove(no);
        }
        else{
            TABM_escreve(no, a, t);
        }
        return no;
    }
    if((i < a->nchaves) && (id == a->chaves[i].id)) i++;
    TABM y = *arq2TABM(a->filhos[i], t), z, tmp;
    z.nchaves = 0; // verificacao para z n existe
    if(y.nchaves == t-1){ // CASOS 3A e 3B
        if(i < a->nchaves){
            tmp = *arq2TABM(a->filhos[i+1], t);
            if((i < a->nchaves) && (tmp.nchaves >= t)){ // CASO 3A dir
                printf("\nCASO 3A: i menor que nchaves\n");
                copia(&tmp, &z, t);
                if(!y.folha){
                    y.chaves[t-1] = TRtoTR(y.chaves[t-1], a->chaves[i]);
                    a->chaves[i] = TRtoTR(a->chaves[i], z.chaves[0]);
                }
                else{
                    a->chaves[i].id = z.chaves[0].id + 1;
                    y.chaves[t-1] = TRtoTR(y.chaves[t-1], z.chaves[0]);
                }
                y.nchaves++;
                int j;
                for(j=0; j < z.nchaves - 1; j++) 
                    z.chaves[j] = TRtoTR(z.chaves[j], z.chaves[j+1]);
                strcpy(y.filhos[y.nchaves], z.filhos[0]);
                for(j=0; j < z.nchaves; j++)
                    strcpy(z.filhos[j], z.filhos[j+1]);
                z.nchaves--;
                TABM_escreve(no, a, t);
                TABM_escreve(a->filhos[i], &y, t);
                TABM_escreve(a->filhos[i+1], &z, t);
                strcpy(a->filhos[i], remocao(a->filhos[i], id, t));
                FILE *fpaux = fopen(a->filhos[i], "rb");
                if(!fpaux){
                    strcpy(a->filhos[i], "NULL");
                    TABM_escreve(no, a, t);
                }
                else fclose(fpaux);
                return a;
            }
        }
        if(i > 0){
            tmp = *arq2TABM(a->filhos[i-1], t);
            if((i > 0) && (z.nchaves == 0) && (tmp.nchaves >=t)){ //CASO 3A esq
                printf("\nCASO 3A: i igual a nchaves\n");
                TABMtoTABM(&tmp, &z, t);
                int j; 
                for(j = y.nchaves; j>0; j--)
                    y.chaves[j] = TRtoTR(y.chaves[j], y.chaves[j-1]);
                for(j = y.nchaves+1; j>0; j--)
                    strcpy(y.filhos[j], y.filhos[j-1]);
                if(!y.folha){
                    y.chaves[0] = TRtoTR(y.chaves[0], a->chaves[i-1]);
                    a->chaves[i-1] = TRtoTR(a->chaves[i-1], z.chaves[z.nchaves - 1]);
                }
                else{
                    a->chaves[i-1] = TRtoTR(a->chaves[i-1], z.chaves[z.nchaves - 1]);
                    y.chaves[0] = TRtoTR(y.chaves[0], z.chaves[z.nchaves-1]);
                }
                y.nchaves++;
                strcpy(y.filhos[0], z.filhos[z.nchaves]);
                z.nchaves--;
                TABM_escreve(no, a, t);
                TABM_escreve(a->filhos[i], &y, t);
                TABM_escreve(a->filhos[i-1], &z, t);
                strcpy(a->filhos[i], remocao(a->filhos[i], id, t));
                FILE *fpaux = fopen(a->filhos[i], "rb");
                if(!fpaux){
                    strcpy(a->filhos[i], "NULL");
                    TABM_escreve(no, a, t);
                }
                else fclose(fpaux);
            }
        }
        if(z.nchaves == 0){ //CASO 3B

        }
    }
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