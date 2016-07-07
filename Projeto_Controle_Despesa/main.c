//
//  main.c
//  Fila Exercicio
//
//  Created by Tauan Flores on 6/5/16.
//  Copyright © 2016 Astral Chest. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "fila-h.h"
#include <string.h>
#include <math.h>

#define MAX 40

typedef struct ElementoD{
    
    double valor;
    struct ElementoD *prox;
    
}ElementoD;

typedef struct Elemento{
    
    double valor;
    struct Elemento *prox;
    
}Elemento;

struct Fila{
    
    char nome[51];
    Elemento *ini;
    Elemento *final;
    
    ElementoD *iniD;
    ElementoD *finalD;
    
};

int verifica_nome(char *s){
    
    int i;
    for (i=0; s[i] != '\0'; i++) {
        
        if ((s[i] >= 0 && s[i] <= 64) || (s[i]>= 91 && s[i] <= 96) || (s[i] >= 123 && s[i] <= 127)) {
            if (s[i] == 32) {
                break;
            }
            printf("Caractere '%c' inválido! Tente novamente.\n",s[i]);
            return 0;
        }
        
    }
    return 1;
}


Fila *fila_cria(void){
    
    char aux[51];
    int a;
    Fila *f = malloc(sizeof(Fila));
    if (f == NULL) {
        abort();
    }
    
    for (a = 1; a != 0;)
    {
        printf("- Criar nova coluna || Digite um nome para coluna:\n");
        scanf(" %[^\n]s",aux);
        if (verifica_nome(aux)) {
            strcpy(f->nome, aux);
            a = 0;
        }else{
            a = 1;
        }
    } // fim for
    
    f->ini = f->final = NULL;
    f->iniD = f->finalD = NULL;
    
    return f;
}

int fila_vazia (Fila *f){
    
    return f->ini == NULL;
}

int fila_vazia_despesa(Fila *f){
    
    return f->iniD == NULL;
}


void fila_destroi (Fila *f){
    
    
    Elemento *p = f->ini;
    while (p != NULL) {
        
        Elemento *aux = p->prox;
        free(p);
        p = aux;
        
    }
    free(f);
    printf("- %s deletada com sucesso!\n\n",f->nome);
    return;
}

int fila_pop_despesa(Fila *f , double *x){
    
    if (fila_vazia_despesa(f)) {
        printf("Impossivel retirar despesa, nao existe despesa.");
        return 0;
    }
    ElementoD *aux;
    aux = f->iniD;
    *x = f->iniD->valor;
    f->iniD = f->iniD->prox;
    free(aux);
    return 1;
}

int fila_insere_dispesa(Fila *f , double x){
    
    ElementoD * elt = malloc(sizeof(ElementoD));
    if (elt == NULL) {
        abort();
    }
    
    elt->prox = NULL;
    elt->valor = x;
    
    if (fila_vazia_despesa(f)) {
        f->iniD = elt;
        f->finalD = elt;
        printf("- %.2f de despesa inserida em %s com sucesso!\n",x , f->nome);
    }
    else
    {
        f->finalD->prox = elt;
        f->finalD = elt;
        printf("- %.2f de despesa inserida em %s com sucesso!\n",x , f->nome);
    }
    return 1;
}

int fila_insere(Fila *f, double x) {
    
    Elemento *elt = malloc(sizeof(Elemento));
    if (elt == NULL) {
        return 0;
    }
    
    elt->prox = NULL;
    elt->valor = x;
    
    if (fila_vazia(f)) {
        
        f->ini = elt;
        f->final = elt;
        printf("- %.2f inserido em %s com sucesso!\n",x , f->nome);
    }else{
        f->final->prox = elt;
        f->final = elt;
        printf("- %.2f inserido em %s com sucesso!\n",x , f->nome);
    }
    return 1;
}

int fila_pop(Fila *f, double *x){
    
    if (fila_vazia(f)) {
        printf("Impossivel remover , fila vazia!\n");
        return 0;
    }
    else
    {
        
        Elemento *p = f->ini;
        f->ini = f->ini->prox;
        *x = p->valor;
        free(p);
        
    }
    printf("\nRemovido com sucesso!\n\n");
    return 1;
}

void exibe_nome_fila(Fila **f , int n){
    
    int i = 0;
    Fila *aux;
    for (aux = f[i] ; f[i] != NULL; i++) {
        
        printf("%d - %s\n",i,f[i]->nome);
    }
    return;
}

void reorganiza_vetor(Fila *v[] ,int x){
    
    for (; v[x] != NULL; x++) {
        v[x] = v[x+1];
    }
    return;
    
}

int testa_existe_despesa(Fila *f){
    
    ElementoD *aux;
    aux = f->iniD;
    if (aux == NULL) {
        return 0;
    }
    
    return 1;
}

void fila_exibe_despesa(Fila *f){
    
    ElementoD *aux;
    double soma = 0.0;
    printf("\nDespesas de %s\n",f->nome);
    for (aux = f->iniD; aux != NULL; aux = aux->prox) {
        
        printf("valor : %.2lf\n",aux->valor);
        soma += aux->valor;
    }
    printf("valor total de despesa: %.2lf\n",soma);
    return;
}

void fila_exibe_lucro(Fila *f){
    
    Elemento *aux;
    double somaR , somaD , lucroB;
    somaR = somaD = lucroB = 0.0;
    printf("\nReceitas de %s\n",f->nome);
    for (aux = f->ini; aux != NULL; aux = aux->prox) {
        
        printf("valor : %.2lf\n",aux->valor);
        somaR += aux->valor;
    }
    ElementoD *auxD;
    printf("\nDespesas de %s\n",f->nome);
    for (auxD = f->iniD; auxD != NULL; auxD = auxD->prox) {
        
        printf("valor : %.2lf\n",auxD->valor);
        somaD += auxD->valor;
    }
    
    lucroB = somaR - somaD;
    printf("\n|*| Soma total das receitas de %s : %.2lf reais |*|",f->nome,somaR);
    printf("\n|*| Soma total das despesas de %s : %.2lf reais |*|\n",f->nome,somaD);
    if (lucroB < 0) {
        printf("|-| Prejuizo encontrado em %s no valor de : %.2lf reais |*|\n",f->nome,lucroB);
        printf("\n");
    }else{
        printf("|+| Lucro bruto: %.2lf reais |+|\n",lucroB);
        printf("\n");
    }
    return;
}

void fila_exibe(Fila *f){
    
    Elemento *aux;
    double soma;
    printf("\nReceitas de %s\n",f->nome);
    for (aux = f->ini; aux != NULL; aux = aux->prox) {
        
        printf("valor : %.2lf\n",aux->valor);
        soma += aux->valor;
    }
    printf("valor total de receita: %.2lf\n",soma);
    return;
}

int testa_se_existe_em_vetor(Fila *f[] , int x ){
    
    int i = 0;
    Fila *aux;
    for (aux = f[i] ; f[i] != NULL; i++) {
        if (i == x) {
            return 1;
        }
    }
    return 0;
}

int testa_vetor_ponteiro_vazio(Fila *f[]){
    
    return f[0] == NULL;
}

void chama_menu_switch(Fila **f, int n){
    
    char s[3];
    char confi , c1,c2;
    int i,y,x,a,z,ok;
    double r;
    a = 0;
    for(i = 0; z != 11 ; i++) { // inicio for
        
        printf("|*|Comandos Menu 1.0|*|\n1 - Criar nova coluna\n2 - Deletar uma coluna\n3 - Inserir receita em coluna\n4 - Remover receita em coluna\n5 - Visualizar lista de colunas\n6 - Remover despesa em coluna\n7 - Inserir despesa em coluna\n8 - Visualiza despesas em uma coluna\n9 - Visualiza receitas em uma coluna\n10 - Calcular lucro bruto\n11 - Sair\n");
        do {
            scanf(" %2[^\n]s", s);
            
            ok =0;
            for (i=0;i<strlen(s);i++){
                if (s[i] >= 48 && s[i] <= 57) {
                    ok = 1;
                }
            }
        } while (!ok);
        
        c1 = s[0];
        c2 = s[1];
        switch (c1) {
            case '1':
                z = 1;
                if (s[1] != 0) {  // caso a string tenha o segundo valor
                    switch (c2) {
                        case '0':
                            z = 10;
                            break;
                            
                        case '1':
                            z = 11;
                            break;
                            
                        case '2':
                            z =12;
                            break;
                            
                        case '3':
                            z = 13;
                            break;
                            
                        case '4':
                            z = 14;
                            break;
                            
                        case '5':
                            z = 15;
                            break;
                            
                        case '6':
                            z = 16;
                            break;
                            
                        case '7':
                            z = 17;
                            break;
                            
                        case '8':
                            z = 18;
                            break;
                            
                        case '9':
                            z = 19;
                            break;
                            
                        default:
                            z = 0;
                            break;
                    }
                }
                break;
                
            case '2':
                z =2;
                break;
                
            case '3':
                z = 3;
                break;
                
            case '4':
                z = 4;
                break;
                
            case '5':
                z = 5;
                break;
                
            case '6':
                z = 6;
                break;
                
            case '7':
                z = 7;
                break;
                
            case '8':
                z = 8;
                break;
                
            case '9':
                z = 9;
                break;
                
            default:
                z = 0;
                break;
        }
        
        switch (z) {
                
            case 1 :
                
                if (a >= MAX) {
                    printf("Muitas colunas, delete uma para criar uma nova.\n");
                    break;
                }
                
                f[a] = fila_cria();
                printf("- %s - Criada com sucesso!\n\n",f[a]->nome);
                a++;
                break;
                
            case 2:
                if (testa_vetor_ponteiro_vazio(f)) {
                    printf("Não existe nenhuma coluna cadastrada.\n");
                    break;
                }
                printf("Selecione o numero da coluna que deseja destruir por completo:\n");
                exibe_nome_fila(f,n);
                scanf(" %d",&x);
                if(testa_se_existe_em_vetor(f,x)){
                    printf("Tem certeza que deseja deletar %s por completo?[Y/N]\n",f[x]->nome);
                    scanf(" %c[y-Y n-N]",&confi);
                    if ((confi == 'y') || (confi == 'Y')) {
                        fila_destroi(f[x]);
                        reorganiza_vetor(f,x);
                        a--;
                        break;
                    }
                    if (confi == 'n' || confi == 'N'){
                        printf("\nVoltando ao menu.\n\n");
                        break;
                    }else{
                        printf("\nColuna não identificada, voltando ao menu..\n\n");
                        break;
                    }
                }
                
            case 3:
                if (testa_vetor_ponteiro_vazio(f)) {
                    printf("Não existe nenhuma coluna cadastrada.\n");
                    break;
                }
                printf("Selecione em qual coluna deseja inserir uma receita:\n");
                exibe_nome_fila(f, n);
                scanf(" %d",&y);
                if(testa_se_existe_em_vetor(f,y)){
                    printf("Selecione um valor:\n");
                    double h;
                    scanf("%lf",&h);
                    fila_insere(f[y],h);
                    break;
                }else{
                    printf("\nColuna não identificada, voltando ao menu.\n\n");
                    break;
                }
                
            case 4:
                if (testa_vetor_ponteiro_vazio(f)) {
                    printf("Não existe nenhuma coluna cadastrada.\n");
                    break;
                }
                printf("Selecione em qual coluna deseja remover uma receita:\n");
                exibe_nome_fila(f, n);
                scanf(" %d",&y);
                fila_exibe(f[y]);
                printf("Tem certeza que deseja remover o primeiro valor?[Y/N]\n");
                scanf(" %c[y-Y n-N]",&confi);
                if (confi == 'y' || confi == 'Y') {
                    fila_pop(f[y], &r);
                    break;
                } else if (confi == 'n' || confi == 'N'){
                    printf("\n..voltando ao menu\n");
                    break;
                }else{
                    printf("\n..letra invalida , voltando ao menu.\n\n");
                    break;
                }
                
                break;
                
            case 5:
                if (testa_vetor_ponteiro_vazio(f)) {
                    printf("Não existe nenhuma coluna cadastrada.\n");
                    break;
                }
                printf("\n- Lista de colunas criadas:\n");
                exibe_nome_fila(f, n);
                printf("\n");
                break;
                
            case 6:
                if (testa_vetor_ponteiro_vazio(f)) {
                    printf("Não existe nenhuma coluna cadastrada.\n");
                    break;
                }
                printf("Selecione em qual coluna deseja remover uma despesa:\n");
                exibe_nome_fila(f, n);
                scanf(" %d",&y);
                if(testa_se_existe_em_vetor(f,y)){
                    if (testa_existe_despesa(f[y])) {
                        fila_exibe_despesa(f[y]);
                        printf("Tem certeza que deseja remover o primeiro valor?[Y/N]\n");
                        scanf(" %c[y-Y n-N]",&confi);
                        if (confi == 'y' || confi == 'Y') {
                            if(fila_pop_despesa(f[y], &r)){
                                printf("\nRemovido com sucesso!\n\n");
                                break;
                                
                            }else{
                                break;
                            }
                        } else if (confi == 'n' || confi == 'N'){
                            printf("\n..voltando ao menu\n");
                            break;
                        }else{
                            printf("\n..letra invalida, voltando ao menu.\n\n");
                            break;
                        }
                        
                        
                    }else{
                        printf("Nao existe despesas cadastradas, adicione alguma despesa.\n");
                        break;
                    }
                    
                }else{
                    printf("Coluna inválida, voltando ao menu..\n");
                    break;
                }
                
            case 7:
                if (testa_vetor_ponteiro_vazio(f)) {
                    printf("Não existe nenhuma coluna cadastrada.\n");
                    break;
                }
                printf("Selecione em qual coluna deseja inserir um valor de despesa:\n");
                exibe_nome_fila(f, n);
                scanf(" %d",&y);
                if(testa_se_existe_em_vetor(f,y)){
                    printf("Selecione um valor:\n");
                    double h;
                    scanf("%lf",&h);
                    fila_insere_dispesa(f[y],h);
                    printf("\n");
                    break;
                }else{
                    printf("\nColuna não identificada, voltando ao menu.\n\n");
                    printf("\n");
                    break;
                }
                
                break;
                
            case 8:
                if (testa_vetor_ponteiro_vazio(f)) {
                    printf("Não existe nenhuma coluna cadastrada.\n");
                    break;
                }
                printf("\n- Escolha uma coluna para visualizar suas despesas:\n");
                exibe_nome_fila(f, n);
                scanf(" %d",&y);
                if(testa_se_existe_em_vetor(f,y)){
                    
                    fila_exibe_despesa(f[y]);
                }else{
                    printf("Coluna nao identificada, retornando ao menu..");
                }
                printf("\n");
                break;
                
            case 9 :
                if (testa_vetor_ponteiro_vazio(f)) {
                    printf("Não existe nenhuma coluna cadastrada.\n");
                    break;
                }
                printf("\n- Escolha uma coluna para visualizar suas receitas:\n");
                exibe_nome_fila(f, n);
                scanf(" %d",&y);
                if(testa_se_existe_em_vetor(f,y)){
                    
                    fila_exibe(f[y]);
                }else{
                    printf("Coluna nao identificada retornando ao menu..");
                }
                printf("\n");
                break;
                
            case 10:
                if (testa_vetor_ponteiro_vazio(f)) {
                    printf("Não existe nenhuma coluna cadastrada.\n");
                    break;
                }
                printf("\n- Escolha uma coluna para calcular o lucro baseado nas receitas e despesas:\n");
                exibe_nome_fila(f, n);
                scanf(" %d",&y);
                if(testa_se_existe_em_vetor(f,y)){
                    
                    fila_exibe_lucro(f[y]);
                }
                break;
                
            case 11:
                printf("\n..Programa Finalizado.\n");
                printf("\n");
                break;
                
            default:
                
                printf("Opcao invalida, tente novamente:\n");
                break;
                
        }
    } // fim for
}

void inicia_vetor_null(Fila *v[] , int n){
    
    int i;
    for (i = 0; i<n+1; i++) {
        v[i] = NULL;
    }
    
}

int main(void) {
    
    Fila *v[MAX];
    inicia_vetor_null(v , MAX);
    chama_menu_switch(v,MAX);
    
    
    return 0;
}
