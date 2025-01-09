#include "TR.c"
// Retorna todas as residências de mesmo CEP
void retornaCEP(int cep, int t, char *arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (x->chaves[i].cep == cep) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

// Retorna todas residências de mesma latitude
void retornaLAT(char *latitude, int t, char *arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strcmp(x->chaves[i].latitude, latitude)==0) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

// Retorna todas residências de mesma longitude
void retornaLO(char *longitude, int t, char *arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strcmp(x->chaves[i].longitude, longitude)==0) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

// Retorna todas residências situadas no mesmo bairro
void retornaBAIRRO(char *bairro, int t, char *arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strcmp(x->chaves[i].bairro, bairro)==0) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

// Retorna todas residências de mesmo tipo
void retornaTIPO(int tipo, int t, char **arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(*arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    char aux[30];
    if (tipo == 1) strcpy(aux,"APARTMENT");
    else if (tipo == 2) strcpy(aux,"HOME");
    else if (tipo == 3) strcpy(aux,"RESIDENTIAL_ALLOTMENT_LAND");
    else if (tipo == 4) strcpy(aux,"COMMERCIAL_PROPERTY");
    else if (tipo == 5) strcpy(aux,"OFFICE");
    else if (tipo == 6) strcpy(aux,"COMMERCIAL_BUILDING");
    else if (tipo == 7) strcpy(aux,"CONDOMINIUM");
    else if (tipo == 8) strcpy(aux,"BUSINESS");
    else if (tipo == 9) strcpy(aux,"PENTHOUSE");
    else if (tipo == 10) strcpy(aux,"VILLAGE_HOUSE");
    else if (tipo == 11) strcpy(aux,"SHED_DEPOSIT_WAREHOUSE");
    else if (tipo == 12) strcpy(aux,"ALLOTMENT_LAND");
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strcmp(x->chaves[i].tipo, aux)==0) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

// Retorna todas residências com mesma quantidade de metros quadrados
void retornaM2(int m2, int t, char *arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if ((x->chaves[i].preco_total / x->chaves[i].preco_m2) == m2) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

// Retorna todas residências na mesma rua
void retornaRUA(char rua, int t, char *arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strcmp(x->chaves[i].rua, &rua)==0) resp = TLSE_TR_insere(resp,&x->chaves[i]);
        }
        x =  arq2TABM(x->prox,t);
    }
    TLSE_TR_imprime(resp);
}

// Remove todos imoveis dentro de uma faixa de preço
void removeImoveisPorPreco(double precoMin, double precoMax, int t, char *arq) {
    TABM *x = arq2TABM(arq, t);
    TLSE_TR *listaRemocoes = NULL; // lista pra armazenar os imoveis que serao removidos

    // vai ate o cara mais a esquerda
    while (!x->folha) {
        x = arq2TABM(x->filhos[0], t);
    }

    while (x) {
        for (int i = 0; i < x->nchaves; i++) {
            // ve se o preco ta na faixa
            if (x->chaves[i].preco_total >= precoMin && x->chaves[i].preco_total <= precoMax) {
                printf("Marcando para remoção: imóvel ID: %ld, Preço Total: %.2f\n", x->chaves[i].id, x->chaves[i].preco_total);

                // bota o imovel na lista de remoções
                listaRemocoes = TLSE_TR_insere(listaRemocoes, &x->chaves[i]);
            }
        }
        x = arq2TABM(x->prox, t);
    }

    // percorre a lista de remocoes removendo os imoveis
    TLSE_TR *p = listaRemocoes;
    char tmp[20];
    while (p) {
        printf("Removendo imóvel ID: %ld\n", p->info->id);
        strcpy(tmp, TABM_busca(arq, p->info->id, t));
        strcpy(arq, remocao(arq, p->info->id, t));
        remove(tmp);
        p = p->prox;
    }

    TLSE_TR_libera(listaRemocoes);

}


// Alterando preço total de uma residencia
void alteraPrecoTotal(long int id, double novoPrecoTotal, int t, char *arq) {
    char resp[20];
    int i;
    strcpy(resp, TABM_busca(arq, id, t));
    if(strcmp(resp, "NULL") == 0){
        printf("ID %ld nao encontrado\n", id);
        return;
    }
    TABM *x = arq2TABM(resp, t);
    for(i = 0; (i < x->nchaves) && (x->chaves[i].id != id); i++);
    x->chaves[i].preco_total = novoPrecoTotal;
    TABM_escreve(resp, x, t);
    printf("\nPreco alterado com sucesso\n");
    return;
}


// Alterando preço por m2
void alteraPrecoPorM2(long int id, double novoPrecoM2, int t, char *arq) {
    char resp[20];
    int i;
    strcpy(resp, TABM_busca(arq, id, t));
    if (strcmp(resp, "NULL") == 0) {
        printf("ID %ld nao encontrado\n", id);
        return;
    }
    TABM *x = arq2TABM(resp, t);
    for (i = 0; (i < x->nchaves) && (x->chaves[i].id != id); i++);
    x->chaves[i].preco_m2 = novoPrecoM2;
    TABM_escreve(resp, x, t);
    return;
}

// Alterando descrições
void alteraDescricao(long int id, char *novaDescricao, int t, char *arq) {
    char resp[20];
    int i;
    strcpy(resp, TABM_busca(arq, id, t));
    if (strcmp(resp, "NULL") == 0) {
        printf("ID %ld nao encontrado\n", id);
        return;
    }
    TABM *x = arq2TABM(resp, t);
    for (i = 0; (i < x->nchaves) && (x->chaves[i].id != id); i++);
    strcpy(x->chaves[i].descricao, novaDescricao);
    TABM_escreve(resp, x, t);
    return;
}


void retiraPorTipo(char *tipo, int t, char *arq) {
    TABM *x = arq2TABM(arq, t);
    TLSE_TR *listaRemocoes = NULL;

    while (!x->folha) {
        x = arq2TABM(x->filhos[0], t);
    }

    while (x) {
        for (int i = 0; i < x->nchaves; i++) {
            if (strcmp(x->chaves[i].tipo, tipo) == 0) {
                printf("Marcando para remoção: imóvel ID: %ld, Tipo: %s\n", x->chaves[i].id, x->chaves[i].tipo);
                listaRemocoes = TLSE_TR_insere(listaRemocoes, &x->chaves[i]);
            }
        }
        x = arq2TABM(x->prox, t);
    }
    char tmp[20];
    TLSE_TR *p = listaRemocoes;
    while (p) {
        printf("Removendo imóvel ID: %ld\n", p->info->id);
        strcpy(tmp, TABM_busca(arq, p->info->id, t));
        strcpy(arq, remocao(arq, p->info->id, t));
        remove(tmp);
        p = p->prox;
    }

    TLSE_TR_libera(listaRemocoes);
    printf("Remoção concluída para imóveis do tipo %s.\n", tipo);
}


void retiraPorCEP(int cep, int t, char *arq) {
    TABM *x = arq2TABM(arq, t);
    TLSE_TR *listaRemocoes = NULL;

    while (!x->folha) {
        x = arq2TABM(x->filhos[0], t);
    }

    while (x) {
        for (int i = 0; i < x->nchaves; i++) {
            if (x->chaves[i].cep == cep) {
                printf("Marcando para remoção: imóvel ID: %ld, CEP: %d\n", x->chaves[i].id, x->chaves[i].cep);
                listaRemocoes = TLSE_TR_insere(listaRemocoes, &x->chaves[i]);
            }
        }
        x = arq2TABM(x->prox, t);
    }

    TLSE_TR *p = listaRemocoes;
    char tmp[20];
    while (p) {
        printf("Removendo imóvel ID: %ld\n", p->info->id);
        strcpy(tmp, TABM_busca(arq, p->info->id, t));
        strcpy(arq, remocao(arq, p->info->id, t));
        remove(tmp);
        p = p->prox;
    }

    TLSE_libera(listaRemocoes);
    printf("Remoção concluída para imóveis com CEP %d.\n", cep);
}


void retiraPorRua(char *rua, int t, char *arq) {
    TABM *x = arq2TABM(arq, t);
    TLSE_TR *listaRemocoes = NULL;

    while (!x->folha) {
        x = arq2TABM(x->filhos[0], t);
    }

    while (x) {
        for (int i = 0; i < x->nchaves; i++) {
            if (strcmp(x->chaves[i].rua, rua) == 0) {
                printf("Marcando para remoção: imóvel ID: %ld, Rua: %s\n", x->chaves[i].id, x->chaves[i].rua);
                listaRemocoes = TLSE_TR_insere(listaRemocoes, &x->chaves[i]);
            }
        }
        x = arq2TABM(x->prox, t);
    }

    TLSE_TR *p = listaRemocoes;
    char tmp[20];
    while (p) {
        printf("Removendo imóvel ID: %ld\n", p->info->id);
        strcpy(tmp, TABM_busca(arq, p->info->id, t));
        strcpy(arq, remocao(arq, p->info->id, t));
        remove(tmp);
        p = p->prox;
    }

    TLSE_TR_libera(listaRemocoes);
    printf("Remoção concluída para imóveis na rua %s.\n", rua);
}


void retiraPorLatitude(char *latitude, int t, char *arq) {
    TABM *x = arq2TABM(arq, t);
    TLSE_TR *listaRemocoes = NULL;

    while (!x->folha) {
        x = arq2TABM(x->filhos[0], t);
    }

    while (x) {
        for (int i = 0; i < x->nchaves; i++) {
            if (strcmp(x->chaves[i].latitude, latitude) == 0) {
                printf("Marcando para remoção: imóvel ID: %ld, Latitude: %s\n", x->chaves[i].id, x->chaves[i].latitude);
                listaRemocoes = TLSE_TR_insere(listaRemocoes, &x->chaves[i]);
            }
        }
        x = arq2TABM(x->prox, t);
    }

    TLSE_TR *p = listaRemocoes;
    char tmp[20];
    while (p) {
        printf("Removendo imóvel ID: %ld\n", p->info->id);
        strcpy(tmp, TABM_busca(arq, p->info->id, t));
        strcpy(arq, remocao(arq, p->info->id, t));
        remove(tmp);
        p = p->prox;
    }

    TLSE_TR_libera(listaRemocoes);
    printf("Remoção concluída para imóveis com latitude %s.\n", latitude);
}


void retiraPorLongitude(char *longitude, int t, char *arq) {
    TABM *x = arq2TABM(arq, t);
    TLSE_TR *listaRemocoes = NULL;

    while (!x->folha) {
        x = arq2TABM(x->filhos[0], t);
    }

    while (x) {
        for (int i = 0; i < x->nchaves; i++) {
            if (strcmp(x->chaves[i].longitude, longitude) == 0) {
                printf("Marcando para remoção: imóvel ID: %ld, Longitude: %s\n", x->chaves[i].id, x->chaves[i].longitude);
                listaRemocoes = TLSE_TR_insere(listaRemocoes, &x->chaves[i]);
            }
        }
        x = arq2TABM(x->prox, t);
    }

    TLSE_TR *p = listaRemocoes;
    char tmp[20];
    while (p) {
        printf("Removendo imóvel ID: %ld\n", p->info->id);
        strcpy(tmp, TABM_busca(arq, p->info->id, t));
        strcpy(arq, remocao(arq, p->info->id, t));
        remove(tmp);
        p = p->prox;
    }

    TLSE_TR_libera(listaRemocoes);
    printf("Remoção concluída para imóveis com longitude %s.\n", longitude);
}


void retiraPorBairro(char *bairro, int t, char *arq) {
    TABM *x = arq2TABM(arq, t);
    TLSE_TR *listaRemocoes = NULL;

    while (!x->folha) {
        x = arq2TABM(x->filhos[0], t);
    }

    while (x) {
        for (int i = 0; i < x->nchaves; i++) {
            if (strcmp(x->chaves[i].bairro, bairro) == 0) {
                printf("Marcando para remoção: imóvel ID: %ld, Bairro: %s\n", x->chaves[i].id, x->chaves[i].bairro);
                listaRemocoes = TLSE_TR_insere(listaRemocoes, &x->chaves[i]);
            }
        }
        x = arq2TABM(x->prox, t);
    }

    TLSE_TR *p = listaRemocoes;
    char tmp[20];
    while (p) {
        printf("Removendo imóvel ID: %ld\n", p->info->id);
        strcpy(tmp, TABM_busca(arq, p->info->id, t));
        strcpy(arq, remocao(arq, p->info->id, t));
        remove(tmp);
        p = p->prox;
    }

    TLSE_TR_libera(listaRemocoes);
    printf("Remoção concluída para imóveis no bairro %s.\n", bairro);
}


void procuraqto (long int id,int t,char *arq){
    char *aux = TABM_busca(arq,id,t), *resp = NULL;
    TABM *x = arq2TABM(aux,t);
    int i;
    for (i=0;i<x->nchaves;i++) if (x->chaves[i].id == id) break;
    TR aux2 = x->chaves[i];
    if (strstr(aux2.descricao,"quarto")){
         resp = strstr(aux2.descricao,"quarto");
    }
    else if (strstr(aux2.descricao,"Quarto")){
        resp = strstr(aux2.descricao,"Quarto");
    }
    else if (strstr(aux2.descricao,"QUARTO")){
        resp = strstr(aux2.descricao,"QUARTO");
    }
    else if (strstr(aux2.descricao,"quartos")){
        resp = strstr(aux2.descricao,"quartos");
    }
    else if (strstr(aux2.descricao,"Quartos")){
        resp = strstr(aux2.descricao,"Quartos");
    }
    else if (strstr(aux2.descricao,"QUARTOS")){
        resp = strstr(aux2.descricao,"QUARTOS");
    }
    char *respajustada = NULL;
    if (resp) {
        respajustada = resp - 2;
        int y = atoi(respajustada);
        if (y) printf("\n\ta residencia de id %ld tem %s quarto(s)", id, respajustada);
    }
}


void procuravenda (int t,char *arq){
    TLSE_TR *resp = NULL;
    TABM *x = arq2TABM(arq,t);
    while(!x->folha) x = arq2TABM(x->filhos[0],t);
    while(x){
        for(int i=0;i<x->nchaves;i++){
            if (strstr(x->chaves[i].descricao,"vende")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
            else if (strstr(x->chaves[i].descricao,"Vende")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
            else if (strstr(x->chaves[i].descricao,"VENDE")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
            else if (strstr(x->chaves[i].descricao,"venda")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
            else if (strstr(x->chaves[i].descricao,"Venda")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
            else if (strstr(x->chaves[i].descricao,"VENDA")){
                resp = TLSE_TR_insere(resp,&x->chaves[i]);
            }
        }
        x =  arq2TABM(x->prox,t);
    }
    if (!resp) return;
    TLSE_TR *y = resp, *z;
    double maior = resp->info->preco_total, menor = resp->info->preco_total, troca;
    y = y->prox;
    while (y){
        if (y->info->preco_total > maior){
            maior = y->info->preco_total;
            z = y;
        }
        y = y->prox;
    }
    printf("\n\to imovel a venda mais caro eh o de id %ld, localizado no bairro %s, rua %s e numero %d, e vale %lf reais, com um metro quadrado no valor de %lf.",z->info->id,z->info->bairro,z->info->rua,z->info->numero,z->info->preco_total, z->info->preco_m2);
    y=resp->prox;
    while (y){
        if (y->info->preco_total < menor){
            menor = y->info->preco_total;
            z = y;
        }
        y = y->prox;
    }
    printf("\n\to imovel a venda mais barato eh o de id %ld, localizado no bairro %s, rua %s e numero %d, e vale %lf reais, com um metro quadrado no valor de %lf.",z->info->id,z->info->bairro,z->info->rua,z->info->numero,z->info->preco_total, z->info->preco_m2);
    TLSE_TR_imprime(resp);
}


