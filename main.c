/*
 * Arquivo MAIN que realiza testes com o arquivo ordenacao.h
 * Feito por Thiago Fortes Kolodziejski (GRR: 20232364)
 * em 15/07/2024 para a disciplina de alg2.
*/

/* acrescente demais includes que voce queira ou precise */
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/types.h>

#include "deque.h"
#include "ordenacao.h"
#include "manipulaVetor.h"

/* 
 * Implementação da estrutura principal do programa. 
 * Algumas funções são internas e só podem ser usadas aqui.
*/

/*~~~~~~~~~~~~~~~~~~~ Tratamendo do resultado dos Testes ~~~~~~~~~~~~~~~~~~~~~*/

/* Função para imprimir os dados */
void printMatrixResults(uint64_t resultsComp[][4], double resultsTime[][4]) {
    
    /* Rótulos para os tipos de ordenação */
    const char *labels[] = {"Ms", "Qs", "Hp", "MsSR", "QsSR", "HpSR"};
    int numLabels = sizeof(labels) / sizeof(labels[0]);
    
    /* Rótulos das colunas */
    const char *columnHeaders[] = {"tam", "VetAleat", "VetInv", "VetOrd"};
    int numCols = sizeof(columnHeaders) / sizeof(columnHeaders[0]);
    
    /* Calcula o número de '+' necessários para a borda superior e inferior */
    int colWidth = 22; /* 20 para o valor + 2 para os espaços */
    int labelWidth = 8; /* Largura do rótulo com 8 caracteres de espaçamento */
    int borderLength = (numCols * colWidth) + labelWidth + 2 + 1; /* 1 para a tabulação inicial */
    
    /* Imprime a borda superior */
    printf("\t");
    for (int i = 0; i < borderLength; i++)
        printf("+");
    printf("\n");
    
    /* Imprime os cabeçalhos das colunas */
    printf("\t+ ");
    for (int i = 0; i < numCols; i++)
        printf("%21s", columnHeaders[i]);
    printf("            +\n");
    
    /* Imprime a borda abaixo dos cabeçalhos */
    printf("\t");
    for (int i = 0; i < borderLength; i++)
        printf("+");
    printf("\n");
    
    /* Imprime os resultados de comparações */
    for (int i = 0; i < numLabels; i++) {
        printf("\t+ %-4s", labels[i]);
        for (int j = 0; j < numCols; j++)
            printf("%20" PRIu64, resultsComp[i][j]);
        printf("            +\n");
    }
    
    /* Imprime a borda que divide as comparacoes do tempo */
    printf("\t");
    for (int i = 0; i < borderLength; i++)
        printf("+");
    printf("\n");
    
    /* Imprime os resultados de tempo */
    for (int i = 0; i < numLabels; i++) {
        printf("\t+ %-4s%20" PRIu64, labels[i], resultsComp[i][0]);
        for (int j = 1; j < numCols; j++)
            printf("%20.8f", resultsTime[i][j]);
        printf("            +\n");
    }
    
    /* Imprime a borda inferior */
    printf("\t");
    for (int i = 0; i < borderLength; i++)
        printf("+");
    printf("\n");
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* Inicia os dados dos vetores que contém os resultados */
void initResults(uint64_t resultsComp[][4], 
                 double resultsTime[][4], size_t tamVetor) {
    
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 4; j++) {
            if (j == 0) {
                resultsComp[i][j] = tamVetor;
                resultsTime[i][j] = (double) tamVetor;
            } else {
                resultsComp[i][j] = 0;
                resultsTime[i][j] = 0;
            }
        }
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void printNome(char nome[MAX_CHAR]) {
    
    getNome(nome);
    printf("\t++++++++++++++++++++++++++++++++++++++++++\n");
	printf("\t+ Trabalho de %s +\n", nome);
	printf("\t+ GRR %u\t\t\t\t +\n", getGRR());
    printf("\t++++++++++++++++++++++++++++++++++++++++++\n");
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void printComp(uint64_t numComp) {
    
    if(numComp > 1000)
        printf("\n|\t A qtd de comparacoes foi: %ld \t\t|\n", numComp);
    else
        printf("\n|\t A qtd de comparacoes foi: %ld \t\t\t|\n", numComp);
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* Faz o calculo do tempo de execucao da funcao e o imprime. */
double printTime(clock_t start, clock_t end) {
    
	double total = ((double)end - start)/CLOCKS_PER_SEC;
    printf("\n|\t O tempo gasto pelo algoritmo foi: %f \t|\n", total);
    return total;
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void printEstaOrdenado(int vetor[], int tamVetor) {
    
    if(estaOrdenado(vetor, tamVetor))
        printf("\n|\t O vetor ficou ordenado corretamente. \t\t|\n");
    else
        printf("\n|\t\t Falha na ordenacao. \t\t|\n");
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void testarOrdena(int vetor[], int tamVetor, uint64_t resultsComp[][4], 
        double resultsTime[][4], uint64_t (*protFunc)(int*, size_t)) {
    
    static int i = 0;
	clock_t start, end; //variáveis do tipo clock_t
    uint64_t numComp;
    
    printf("\n------------- Teste com o vetor aleatorio: --------------\n");
    inserirVetor(vetor, tamVetor);
    start = clock();
    numComp = protFunc(vetor, tamVetor);
    end = clock();
    printComp(numComp);
    resultsComp[i][1] = numComp;
    resultsTime[i][1] = printTime(start, end);
    printEstaOrdenado(vetor, tamVetor);
    
    printf("\n-------------- Teste com o vetor inverso: ---------------\n");
    inverteVetor(vetor, tamVetor);
    start = clock();
    numComp = protFunc(vetor, tamVetor);
    end = clock();
    printComp(numComp);
    resultsComp[i][2] = numComp;
    resultsTime[i][2] = printTime(start, end);
    printEstaOrdenado(vetor, tamVetor);
    
    printf("\n-------------- Teste com o vetor ordenado: --------------\n");
    start = clock();
    numComp = protFunc(vetor, tamVetor);
    end = clock();
    printComp(numComp);
    resultsComp[i][3] = numComp;
    resultsTime[i][3] = printTime(start, end);
    printEstaOrdenado(vetor, tamVetor);
    
    printf("\n=========================================================\n\n");
    
    i++;
    
}

void salvarResultadosGNUPlot(const char *nomeArquivo, uint64_t resultsComp[6][4], double resultsTime[6][4]) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    // Cabeçalho da tabela
    fprintf(arquivo, "# %-10s %-10s %-15s %-15s %-15s %-15s %-15s %-15s\n",
            "Algoritmo", "tam", "VetAleat", "VetInv", "VetOrd", "TempoAleat", "TempoInv", "TempoOrd");

    // Linhas de dados
    const char *labels[6] = {"Ms", "Qs", "Hp", "MsSR", "QsSR", "HpSR"};
    for (int i = 0; i < 6; i++) {
        fprintf(arquivo, "%-10s %-10" PRIu64 " %-15" PRIu64 " %-15" PRIu64 " %-15" PRIu64 " %-15.8f %-15.8f %-15.8f\n",
                labels[i], resultsComp[i][0], resultsComp[i][1], resultsComp[i][2], resultsComp[i][3],
                resultsTime[i][1], resultsTime[i][2], resultsTime[i][3]);
    }

    fclose(arquivo);
}

/* --------------------------------- MAIN ---------------------------------- */

int main() {
    
	int *vetor;
    size_t tamVetor;
    double resultsTime[6][4];
    uint64_t resultsComp[6][4];
	char nome[MAX_CHAR];
    
    srand(time(NULL)); /* Define uma semente para o gerador aleatorio. */
    
    tamVetor = 10000;
    vetor = criaVetor(tamVetor);
	if(!vetor){
        
		printf("Falha fatal. Impossível alocar memoria.");
		return 1;
        
	}
    
    initResults(resultsComp, resultsTime, tamVetor);
    
    printf("\n================== MERGE SORT RECURSIVO =================\n");
    testarOrdena(vetor, tamVetor, resultsComp, resultsTime, mergeSort);
    
    printf("\n================== QUICK SORT RECURSIVO =================\n");
    testarOrdena(vetor, tamVetor, resultsComp, resultsTime, quickSort);
    
    printf("\n================== HEAP SORT RECURSIVO  =================\n");
    testarOrdena(vetor, tamVetor, resultsComp, resultsTime, heapSort);
    
    printf("\n================== MERGE SORT INTERATIVO ================\n");
    testarOrdena(vetor, tamVetor, resultsComp, resultsTime, mergeSortSR);
    
    printf("\n================== QUICK SORT INTERATIVO ================\n");
    testarOrdena(vetor, tamVetor, resultsComp, resultsTime, quickSortSR);
    
    printf("\n================== HEAP SORT INTERATIVO  ================\n");
    testarOrdena(vetor, tamVetor, resultsComp, resultsTime, heapSortSR);
    
    destroiVetor(vetor);
    
    printf("\n");
    printf("\t\t\t\t Visualizacao dos resultados, forma simplificada: \n");
    printMatrixResults(resultsComp, resultsTime);
    printf("\n");
    printf("\n");
    printf("\t\t\t\t *Quantidade total de interacoes no deque: * \n");
    printf("\t\t\t\t->\t%20" PRIu64, obterInteracoesDeque());
    printf("\n");
    printf("\n");
    printNome(nome);
    salvarResultadosGNUPlot("resultados_gnuplot.txt", resultsComp, resultsTime);
    /* Chama o GNUPlot para gerar o gráfico */
    system("gnuplot plot.gp");
    
	return 0;
    
}

/* ------------------------------------------------------------------------- */

