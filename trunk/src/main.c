#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lrusimul.h"

int main(int argc, char *argv[])
{

    FILE* pFile;
    char* nomeArquivo;

    int           enumComando;
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
    if (pFile==NULL){
        printf("\nERRO: Arquivo nao existe ou eh invalido.\n");
        return -1;
    }

    fgets(linha,sizeof(linha),pFile);
    strcpy(comando,strtok(linha," \t"));

    // Verifica se o primeiro comando é MEMSIZE
    if(strcmp("MEMSIZE",comando) < 0){
        printf("\nERRO: Voce não definiu a quantidade de quadros da memoria. O primeiro comando do arquivo deve ser MEMSIZE.\n");
        return -2;
    }
    strcpy(parametros[0],strtok(NULL," \t"));    // extrai o parâmetro 1 do MEMSIZE
    //corta(parametros[0]);

    // inicializa memoria
    printf("Comando: MEMSIZE\nParametros: %s\n\n"
                        ,parametros[0]);
    memSize(atoi(parametros[0]));

    // le o resto do arquivo
    while(!feof(pFile)){

        // verifica o comando
        fgets(linha,sizeof(linha),pFile);
        //corta(linha);
        strcpy(comando,strtok(linha," \t"));
        
        if(strlen(comando)<4)
            break;
            
        if(!(strcmp("MEMSIZE ",comando))){
            printf("\nERRO(Comando: %s): Voce nao pode definir a quantidade de quadros da memoria 2 vezes.\n",comando);
            return -3;
        }

        if(!(strcmp("PROCSIZE",comando)))
            enumComando = PROCSIZE;
        else if(!(strcmp("READ",comando)))
            enumComando = READ;
        else if(!(strcmp("WRITE",comando)))
            enumComando = WRITE;
        else if(!(strcmp("ENDPROC",comando)))
            enumComando = ENDPROC;
        else { // ERRO
            printf("\nERRO: Comando inválido: %s.\n", comando);
            return -4;
        }
        switch(enumComando)
        {
            case PROCSIZE:
            {
                strcpy(parametros[0],strtok(NULL," \t"));     // extrai o parâmetro 1 do READ
                strcpy(parametros[1],strtok(NULL," \t"));     // extrai o parâmetro 2 do READ

                printf("Comando: PROCSIZE\nParametros: %s\t %s\n\n"
                        ,parametros[0]
                        ,parametros[1]);

                procSize(atoi(parametros[0]),atoi(parametros[1]));

                break;
            }
            case READ:
            {
                strcpy(parametros[0],strtok(NULL," \t"));    // extrai o parâmetro 1 do READ
                strcpy(parametros[1],strtok(NULL," \t"));    // extrai o parâmetro 2 do READ
                

                printf("Comando: READ\nParametros: %s\t %s\n\n"
                        ,parametros[0]
                        ,parametros[1]);

                Read(atoi(parametros[0]),atoi(parametros[1]));

                break;
            }
            case WRITE:
            {
                strcpy(parametros[0],strtok(NULL," \t"));    // extrai o parâmetro 1 do WRITE
                strcpy(parametros[1],strtok(NULL," \t"));    // extrai o parâmetro 2 do WRITE
                

                printf("Comando: WRITE\nParametros: %s\t %s\n\n"
                        ,parametros[0]
                        ,parametros[1]);

                Write(atoi(parametros[0]),atoi(parametros[1]));

                break;
            }
            case ENDPROC:
            {
                strcpy(parametros[0],strtok(NULL," \t"));    // extrai o parâmetro 1 do ENDPROC
                

                printf("Comando: ENDPROC\nParametros: %s\n\n"
                        ,parametros[0]);

                endProc(atoi(parametros[0]));

                break;
            }
        }
    }

    // Grava o arquivo de LOG
    mostraRelatorio();
    gravaRelatorio();

    return 1;
}













