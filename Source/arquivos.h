#ifndef ARQUIVOS_H
#define ARQUIVOS_H
int contar_colunas(FILE *arquivo);
int contar_linhas(FILE *arquivo);
void abrir_arquivos(char *argv, int ***matriz);
void criar_arquivo(int **matriz_soma, int linhas, int colunas);

#endif