#include <stdio.h>
#include "arquivos.h"

int main(int argc, char *argv[]){
    if(argc<2){
        printf("ERRO: Numero insuficiente de arquivos!\n");
        return 0;
    }
    char *valor;
    abrir_arquivos(argv[1], valor);

}