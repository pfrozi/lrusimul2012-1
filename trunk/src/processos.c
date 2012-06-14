#include <stdlib.h>  //necessaria para o malloc
#include <string.h> //necessaria para o strcmp
#include "../include/lrusimul.h"
#include "../include/processos.h"

process* criaLista(void)
{
    pid_contador = 0;
    return NULL;
}


process* insere(process *l, int pid, int size)
{
    process* novo; //novo elemento
    process* ant = NULL; //ponteiro auxiliar para a posição anterior
    process* ptaux = l; //ponteiro auxiliar para percorrer a lista
    process* ptLista = l;
    page* paginas; // Ponteiro para as páginas do processo que serão alucadas como uma matriz
    int i;
 
    /* Gera um array que é um conjunto de páginas para o processo */
    paginas = (page*) malloc((sizeof(page) * size));
    for(i = 0; i < size; i++) {
        paginas[i].pagina = i;
        paginas[i].acessos = 0;
        paginas[i].nroPageFault = 0;
        paginas[i].nroSubst = 0;
        paginas[i].local = 'S';
    }
 
    /* Gera um novo elemento processo na lista */
    novo = (process*) malloc(sizeof(process));
    novo->pid  = pid;
    novo->size = size;
    novo->estado = INICIALIZADO;
    novo->paginas = paginas;
   
    /* procurando a posição de inserção */
    while ((ptaux!=NULL) && (ptaux->pid < pid)) 
    {
        ant = ptaux;
        ptaux = ptaux->prox;
    }

    /* encaeia o elemento */
    if (ant == NULL) /*o anterior não existe, logo o elemento será inserido na primeira posição*/
    {
        novo->prox = l;
        l = novo;
    }
    else /* elemento inserido no meio da lista */
    {
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    pid_contador++; // incrementa o total de processos na lista
    
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

    pid_contador--; // decrementa o total de processos na lista
    
    return l;
}  
 
process* destroi(process* l)
{
    process *ptaux; //ponteiro auxiliar para percorrer a lista
    while (l != NULL) {
        ptaux = l;
        l = l->prox;
        free(ptaux);
    }
    free(l);
    
    pid_contador = 0; // zera o total de processos na lista

    return NULL;            
}

void imprimeCrescente(process* l)
{  
    process* ptaux;
    int i;
    int contador;
    
    printf("TOTAL DE PROCESSOS = %d\n\n", pid_contador);
    if (l != NULL) {
        for(ptaux=l, contador = 0; ptaux!=NULL; ptaux=ptaux->prox, contador++) {
            printf("PROCESSO %d - Size(paginas) = %d - Estado = %d\n", 
                ptaux->pid, ptaux->size, ptaux->estado);
            for(i = 0; i < ptaux->size; i++) {
                printf("Página Acessos(R/W) NroPageFault NroSubst Local\n");
                printf("%-7d %12d %12d %8d %5c\n", 
                    ptaux->paginas[i].pagina, 
                    ptaux->paginas[i].acessos, 
                    ptaux->paginas[i].nroPageFault, 
                    ptaux->paginas[i].nroSubst, 
                    ptaux->paginas[i].local);
            }
            printf("\n");
        }
        printf("\nRECONTAGEM DE PROCESSOS = %d\n", contador);
    } else {
        printf("\nERRO: A lista de processos está vazia.\n");
    }
}

void gravaLOG(process* l)
{
    FILE* arq_log;
    process* ptaux;
    int i;
    int result;
    
    arq_log = fopen(ARQ_LOG,"wt") // abre para escrita de arquivo texto
    if (arq_log != NULL) { 
        if (l != NULL) {
            for(ptaux=l; ptaux!=NULL; ptaux=ptaux->prox) {
                result = fprintf(arq_log, "PROCESSO %d\n", 
                    ptaux->pid, ptaux->size, ptaux->estado);
                if(result == EOF) {
                    printf("\nERRO: Não foi possível gravar no arquivo de LOG (1).\n");
                    break;
                }
                
                for(i = 0; i < ptaux->size; i++) {
                    result = fprintf(arq_log, "Página Acessos(R/W) NroPageFault NroSubst\n");
                    if(result == EOF) {
                        printf("\nERRO: Não foi possível gravar no arquivo de LOG (2).\n");
                        break;
                    }
                    
                    result = fprintf(arq_log, "%-7d %12d %12d %8d\n", 
                        ptaux->paginas[i].pagina, 
                        ptaux->paginas[i].acessos, 
                        ptaux->paginas[i].nroPageFault, 
                        ptaux->paginas[i].nroSubst);
                    if(result == EOF) {
                        printf("\nERRO: Não foi possível gravar no arquivo de LOG (3).\n");
                        break;
                    }
                }
                result = fprintf(arq_log, "\n");
                if(result == EOF) {
                    printf("\nERRO: Não foi possível gravar no arquivo de LOG (4).\n");
                    break;
                }
            }
        } else {
            printf("\nERRO: A lista de processos está vazia.\n");
        }
        fclose(arq_log);
    } else {
        printf("\nERRO: Não foi possível criar o arquivo de LOG.\n");
    }
}