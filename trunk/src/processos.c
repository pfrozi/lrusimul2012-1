#include <stdlib.h>  //necessaria para o malloc
#include <string.h> //necessaria para o strcmp
#include "../include/lrusimul.h"
#include "../include/processos.h"

process* cria_lista(void)
{
    pid_contador = 1;
    return NULL;
}


process* insere_ord(process *l, int pid, int size, int page* paginas)
{
    process *novo; //novo elemento
    process *ant = NULL; //ponteiro auxiliar para a posição anterior
    process *ptaux = l; //ponteiro auxiliar para percorrer a lista
    process *ptLista = l;
     
    novo = (process*) malloc(sizeof(process));
    novo->pid  = pid;
    novo->size = size;
    novo->estado = INICIALIZADO;
    novo->paginas = paginas;
   
    /*procurando a posição de inserção*/
    while ((ptaux!=NULL) && (ptaux->pid != pid)) //se info.titulo < dados.titulo então strcmp retorna um valor menor que zero
    {
        ant = ptaux;
        ptaux = ptaux->prox;
    }

    /*encaeia o elemento*/
    if (ant == NULL) /*o anterior não existe, logo o elemento será inserido na primeira posição*/
    {
        novo->prox = l;
        l = novo;
    }
    else /*elemento inserido no meio da lista*/
    {
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    return l;
}


process* remove(process* l, int pid)
{
    process *ant = NULL; //ponteiro auxiliar para a posição anterior
    process *ptaux = l;  //ponteiro auxiliar para percorrer a lista

    /*procura o elemento na lista*/
    while (ptaux !=NULL && (strcmp(ptaux->info.titulo, titulo)))
    {          
        ant = ptaux;
        ptaux = ptaux->prox;
    }
     
    /*verifica se achou*/
    if (ptaux == NULL)
        return l; /*retorna a lista original*/
       
    if (ant == NULL) /*vai remover o primeiro elemento*/
        l = ptaux->prox;
    else /*vai remover do meio ou do final*/
        ant->prox = ptaux->prox;
      
    free(ptaux); /*libera a memória alocada*/
    
    return l;
}  
