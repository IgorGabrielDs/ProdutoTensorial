#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
    int inicio;
    int fim;
    int colunas;
    int **matriz;
} Dados;

void *alocar_matriz(void *arg){
    Dados *dados = (Dados *)arg;

    for(int i = dados->inicio; i < dados->fim; i++){
        dados->matriz[i] = malloc(dados->colunas * sizeof(int));
        if (dados->matriz[i] == NULL){
            printf("ERRO: Falha ao alocar dinamicamente\n");
            exit(1);
        }
    }

    return NULL;
}

int contar_colunas(FILE *arquivo){
    int caracter, valor, colunas = 0;

    while (fscanf(arquivo, "%d", &valor) == 1){
        colunas++;
        if(fgetc(arquivo) == '\n'){
            break;
        }
    }
    
    rewind(arquivo);
    return colunas;
}

int contar_linhas(FILE *arquivo){
    int caracter, anterior = 0, linhas = 0, conteudo = 0;

    while((caracter = fgetc(arquivo)) != EOF){
        if((anterior == '\n' && caracter == '\n') || 
           (anterior == ' ' && caracter == '\n') ||
           (anterior == '\n' && caracter == ' ')){
            printf("ERRO: Formatação incorreta\n");
            exit(1);
        }
        if(caracter != ' ' && caracter != '\n'){
            conteudo = 1;
        }
        if(caracter == '\n'){
            if(conteudo){
                linhas++;
                conteudo = 0;
            }
        }
        anterior = caracter;
    }
    if(conteudo){
        linhas++;
    }

    rewind(arquivo);
    return linhas;
}

void criar_matriz(FILE *arquivo, int ***matriz){
    int linhas = contar_linhas(arquivo);
    int colunas = contar_colunas(arquivo);

    *matriz = malloc(linhas * sizeof(int *));
    if (*matriz == NULL){
        printf("ERRO: Falha ao alocar dinamicamente\n");
        exit(1);
    }

    pthread_t t1, t2;
    Dados dados1, dados2;
    int meio = linhas / 2;

    dados1.inicio = 0;
    dados1.fim = meio;
    dados1.colunas = colunas;
    dados1.matriz = *matriz;

    dados2.inicio = meio;
    dados2.fim = linhas;
    dados2.colunas = colunas;
    dados2.matriz = *matriz;

    pthread_create(&t1, NULL, alocar_matriz, &dados1);
    pthread_create(&t2, NULL, alocar_matriz, &dados2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            fscanf(arquivo, "%d", &(*matriz)[i][j]);
        }
    }

    rewind(arquivo);
}

void abrir_arquivos(char *argv, int ***matriz){
    FILE *arquivo = fopen(argv,"r+");
    if (arquivo == NULL){
        printf("ERRO: Arquivo não encontrado!\n");
        exit(1);
    }
    int caracter = fgetc(arquivo);

    if (caracter == EOF){
        printf("ERRO: Arquivo vazio\n");
        exit(1);
    }
    if(caracter == ' ' || caracter == '\n'){
        printf("ERRO: Formatação incorreta\n");
        exit(1);
    }
    rewind(arquivo);
    criar_matriz(arquivo, matriz);
    fclose(arquivo);
}

void criar_arquivo(int **matriz_soma, int linhas, int colunas){
    FILE *arquivo = fopen("tensor_igds.out","w");
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            fprintf(arquivo, "%d", matriz_soma[i][j]);
            if(j < colunas-1){
                fprintf(arquivo, " ");
            }
        }
        if(i < linhas-1){
            fprintf(arquivo, "\n");
        }
    }
    fclose(arquivo);
}