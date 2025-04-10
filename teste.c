#include "funcoes.h"

// Função para limpar o buffer de entrada
void limpar_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(void){
    TR aux, aux2;
    int t, opcao, op2, op3;
    long int id;
    int cont = 1;
    char * raiz = (char*)malloc(sizeof(char)*30);
    printf("Insira o valor de t para a construcao da arvore: ");
    scanf("%d", &t);
    if(t < 2) t = 2;
    le_dados("entrada.txt", &raiz, t, &cont);
    TABM_imprime(&raiz, t);
    do{
        printf("\n\t0 - Sair\n\t1 - Retornar imoveis\n\t2 - Retirar imoveis\n\t3 - Inserir imoveis\n\t4 - Alterar imoveis\n\t5 - Imprimir informacoes de um ID\n\t6 - Retornar infomacoes adicionais\n\t7 - Imprimir arvore");
        printf("\n");
        printf("\tDigite uma das opcoes acima: ");
        scanf("%d", &opcao);
        printf("\n");
        switch (opcao)
        {
            case 1:
                printf("\n\t0 - Voltar\n\t1 - Por preco\n\t2 - Por localidade\n\t3 - Por tipo\n\t4 - Por metragem\n\t");
                printf("\n");
                printf("\tDigite uma das opcoes acima: ");
                scanf("%d", &op2);
                printf("\n");
                if (op2==1){
                    printf("\n\t0 - Voltar\n\t1 - A venda mais caro e mais barato\n\t2 - Alugado mais caro e mais barato");
                    printf("\n");
                    printf("\tDigite uma das opcoes acima: ");
                    scanf("%d", &op2);
                    printf("\n");
                    if (op2==1){
                        procuravenda(t,raiz);
                    }
                    else if (op2==2){
                        procuraaluga(t,raiz);
                    }
                    else continue;
                }
                else if (op2==2){
                    printf("\n\t0 - Voltar\n\t1 - CEP\n\t2 - latitude\n\t3 - longitude\n\t4 - rua\n\t 5 - bairro");
                    printf("\n");
                    printf("\tDigite uma das opcoes acima: ");
                    scanf("%d", &op2);
                    printf("\n");
                    if (op2==1){
                        int cep;
                        printf("\n\tdigite o cep: ");
                        scanf("%d",&cep);
                        retornaCEP(cep,t,raiz);
                    }
                    else if (op2==2){
                        char lat[20];
                        printf("\n\tdigite a latitude:");
                        limpar_buffer();
                        scanf("%s",lat);
                        limpar_buffer();
                        retornaLAT(lat,t,raiz);
                    }
                    else if(op2==3){
                        char lo[20];
                        printf("\n\tdigite a longitude:");
                        limpar_buffer();
                        scanf("%s",lo);
                        limpar_buffer();
                        retornaLO(lo,t,raiz);
                    }
                    else if (op2==4){
                        char rua[20];
                        printf("\n\tdigite a rua:");
                        limpar_buffer();
                        scanf("%50[^\n]", rua);
                        limpar_buffer();
                        retornaRUA(rua,t,raiz);
                    }
                    else if (op2==5){
                        char ba[20];
                        limpar_buffer();
                        printf("\n\tdigite o bairro:");
                        scanf("%30[^\n]",ba);
                        limpar_buffer();
                        retornaBAIRRO(ba,t,raiz);
                    }
                    else continue;
                }
                else if (op2==3){
                    printf("\n\t0 - Voltar\n\t1 - Apartamentos\n\t2 - Casas\n\t3 - Terrenos Residenciais\n\t4 - Comércios\n\t 5 - Escritórios\n\t 6 - Salas Comerciais\n\t 7 - Condomínios\n\t 8 - Empreendimentos\n\t 9 - Coberturas\n\t 10 - Casas de Vilarejo\n\t 11 - Depósitos\n\t 12 - Lotes");
                    printf("\n");
                    printf("\tDigite uma das opcoes acima: ");
                    scanf("%d", &op2);
                    printf("\n");
                    retornaTIPO(op2,t,&raiz);

                }
                else if (op2==4){
                    int m2;
                    printf("\n\tdigite a metragem: ");
                    scanf("%d",&m2);
                    retornaM2(m2,t,raiz);
                }
                break;

            case 2:
                printf("\n\t0 - Voltar\n\t1 - Por faixa de preco\n\t2 - Por localidade\n\t3 - Por tipo\n\t4 - Por metragem\n\t");
                printf("\n");
                printf("\tDigite uma das opcoes acima: ");
                scanf("%d", &op2);
                printf("\n");
                if (op2==1){
                    int vma, vmi;
                    printf("\n\tdigite o valor minimo:");
                    scanf("%d",&vmi);
                    printf("\n\tdigite o valor maximo:");
                    scanf("%d",&vma);
                    removeImoveisPorPreco(vmi,vma,t,raiz);
                    TABM_imprime(&raiz, t);
                }
                else if (op2==2){
                    printf("\n\t0 - Voltar\n\t1 - CEP\n\t2 - latitude\n\t3 - longitude\n\t4 - rua\n\t 5 - bairro");
                    printf("\n");
                    printf("\tDigite uma das opcoes acima: ");
                    scanf("%d", &op3);
                    printf("\n");
                    if (op3==1){
                        int cep;
                        printf("\n\tdigite o cep: ");
                        scanf("%d",&cep);
                        retiraPorCEP(cep,t,raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else if (op3==2){
                        char lat[20];
                        printf("\n\tdigite a latitude:");
                        limpar_buffer();
                        scanf("%s",lat);
                        limpar_buffer();
                        retiraPorLatitude(lat,t,raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else if(op3==3){
                        char lo[20];
                        printf("\n\tdigite a longitude:");
                        limpar_buffer();
                        scanf("%s",lo);
                        limpar_buffer();
                        retiraPorLongitude(lo,t,raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else if (op3==4){
                        char rua[20];
                        printf("\n\tdigite a rua:");
                        limpar_buffer();
                        scanf("%50[^\n]", rua);
                        limpar_buffer();
                        retiraPorRua(rua,t,raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else if (op3==5){
                        char ba[20];
                        printf("\n\tdigite o bairro:");
                        limpar_buffer();
                        scanf("%30[^\n]",ba);
                        limpar_buffer();
                        printf("%s", ba);
                        retiraPorBairro(ba,t,raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else continue;
                }
                else if (op2==3){
                    printf("\n\t0 - Voltar\n\t1 - Apartamentos\n\t2 - Casas\n\t3 - Terrenos Residenciais\n\t4 - Salas Comerciais\n\t 5 - Escritórios\n\t 6 - Comércios\n\t 7 - Condomínios\n\t 8 - Empreendimentos\n\t 9 - Coberturas\n\t 10 - Casas de Vilarejo\n\t 11 - Depósitos\n\t 12 - Lotes");
                    printf("\n");
                    printf("\tDigite uma das opcoes acima: ");
                    scanf("%d", &op3);
                    printf("\n");
                    if(op3 == 1){
                        retiraPorTipo("APARTMENT", t, raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else if(op3 == 2){
                        retiraPorTipo("HOME", t, raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else if(op3 == 3){
                        retiraPorTipo("RESIDENTIAL_ALLOTMENT_LAND", t, raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else if(op3 == 4){
                        retiraPorTipo("COMMERCIAL_PROPERTY", t, raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else if(op3 == 5){
                        retiraPorTipo("OFFICE", t, raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else if(op3 == 6){
                        retiraPorTipo("COMMERCIAL_BUILDING", t, raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else if(op3 == 7){
                        retiraPorTipo("CONDOMINIUM", t, raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else if(op3 == 8){
                        retiraPorTipo("BUSINESS", t, raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else if(op3 == 9){
                        retiraPorTipo("PENTHOUSE", t, raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else if(op3 == 10){
                        retiraPorTipo("VILLAGE_HOUSE", t, raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else if(op3 == 11){
                        retiraPorTipo("SHED_DEPOSIT_WAREHOUSE", t, raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else if(op3 == 12){
                        retiraPorTipo("ALLOTMENT_LAND", t, raiz);
                        TABM_imprime(&raiz, t);
                    }
                    else continue;
                }
                else if (op2==4){
                    int m2;
                    printf("\n\tdigite a metragem: ");
                    scanf("%d",&m2);
                    retiraPorMetragem(m2, t, raiz);
                    TABM_imprime(&raiz, t);
                }
                break;

            case 3:
                printf("\n\tdigite as seguintes informacoes:\n");

                printf("\n\tid: ");
                scanf("%ld",&aux.id);
                limpar_buffer();

                printf("\n\tbairro: ");
                scanf("%29[^\n]",aux.bairro);
                limpar_buffer();

                printf("\n\trua: ");
                scanf("%49[^\n]",aux.rua);
                limpar_buffer();

                printf("\n\ttipo: ");
                scanf("%29[^\n]",aux.tipo);
                limpar_buffer();

                printf("\n\tlatitude: ");
                scanf("%29[^\n]",aux.latitude);
                limpar_buffer();

                printf("\n\tlongitude: ");
                scanf("%29[^\n]",aux.longitude);
                limpar_buffer();

                printf("\n\tcep: ");
                scanf("%d",&aux.cep);
                limpar_buffer();

                printf("\n\tnumero: ");
                scanf("%d",&aux.numero);
                limpar_buffer();

                printf("\n\tpreco: ");
                scanf("%lf",&aux.preco_total);
                limpar_buffer();

                printf("\n\tpreco/m2: ");
                scanf("%lf",&aux.preco_m2);
                limpar_buffer();

                printf("\n\tdescricao: ");
                scanf("%2499[^\n]",aux.descricao);
                limpar_buffer();

                strcpy(raiz,TABM_insere(&aux, t, &raiz, &cont));
                TABM_imprime(&raiz, t);
                break;

            case 4:
                printf("\n\tdigite o id do imovel que deseja alterar:");
                scanf("%ld",&id);
                TABM_imprime_por_ID(raiz, id, t);
                printf("\n\n");
                printf("\n\t0 - voltar\n\t1 - preco total\n\t2 - preco por m2\n\t3 - descricao\n");
                printf("\n");
                printf("\tDigite o que deseja alterar: ");
                scanf("%d", &op2);
                if (op2 == 1){
                    printf("\n\tdigite o novo preco total:");
                    scanf("%lf",&aux2.preco_total);
                    alteraPrecoTotal(id,aux2.preco_total,t,raiz);
                    TABM_imprime_por_ID(raiz, id, t);
                }
                else if (op2 == 2){
                    printf("\n\tdigite o novo preco por m2:");
                    scanf("%lf",&aux2.preco_m2);
                    alteraPrecoPorM2(id,aux2.preco_m2,t,raiz);
                    TABM_imprime_por_ID(raiz, id, t);
                }
                else if (op2 == 3){
                    limpar_buffer();
                    printf("\n\tdigite a nova descricao: ");
                    limpar_buffer();
                    scanf("%2500[^\n]",aux2.descricao);
                    limpar_buffer();
                    alteraDescricao(id,aux2.descricao,t,raiz);
                    TABM_imprime_por_ID(raiz, id, t);
                }
                break;

            case 5:
                printf("\n\tdigite o id do imovel que deseja imprimir:");
                scanf("%ld",&id);
                TABM_imprime_por_ID(raiz, id, t);
                break;

            case 6:
                printf("\n\tdigite o id do imovel que voce quer receber informacoes adicionais: ");
                scanf("%ld", &id);
                procuraqto(id,t,raiz);
                procuravaga(id,t,raiz);
                procurabanheiro(id,t,raiz);
                procuraamb(id,t,raiz);
                procuradorm(id,t,raiz);
                procurametro(id,t,raiz);
                procurap24(id,t,raiz);
                procurasuite(id,t,raiz);
                break;

            case 7:
                TABM_imprime(&raiz, t);
                break;
            default:
                if(opcao != 0) printf("Opcao invalida!!!\n");
                break;
        }
    } while (opcao);
    free(raiz);
    return 0;
}