#include "TR.c"

int main(void){
    int t;
    int cont = 1;
    char * raiz = (char*)malloc(sizeof(char)*30);
    mkdir("Arquivos");
    printf("Insira o valor de t para a construcao da arvore: ");
    scanf("%d", &t);
    if(t < 2) t = 2;
    le_dados("entrada.txt", &raiz, t, &cont);
    TABM_imprime(&raiz, t);
    return 0;
}