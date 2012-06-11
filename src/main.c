#include <stdio.h>
#include <stdlib.h>
#include "lrusimul.h"


int main(int argc, char *argv[])
{
    
    FILE* pFile;
    char* nomeArquivo;
    
    enumComandos  enumComando;
    char          linha[50];
    char          comando[10];
    char          parametros[2][10];
    
    nomeArquivo = argv[1];
    
    // É uma entrada válida
    if (nomeArquivo==NULL){
        printf("\nERRO: Arquivo inválido.\n");
        return -1;
    }
    // Inicialização das estruturas
    
    // Abre arquivo para leitura
    pFile = fopen (nomeArquivo,"r");
    
    fgets(linha,sizeof(linha),pFile);
    strcpy(comando,strtok(linha," \t"));

    // Verifica se o primeiro comando é MEMSIZE
    if(strcmp(comando,"MEMSIZE") < 0){
        printf("\nERRO: Vece não definiu a quantidade de quadros da memoria. O primeiro comando do arquivo deve ser MEMSIZE.\n");
        return -2;
    }    
    strcpy(parametros[0],strtok(linha," \t"));    // extrai o parâmetro 1 do MEMSIZE
    corta(parametros[0]);
    
    // inicializa memoria
    memSize(atoi(parametros[0]));
    
    // le o resto do arquivo
    while(!feof(pFile)){
        
        // verifica o comando
        fgets(linha,sizeof(linha),pFile);
        strcpy(comando,strtok(linha," \t"));
        
        if(!(strcmp(comando,"MEMSIZE") < 0)){
            printf("\nERRO: Vece não pode definir a quantidade de quadros da memoria 2 vezes.\n");
            return -3;
        } 
        if(!(strcmp(comando,"PROCSIZE") < 0))
            enumComando = PROCSIZE;   
        else if(!(strcmp(comando,"READ") < 0))
            enumComando = READ;
        else if(!(strcmp(comando,"WRITE") < 0))
            enumComando = WRITE;
        else if(!(strcmp(comando,"ENDPROC") < 0))
            enumComando = ENDPROC;
        else { // ERRO
            printf("\nERRO: Comando inválido: %s.\n", comando);
            return -4;
        }
        switch(enumComando)
        {
            case PROCSIZE:
            {
                trcpy(parametros[0],strtok(linha," \t"));     // extrai o parâmetro 1 do READ
                strcpy(parametros[1],strtok(linha," \t"));    // extrai o parâmetro 2 do READ
                corta(parametros[1]);
                
                break;
            }
            case READ:
            {
                strcpy(parametros[0],strtok(linha," \t"));    // extrai o parâmetro 1 do READ
                strcpy(parametros[1],strtok(linha," \t"));    // extrai o parâmetro 2 do READ
                corta(parametros[1]);
                
                break;
            }
            case WRITE:
            {
                strcpy(parametros[0],strtok(linha," \t"));    // extrai o parâmetro 1 do WRITE
                strcpy(parametros[1],strtok(linha," \t"));    // extrai o parâmetro 2 do WRITE
                corta(parametros[1]);
                
                break;
            }
            case ENDPROC:
            {
                strcpy(parametros[0],strtok(linha," \t"));    // extrai o parâmetro 1 do ENDPROC
                corta(parametros[0]);
                
                break;
            }
        }
    }
}













