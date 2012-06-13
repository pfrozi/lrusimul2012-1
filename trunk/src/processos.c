#include <stdlib.h>  //necessaria para o malloc
#include <string.h> //necessaria para o strcmp
#include "../include/lrusimul.h"
#include "../include/processos.h"

process* cria_lista(void)
{
    pid_contador = 1;
    return NULL;
}


process* insere(process *l, int pid, int size, int page* paginas)
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
    while ((ptaux!=NULL) && (ptaux->pid < pid)) 
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
    while (ptaux !=NULL && (ptaux->pid != pid))
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

void imprimeCrescente(process* l)
{  
    process* ptaux;
    if (l == NULL)
        puts("lista vazia");
    else
        for (ptaux=l; ptaux!=NULL; ptaux=ptaux->prox)
            printf("PID = %10d Size(paginas) = %10d Estado = %d\n"
                   , ptaux->pid
                   , ptaux->size,
                     ptaux->estado);
}
 
process* destroi(process* l)
{
   process *ptaux; //ponteiro auxiliar para percorrer a lista
   while (l != NULL)
   {
         ptaux = l;
         l = l->prox;
         free(ptaux);
   }
   free(l);   
   return NULL;            
}   