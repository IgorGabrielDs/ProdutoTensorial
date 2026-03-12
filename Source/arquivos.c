#include <stdio.h>
#include <stdlib.h>
void contar_colunas(FILE *arquivo, int *colunas){
    int caracter;
    while ((caracter = fgetc))
    {
        /* code */
    }
    
}
void contar_linhas(FILE *arquivo, int *linhas){
    int caracter;
    while((caracter = fgetc(arquivo))!= EOF){
        if(caracter == '\n'){
            (*linhas)++;
        }
    }
    rewind(arquivo);
}

void abrir_arquivos(char *argv, int **matriz){
    FILE *arquivo = fopen(argv,"r");
    if (arquivo == NULL){
        printf("ERRO: Arquivo não encontrado!\n");
        exit(1);
    }
    int linhas = 1, colunas = 1;
    contar_linhas(arquivo, &linhas);
    printf("%d\n", linhas);
    if(linhas == colunas){
        printf("Funcionou!");
    }
    fclose(arquivo);
}