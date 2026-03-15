#include <stdio.h>
#include <stdlib.h>
#include "arquivos.h"


void calcular_tensor(char *argv1, char *argv2, int **matriz_1, int **matriz_2, int ***matriz_soma){
    FILE *arquivo1 = fopen(argv1, "r");
    FILE *arquivo2 = fopen(argv2, "r");
    int linhas1 = contar_linhas(arquivo1);
    int linhas2 = contar_linhas(arquivo2);
    int colunas1 = contar_colunas(arquivo1);
    int colunas2 = contar_colunas(arquivo2);
    int linhas_soma = linhas1 * linhas2;
    int colunas_soma = colunas1 * colunas2;
    fclose(arquivo1);
    fclose(arquivo2);
    (*matriz_soma) = malloc((linhas_soma) * sizeof(int *));
    if ((*matriz_soma) == NULL){
        printf("ERRO: Falha ao alocar dinamicamente\n");
        exit(1);
    }
    for(int i = 0; i< (linhas_soma); i++){
        (*matriz_soma)[i] = malloc((colunas_soma) * sizeof(int));
        if ((*matriz_soma)[i] == NULL){
        printf("ERRO: Falha ao alocar dinamicamente\n");
        exit(1);
    }
    }
    for(int i = 0; i < linhas1; i++){
        for(int j = 0; j < colunas1; j++){
            for(int k = 0; k < linhas2; k++){
                for(int l = 0; l < colunas2; l++){
                    (*matriz_soma)[i * linhas2 + k][j * colunas2 + l] = matriz_1[i][j] * matriz_2[k][l];
                }
            }
        }
    }
    criar_arquivo(*matriz_soma, linhas_soma, colunas_soma);
}