#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "arquivos.h"
#include "soma_tensor.h"

typedef struct {
    char *nome_arquivo;
    int ***matriz_destino;
} Arquivo;

void free_matriz(int **matriz, int linhas){
    for(int i = 0; i < linhas; i++){
        free(matriz[i]);
    }
    free(matriz);
}

void *abrir_arquivo(void *arg){
    Arquivo *dados = (Arquivo *)arg;
    abrir_arquivos(dados->nome_arquivo, dados->matriz_destino);
    return NULL;
}

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("ERRO: Numero incorreto de arquivos!\n");
        return 0;
    }

    int **matriz_1;
    int **matriz_2;
    int **matriz_soma;

    pthread_t t1, t2;

    Arquivo dados1 = {argv[1], &matriz_1};
    Arquivo dados2 = {argv[2], &matriz_2};

    pthread_create(&t1, NULL, abrir_arquivo, &dados1);
    pthread_create(&t2, NULL, abrir_arquivo, &dados2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    FILE *arquivo1 = fopen(argv[1], "r");
    FILE *arquivo2 = fopen(argv[2], "r");

    if(arquivo1 == NULL || arquivo2 == NULL){
        printf("ERRO: Arquivo não encontrado!\n");
        return 0;
    }

    int linhas1 = contar_linhas(arquivo1);
    int linhas2 = contar_linhas(arquivo2);

    fclose(arquivo1);
    fclose(arquivo2);

    calcular_tensor(argv[1], argv[2], matriz_1, matriz_2, &matriz_soma);

    free_matriz(matriz_1, linhas1);
    free_matriz(matriz_2, linhas2);

    int linhas_resultado = linhas1 * linhas2;

    if(argc > 3){
        for(int i = 3; i < argc; i++){
            int **matriz_extra;
            int **nova_soma;

            abrir_arquivos(argv[i], &matriz_extra);
            calcular_tensor("tensor_igds.out", argv[i], matriz_soma, matriz_extra, &nova_soma);

            FILE *arquivo_extra = fopen(argv[i], "r");
            FILE *arquivo_tensor = fopen("tensor_igds.out", "r");

            if(arquivo_extra == NULL || arquivo_tensor == NULL){
                printf("ERRO: Arquivo não encontrado!\n");
                return 0;
            }

            int linhas_extra = contar_linhas(arquivo_extra);
            int linhas_antigas = contar_linhas(arquivo_tensor);

            fclose(arquivo_extra);
            fclose(arquivo_tensor);

            free_matriz(matriz_soma, linhas_antigas);
            free_matriz(matriz_extra, linhas_extra);

            matriz_soma = nova_soma;
            linhas_resultado = linhas_antigas * linhas_extra;
        }
    }

    free_matriz(matriz_soma, linhas_resultado);

    return 0;
}