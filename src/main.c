#include <stdio.h>
#include <stdlib.h>
#include "lrusimul.h"


int main(int argc, char *argv[])
{
    FILE* pFile;
    char* nomeArquivo;
    
    nomeArquivo = argv[1];
    
    // É uma entrada válida
    if (nomeArquivo==NULL){
        printf("Arquivo inválido.");
        return -1;
    }
    // Inicialização das estruturas
    
    // Abre arquivo para leitura
    pFile = fopen (nomeArquivo,"r");
    
}
