/*
 * Arquivo de código fonte para deque.c Feito por Thiago Fortes Kolodziejski (GRR: 20232364)
 * em 11/07/2024 para a disciplina de alg2.
*/

/* Acrescente demais includes que você queira ou precise */
#include <stdio.h>
#include <stdlib.h>

#include "deque.h"

/* Variável global para contar as interações */
static uint64_t contadorInteracoes = 0;

/* 
 * Implementação das funções definidas em 'deque.h'. 
 * Algumas funções são internas e só podem ser usadas aqui.
*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Deque* criarDeque(int capacidadeInicial) {
    Deque *deque = (Deque *) malloc(sizeof(Deque));
    deque->dados = (int *) malloc(capacidadeInicial * sizeof(int));
    deque->frente = 0;
    deque->tras = 0;
    deque->tamanho = 0;
    deque->capacidade = capacidadeInicial;
    return deque;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void liberarDeque(Deque* deque) {
    free(deque->dados);
    free(deque);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void redimensionarDeque(Deque* deque) {
    int capacidadeNova = deque->capacidade * 2;
    int *novosDados = (int *) malloc(capacidadeNova * sizeof(int));
    if (!novosDados) {
        fprintf(stderr, "Erro ao alocar memória para os subvetores no deque\n");
        abort();
    }

    for (int i = 0; i < deque->tamanho; i++) {
        novosDados[i] = deque->dados[(deque->frente + i) % deque->capacidade];
    }

    free(deque->dados);
    deque->dados = novosDados;
    deque->frente = 0;
    deque->tras = deque->tamanho;
    deque->capacidade = capacidadeNova;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void empurrarFrente(Deque* deque, int valor) {
    if (estaCheio(deque)) {
        redimensionarDeque(deque);
    }
    deque->frente = (deque->frente - 1 + deque->capacidade) % deque->capacidade;
    deque->dados[deque->frente] = valor;
    deque->tamanho++;
    contadorInteracoes++;  /* Incrementa o contador de interações */
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void empurrarTras(Deque* deque, int valor) {
    if (estaCheio(deque)) {
        redimensionarDeque(deque);
    }
    deque->dados[deque->tras] = valor;
    deque->tras = (deque->tras + 1) % deque->capacidade;
    deque->tamanho++;
    contadorInteracoes++;  /* Incrementa o contador de interações */
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int removerFrente(Deque* deque) {
    if (estaVazio(deque)) {
        printf("Deque está vazio\n");
        return -1; /* Erro: deque vazio */
    }
    int valor = deque->dados[deque->frente];
    deque->frente = (deque->frente + 1) % deque->capacidade;
    deque->tamanho--;
    contadorInteracoes++;  /* Incrementa o contador de interações */
    return valor;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int removerTras(Deque* deque) {
    if (estaVazio(deque)) {
        printf("Deque está vazio\n");
        return -1; /* Erro: deque vazio */
    }
    deque->tras = (deque->tras - 1 + deque->capacidade) % deque->capacidade;
    int valor = deque->dados[deque->tras];
    deque->tamanho--;
    contadorInteracoes++;  /* Incrementa o contador de interações */
    return valor;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int estaVazio(Deque* deque) {
    return deque->tamanho == 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int estaCheio(Deque* deque) {
    return deque->tamanho == deque->capacidade;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void imprimirDeque(Deque* deque) {
    if (estaVazio(deque)) {
        printf("Deque está vazio\n");
        return;
    }

    printf("Deque contém: ");
    for (int i = 0; i < deque->tamanho; i++) {
        int indice = (deque->frente + i) % deque->capacidade;
        printf("%d ", deque->dados[indice]);
    }
    printf("\n");
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

uint64_t obterInteracoesDeque() {
    return contadorInteracoes;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
