/*
 * Arquivo de codigo fonte para ordenacao.h
 * Feito por Thiago Fortes Kolodziejski (GRR: 20232364)
 * em 11/07/2024 para a disciplina de alg2.
*/

/* acrescente demais includes que voce queira ou precise */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deque.h"
#include "ordenacao.h"
#include "manipulaVetor.h"

/* 
 * Implementacao das funcoes definidas em 'ordenacao.h'. 
 * Algumas funcoes sao internas e so podem ser usadas aqui.
*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void getNome(char nome[]) {
    strncpy(nome, "Thiago Fortes Kolodziejski", MAX_CHAR);
    nome[MAX_CHAR - 1] = '\0';
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

uint32_t getGRR() {
    return 20232364;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* Troca dois enderecos de posicao entre si. */
void changePos(int *ini, int *fim) {
    
    int temp = *ini;
    *ini = *fim;
    *fim = temp;
    
}

/* ------------------------------ mergeSort  --------------------------------*/

void merge(int vetor[], int esquer, int metade, int direi, uint64_t *comp) {
    
    /* Cria as variaveis necessarias. */
    int tamUm = metade - esquer + 1;
    int tamDo = direi - metade;
    int pri = MIN_VET, sec = MIN_VET, posi = esquer;
    
    /* Cria subvetores temporarios */
    int *esqueVet = (int*) malloc(tamUm * sizeof(int)); /* Casting para alocacao */
    int *direiVet = (int*) malloc(tamDo * sizeof(int)); /* Casting para alocacao */
    
    if (!esqueVet || !direiVet) {
        fprintf(stderr, "Erro ao alocar memória para os subvetores\n");
        abort(); /* Aborte o programa em caso de falha na alocação de memória */
    }
    
    /* Copia os dados para os subvetores temporarios */
    for (int i = 0; i < tamUm; i++)
        esqueVet[i] = vetor[esquer + i];
    
    for (int j = 0; j < tamDo; j++)
        direiVet[j] = vetor[metade + 1 + j];
    
    /* Mescla os subvetores temporarios de volta ao vetor original */
    while (pri < tamUm && sec < tamDo) {
        
        if ((*comp)++, esqueVet[pri] < direiVet[sec]) {
            
            vetor[posi] = esqueVet[pri];
            pri++;
            
        } else {
            
            vetor[posi] = direiVet[sec];
            sec++;
            
        }
        posi++;
        
    }
    
    /* Copia os elementos restantes, se houver */
    while (pri < tamUm) {
        
        vetor[posi] = esqueVet[pri];
        pri++;
        posi++;
        
    }
    while (sec < tamDo) {
        
        vetor[posi] = direiVet[sec];
        sec++;
        posi++;
        
    }
    
    /* Libera a memoria dos subvetores temporarios */
    free(esqueVet);
    free(direiVet);
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void mergeSortWrapper(int *v, int left, int right, uint64_t *comp) {
    
    if ((*comp)++, left < right) {
        
        int middle = left + (right - left) / 2;
        
        /* Ordena a metade esquerda */
        mergeSortWrapper(v, left, middle, comp);
        
        /* Ordena a metade direita */
        mergeSortWrapper(v, middle + 1, right, comp);
        
        /* Mescla as duas metades ordenadas */
        merge(v, left, middle, right, comp);
        
    }
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

uint64_t mergeSort(int vetor[], size_t tam) {
    
    uint64_t comp = 0;
    mergeSortWrapper(vetor, MIN_VET, tam - 1, &comp);
    return comp;
    
}

/* ------------------------------ quickSort ---------------------------------*/

int particiona(int vetor[], int ini, int fim, int pivo, uint64_t *comp) {
    
    int meio = ini - 1;
    for (int i = ini; i <= fim; i++)
        if ((*comp)++, vetor[i] <= pivo) {
            
            meio++;
            changePos(vetor + meio, vetor + i);
            
        }
    
    return meio;
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void quickSortWrapper(int vetor[], int ini, int fim, uint64_t *comp) {
    
    if(ini >= fim)
        return;
    
    int meio = particiona(vetor, ini, fim, vetor[fim], comp);  
    quickSortWrapper(vetor, ini, meio - 1, comp);
    quickSortWrapper(vetor, meio + 1, fim, comp);
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

uint64_t quickSort(int vetor[], size_t tam) {
    
    uint64_t comp = 0;
    quickSortWrapper(vetor, MIN_VET, tam - 1, &comp);
    return comp;
    
}

/* ------------------------------ heapSort ----------------------------------*/

/* FunÃ§Ã£o para transformar um array em um heap mÃ¡ximo. */
void maxHeapify(int vetor[], int i, int tam, uint64_t *comp) {
    
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;
    int maior = i;

    // Verifica se o filho esquerdo Ã© maior que o pai
    if ((*comp)++, esq < tam && vetor[esq] > vetor[maior])
        maior = esq;

    // Verifica se o filho direito Ã© maior que o pai
    if ((*comp)++, dir < tam && vetor[dir] > vetor[maior])
        maior = dir;

    // Se o maior elemento nÃ£o for o pai, faz a troca e chama maxHeapify recursivamente
    if ((*comp)++, maior != i) {
        
        changePos(&vetor[i], &vetor[maior]);
        maxHeapify(vetor, maior, tam, comp);
        
    }
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* FunÃ§Ã£o para construir um heap mÃ¡ximo. */
void buildMaxHeap(int vetor[], int tam, uint64_t *comp) {
    
    for (int i = tam / 2; i >= 0; i--)
        maxHeapify(vetor, i, tam, comp);
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

uint64_t heapSort(int vetor[], size_t tam) {
    
    uint64_t comp = 0;
    buildMaxHeap(vetor, tam, &comp);

    for (int i = tam - 1; i > 0; i--) {
        
        // Troca o elemento mÃ¡ximo (raiz) com o Ãºltimo elemento nÃ£o ordenado
        changePos(&vetor[0], &vetor[i]);
        
        // Chama maxHeapify para reconstruir o heap mÃ¡ximo com o restante do vetor
        maxHeapify(vetor, 0, i, &comp);
        
    }

    return comp;
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

uint64_t mergeSortSR(int vetor[], size_t tam) {
    
    uint64_t comp = 0;
    Deque *deque = criarDeque(100);
    
    /* Empilha intervalos no deque para mesclar iterativamente */
    for (int size = 1; size < tam; size *= 2) {
        for (int start = 0; start < tam; start += 2 * size) {
            
            int meio = start + size - 1;
            int end = start + 2 * size - 1;
            
            if (meio >= tam - 1)
                meio = tam - 1;
            
            if (end >= tam - 1)
                end = tam - 1;
            
            /* Empilha os intervalos no deque */
            empurrarTras(deque, start);
            empurrarTras(deque, meio);
            empurrarTras(deque, end);
            
        }
    }
    
    /* Desempilha e mescla os intervalos */
    while (!estaVazio(deque)) {
        
        int start = removerFrente(deque);
        int meio = removerFrente(deque);
        int end = removerFrente(deque);

        merge(vetor, start, meio, end, &comp);
        
    }
    
    liberarDeque(deque);
    return comp;
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

uint64_t quickSortSR(int vetor[], size_t tam) {
    
    uint64_t comp = 0;
    Deque *deque = criarDeque(100);
    
    // Empilha o intervalo inicial
    empurrarTras(deque, 0);
    empurrarTras(deque, tam - 1);
    
    while (!estaVazio(deque)) {
        int fim = removerTras(deque);
        int ini = removerTras(deque);

        if (ini < fim) {
            int meio = particiona(vetor, ini, fim, vetor[fim], &comp);

            // Empilha o subvetor direito
            empurrarTras(deque, meio + 1);
            empurrarTras(deque, fim);

            // Empilha o subvetor esquerdo
            empurrarTras(deque, ini);
            empurrarTras(deque, meio - 1);
        }
    }
    
    liberarDeque(deque);
    return comp;
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void maxHeapifyIterativo(int vetor[], int i, int tam, uint64_t *comp) {
    
    Deque *deque = criarDeque(100);
    empurrarTras(deque, i);

    while (!estaVazio(deque)) {
        i = removerFrente(deque);
        int esq = 2 * i + 1;
        int dir = 2 * i + 2;
        int maior = i;

        if ((*comp)++, esq < tam && vetor[esq] > vetor[maior])
            maior = esq;

        if ((*comp)++, dir < tam && vetor[dir] > vetor[maior])
            maior = dir;

        if ((*comp)++, maior != i) {
            changePos(&vetor[i], &vetor[maior]);
            empurrarTras(deque, maior);
        }
    }

    liberarDeque(deque);
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void buildMaxHeapIterativo(int vetor[], int tam, uint64_t *comp) {
    for (int i = tam / 2; i >= 0; i--)
        maxHeapifyIterativo(vetor, i, tam, comp);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

uint64_t heapSortSR(int vetor[], size_t tam) {
    
    uint64_t comp = 0;
    buildMaxHeapIterativo(vetor, tam, &comp);

    for (int i = tam - 1; i > 0; i--) {
        changePos(&vetor[0], &vetor[i]);
        maxHeapifyIterativo(vetor, 0, i, &comp);
    }

    return comp;
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
