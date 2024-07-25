/* 
 * Arquivo de header para manipulaVetor.c
 * Feito por Thiago Fortes Kolodziejski (GRR: 20232364)
 * Feito em 25/09/2023 para a disciplina alg2.
*/

#ifndef __MANIPULA_VETOR_H__
#define __MANIPULA_VETOR_H__

/* Define MIN_VET como o minmo valor excluso do indice do vetor, no caso: 0 */ 
#define MIN_VET 0

/* Função que aloca um vetor com 'tamVetor - 1' posicoes. 
 * - Retornar 0 se ocorreu tudo certo, ou -1 se houve algum problema. */
int * criaVetor(int tamVetor);

/* Função que realiza a inserção de valores aleatorios no vetor. 
 * - Retornar 0 se ocorreu tudo certo, ou -1 se houve algum problema. */
int inserirVetor(int *vetor, int tamVetor);

/* Função responsável por realizar a impressão de um vetor de inteiros.
 * - Retornar 0 se ocorreu tudo certo, ou -1 se houve algum problema. */
int imprimirVetor(int *vetor, int tamVetor); 

/* Função que checa se um vetor de inteiros esta ordenado ou nao. 
 * - Retornar 1 se o vetor esta ordenado, ou 0 se nao. */
int estaOrdenado(int *v, int tamVetor);

/* Função que retorna o vetor original ao contrario. */
void inverteVetor(int *v, int tamVetor);

/* Função que destroi em memória o vetor de racionais. 
 * - Retornar 0 se ocorreu tudo certo, ou -1 se houve algum problema. */
int destroiVetor(int *vetor);

#endif /* __MANIPULA_VETOR_H__ */
