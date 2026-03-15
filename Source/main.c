#include <stdio.h>
#include <stdlib.h>
#include "arquivos.h"
#include "soma_tensor.h"
void liberar_matriz(int **matriz, int linhas){
    for(int i = 0; i < linhas; i++){
        free(matriz[i]);
    }
    free(matriz);
}

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("ERRO: Numero incorreto de arquivos!\n");
        return 0;
    }
    int **matriz_1;
    int **matriz_2;
    int **matriz_soma;
    abrir_arquivos(argv[1], &matriz_1);
    abrir_arquivos(argv[2], &matriz_2);
    calcular_tensor(argv[1], argv[2], matriz_1, matriz_2, &matriz_soma);

    if(argc > 3){
        for(int i = 3; i < argc; i++){
            int **matriz_extra;
            int **nova_soma;

            abrir_arquivos(argv[i], &matriz_extra);

            calcular_tensor("tensor_igds.out", argv[i], matriz_soma, matriz_extra, &nova_soma);

            int linhas_antigas = contar_linhas(fopen("tensor_igds.out", "r"));
            liberar_matriz(matriz_soma, linhas_antigas);

            int linhas_extra = contar_linhas(fopen(argv[i], "r"));
            liberar_matriz(matriz_extra, linhas_extra);

            matriz_soma = nova_soma;
        }
    }

    return 0;
}