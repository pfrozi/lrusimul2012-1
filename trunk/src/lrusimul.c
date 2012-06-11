#include <stdio.h>
#include <stdlib.h>

/*
    Função: memSize
    Parâmetros: size(inteiro)
    Descrição: Define o tamanho da memória física (RAM) em size quadros.
*/
void memSize(int size)
{

}

/*
    Função: procSize
    Parâmetros: id(inteiro), size(inteiro)
    Descrição: Cria processo identificado por id com size páginas. Considerase
                que essa criação coloca todas as páginas do processo no swap
                e não na memória RAM.
*/
void procSize(int id, int size)
{

}

/*
    Função: Read
    Parâmetros: page(inteiro), id(inteiro)
    Descrição: Realiza a leitura de uma posição de memória da página page
                do processo id. Se a página não estiver na memória, ela deve
                ser carregada. Se não houver quadros livres, o algoritmo LRU
                deve ser acionado para providenciar a substituição de uma outra
                página e a carga da página solicitada.
*/
void Read(int id, int size)
{

}

/*
    Função: Write
    Parâmetros: page(inteiro), id(inteiro)
    Descrição: Realiza a escrita em uma posição de memória na página page
                do processo id. Se a página não estiver na memória, ela deve
                ser carregada. Se não houver quadros livres, o algoritmo LRU
                deve ser acionado para providenciar a substituição de uma outra
                página e a carga da página solicitada.
*/
void Write(int id, int size)
{

}

/*
    Função: endProc
    Parâmetros: id(inteiro)
    Descrição: Termina a execução do processo id. Todos os quadros alocados
                a este processo devem ser liberados.
*/
void endProc(int id)
{

}

/*
    Função: corta
    Parâmetros: string(char[])
    Descrição: Função que corta o que sobra do string
*/
void corta(char string[])
{
    if(string[strlen(string)-1]=='\n')
       string[strlen(string)-1] ='\0';
}
/*
    Função: 
    Parâmetros: 
    Descrição: 
*/

/*
    Função: 
    Parâmetros: 
    Descrição: 
*/

/*
    Função: 
    Parâmetros: 
    Descrição: 
*/