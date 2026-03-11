#include <stdio.h>
#include <stdlib.h>

void abrir_arquivos(char *argv, char *matriz){
    FILE *arquivo = fopen(argv,"r");
    if (arquivo == NULL){
        printf("ERRO: Arquivo não encontrado!\n");
        exit(1);
    }
    fscanf(arquivo, "%s", matriz);
    printf("%s", matriz);
    fclose(arquivo);
}