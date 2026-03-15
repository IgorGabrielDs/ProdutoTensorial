#include <stdio.h>
#include <stdlib.h>
#include "arquivos.h"
#include "soma_tensor.h"

int main(int argc, char *argv[]){
    if(argc<3){
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
            int quantidade = argc - 3;
            int ***matrizes = malloc(quantidade * sizeof(int **));
            for (int i = 3; i < argc;i++){
                abrir_arquivos(argv[i], &matrizes[i]);
                calcular_tensor(argv[1], "tensor_igds.out", matrizes[i], matriz_soma, &matriz_soma);
            }
    }
    return 0;
}