#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TR.h"

void procuraqto (long int id,int t,char *arq);

void retornaBAIRRO(char *bairro, int t, char *arq);

void retornaCEP(int cep, int t, char *arq);

// Retorna todas residências de mesma latitude
void retornaLAT(char *latitude, int t, char *arq);

// Retorna todas residências de mesma longitude
void retornaLO(char *longitude, int t, char *arq);

// Retorna todas residências situadas no mesmo bairro
void retornaBAIRRO(char *bairro, int t, char *arq);

// Retorna todas residências de mesmo tipo
void retornaTIPO(int tipo, int t, char **arq);

// Retorna todas residências com mesma quantidade de metros quadrados
void retornaM2(double m2, int t, char *arq);

// Retorna todas residências na mesma rua
void retornaRUA(char *rua, int t, char *arq);

// Remove todos imoveis dentro de uma faixa de preço
void removeImoveisPorPreco(double precoMin, double precoMax, int t, char *arq);

// Alterando preço por m2
void alteraPrecoPorM2(long int id, double novoPrecoM2, int t, char *arq);
// Alterando descrições
void alteraDescricao(long int id, char *novaDescricao, int t, char *arq);


void retiraPorTipo(char *tipo, int t, char *arq);


void retiraPorCEP(int cep, int t, char *arq);


void retiraPorRua(char *rua, int t, char *arq);

void retiraPorLatitude(char *latitude, int t, char *arq);

void retiraPorLongitude(char *longitude, int t, char *arq);


void retiraPorBairro(char *bairro, int t, char *arq);

void procuraqto (long int id,int t,char *arq);

void procuravenda (int t,char *arq);

void procurabanheiro (long int id,int t,char *arq);

void procuradorm (long int id,int t,char *arq);

void procuravaga (long int id,int t,char *arq);

void procurasuite (long int id,int t,char *arq);

void procuraamb (long int id,int t,char *arq);

void procurametro (long int id,int t,char *arq);

void procurap24 (long int id,int t,char *arq);

void procuravenda (int t,char *arq);

void procuraaluga (int t,char *arq);

void alteraPrecoTotal(long int id, double novoPrecoTotal, int t, char *arq);