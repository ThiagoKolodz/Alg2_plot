/*
 * Arquivo de codigo fonte para manipulaVetor.h
 * Feito por Thiago Fortes Kolodziejski (GRR: 20232364)
 * em 20/09/2023 para a disciplina de alg2.
*/

/* acrescente demais includes que voce queira ou precise */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "manipulaVetor.h"

/* 
 * Implementacao das funcoes definidas em 'manipulaVetor.h'. 
 * Algumas funcoes sao internas e so podem ser usadas aqui.
*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int * criaVetor(int tamVetor) {
     
    int *v;
    
    /* Checa se o tamanho eh valido, se nao for, retona 'NULL'. */
    if(!tamVetor)
        return NULL;
    
    return v = (int *) malloc(tamVetor * sizeof(int));
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int inserirVetor(int *v, int tamVetor) {
    
    /* Verifica se o vetor esta alocado, ou se tamVetor é diferente de '0'. */
    if(!v || !tamVetor)
        return -1;
    
    for (int i = MIN_VET; i < tamVetor; i++)
        v[i] = rand();
    
    return 0;
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int imprimirVetor(int *v, int tamVetor) {
    
    /* Verifica se o vetor esta alocado, ou se n é diferente de '0'. */
    if(!v || !tamVetor)
        return -1;
    
    for(int i = MIN_VET; i < tamVetor - 1; i++) {
        
        printf("%d", v[i]);
        printf(" ");
         
    }
    
    printf("%d", v[tamVetor - 1]);
    
    printf("\n");
    return 0;
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int estaOrdenado(int *v, int tamVetor) {
      
    for(int i = 1; i < tamVetor; i++)
        if(v[i] < v[i - 1])
            return 0;

    return 1;
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void inverteVetor(int *v, int tamVetor) {
    
    for (int i = tamVetor - 1, j = 0; i >= 0; i--){
        v[i] = j;
        j++;
    }
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int destroiVetor(int *v) {
    
    /* Caso o vetor nao esteja alocado retorna '-1'. */
    if(!v)
        return -1;
    
    /* Desaloca o vetor de ponteiros para inteiros. */
    free(v);
    return 0;
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

