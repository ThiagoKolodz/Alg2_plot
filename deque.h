/* 
 * Arquivo de cabeçalho para manipulaVetor.c
 * Feito por Thiago Fortes Kolodziejski (GRR: 20232364)
 * Feito em 18/07/2023 para a disciplina alg2.
*/

#ifndef __DEQUE_H__
#define __DEQUE_H__

/* Acrescente demais includes que você queira ou precise */
#include <stdint.h>

/* Estrutura de um deque */
typedef struct Deque {
    
    int *dados;
    int frente;
    int tras;
    int tamanho;
    int capacidade;
    
} Deque;

/* Cria um novo deque com capacidade inicial especificada */
Deque * criarDeque(int capacidadeInicial);

/* Libera a memória alocada para o deque */
void liberarDeque(Deque* deque);

/* Adiciona um elemento no início do deque */
void empurrarFrente(Deque* deque, int valor);

/* Adiciona um elemento no final do deque */
void empurrarTras(Deque* deque, int valor);

/* Remove e retorna um elemento do início do deque */
int removerFrente(Deque* deque);

/* Remove e retorna um elemento do final do deque */
int removerTras(Deque* deque);

/* Verifica se o deque está vazio */
int estaVazio(Deque* deque);

/* Verifica se o deque está cheio */
int estaCheio(Deque* deque);

/* Imprime um deque */
void imprimirDeque(Deque* deque);

/* Retorna a quantidade de interacoes feitas com elementos do deque */
uint64_t obterInteracoesDeque();

#endif // __DEQUE_H__
