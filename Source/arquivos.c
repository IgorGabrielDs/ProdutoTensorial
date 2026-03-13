#include <stdio.h>
#include <stdlib.h>

int contar_colunas(FILE *arquivo){
    int caracter, anterior = ' ';
    int colunas = 0;

    while ((caracter = fgetc(arquivo)) != EOF && caracter != '\n'){
        if (anterior == ' ' && caracter != ' '){
            colunas++;
        }
        anterior = caracter;
    }

    rewind(arquivo);
    return colunas;
}

int contar_linhas(FILE *arquivo){
    int caracter = fgetc(arquivo), linhas = 0;
    
    if(caracter == EOF){
        return linhas;
    }else{
        linhas = 1;
        while((caracter = fgetc(arquivo)) != EOF){
            if(caracter == '\n'){
                linhas++;
            }
        }
    }
    rewind(arquivo);
    return linhas;
}

void abrir_arquivos(char *argv, int ***matriz){
    FILE *arquivo = fopen(argv,"r");
    if (arquivo == NULL){
        printf("ERRO: Arquivo não encontrado!\n");
        exit(1);
    }

    printf("Linhas: %d\n", contar_linhas(arquivo));
    printf("Colunas: %d\n", contar_colunas(arquivo));
    //criar_matriz
    fclose(arquivo);
}

void criar_arquivo(int **matriz, int linhas, int colunas){
    FILE *arquivo = fopen("tensor_igds.out","w");
    for(int i = 0; i<linhas; i++){
        for(int j = 0; j<colunas; j++){
            fprintf(arquivo, "%d ", matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
}