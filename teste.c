#include "TR.c"


void substituir_virgula_por_ponto(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') {
            str[i] = '.';
        }
    }
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

int main(void){
    TLSE_TR *l = NULL;
    l = ledados("entrada.txt", l);
    imprime_id(l);
    return 0;
}