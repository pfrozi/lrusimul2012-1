#include <stdio.h>
#include <stdlib.h>  //necessaria para o malloc
#include <string.h> //necessaria para o strcmp
#include "../include/processos.h"

/*
    Função: criaLista
    Parâmetros: Nenhum
    Descrição: Inicializa a lista de processos
*/
process* criaLista(void)
{
    pid_contador = 0;
    return NULL;
}

/*
    Função: insere
    Parâmetros: l(process*), pid(int), size(int)
    Descrição: Insere um novo processo com o pid e o size especificado na lista
               de processos l. Já cria as respectivas páginas de memória para o
               processo. As páginas são "carregadas" inicialmente no swap.
*/
process* insere(process* l, int pid, int size)
{
    process* novo; //novo elemento
    process* ant = NULL; //ponteiro auxiliar para a posição anterior
    process* ptaux = l; //ponteiro auxiliar para percorrer a lista
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

/*
    Função: remove
    Parâmetros: l(process*), pid(int)
    Descrição: Remove da lista de processos l o processo com o pid especificado.
*/
process* removeProc(process* l, int pid)
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

    // libera a memória alocada
    free(ptaux->paginas);
    free(ptaux);

    pid_contador--; // decrementa o total de processos na lista

    return l;
}

/*
    Função: consulta
    Parâmetros: l(process*), pid(int)
    Retorno: O processo pid ou NULL se não encontrar
    Descrição: Consulta o processo identificado pelo pid na lista de processos l.
*/
process* consulta(process* l, int pid)
{
    process* ptaux = l;  //ponteiro auxiliar para percorrer a lista

    /*procura o elemento na lista*/
    while (ptaux != NULL)
    {
        if(ptaux->pid == pid)
            break;
        ptaux = ptaux->prox;
    }

    return ptaux;
}

/*
    Função: existe
    Parâmetros: l(process*), pid(int)
    Retorno: 1, se o processo está na lista l; 0, caso contrário
    Descrição: Verifica se o processo identificado pelo pid existe na lista de
               processos l.
*/
int existe(process* l, int pid)
{
    process *ptaux = NULL; //ponteiro o processo

    ptaux = consulta(l, pid);

    /*verifica se achou*/
    if(ptaux != NULL){
        if(ptaux->estado == INICIALIZADO)
            return 1;
    }
    return 0;
}

/*
    Função: existePagina
    Parâmetros: l(process*), pid(int), page(int)
    Retorno: 1, se existe a página solicitada no processo pid;
             0, caso contrário
    Descrição: Verifica se o processo identificado pelo pid, que está na lista
               l, possui a página solicitada.
*/
int existePagina(process* l, int pid, int page)
{
    process *ptaux = NULL; //ponteiro o processo

    ptaux = consulta(l, pid);

    // Verifica se acho o processo
    if(ptaux != NULL) {
        /* Verifica se a página existe, como são sequenciais, basta verificar se
           é menor que o tamanho do processo em páginas (size) */
        if(page < ptaux->size) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

/*
    Função: destroi
    Parâmetros: l(process*)
    Descrição: Remove todos os processos da lista.
*/
process* destroi(process* l)
{
    process *ptaux; //ponteiro auxiliar para percorrer a lista
    while (l != NULL) {
        ptaux = l;
        l = l->prox;
        free(ptaux->paginas);
        free(ptaux);
    }
    free(l);

    pid_contador = 0; // zera o total de processos na lista

    return NULL;
}

/*
    Função: imprimeCrescente
    Parâmetros: l(process*)
    Descrição: Mostra na tela a listagem de processos com algumas informações
               além da especificação.
*/
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
            printf("Pagina Acessos(R/W) NroPageFault NroSubst Local\n");
            for(i = 0; i < ptaux->size; i++) {
                printf("%-6d %12d %12d %8d %5c\n",
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
        printf("\nERRO: A lista de processos esta vazia.\n");
    }
}

/*
    Função: imprimeArquivo
    Parâmetros: nome_arquivo (char[]), l(process*)
    Descrição: Grava no arquivo nome_arquivo a listagem de processos conforme a
               especificação.
*/
void imprimeArquivo(char nome_arquivo[], process* l)
{
    FILE* arq;
    process* ptaux;
    int i;
    int result;

    printf("Nome arq: %s\n", nome_arquivo);
    //arq = fopen("log.txt", "wt"); // abre para escrita de arquivo texto
    arq = fopen(nome_arquivo, "w"); // abre para escrita de arquivo texto
    if (arq != NULL) {
        if (l != NULL) {
            for(ptaux=l; ptaux!=NULL; ptaux=ptaux->prox) {
                result = fprintf(arq, "PROCESSO %d\n",
                                ptaux->pid);
                if(result == EOF) {
                    printf("\nERRO: Não foi possivel gravar no arquivo de LOG (1).\n");
                    break;
                }
                result = fprintf(arq, "Pagina Acessos(R/W) NroPageFault NroSubst\n");
                for(i = 0; i < ptaux->size; i++) {
                    
                    if(result == EOF) {
                        printf("\nERRO: Não foi possivel gravar no arquivo de LOG (2).\n");
                        break;
                    }

                    result = fprintf(arq, "%-6d %12d %12d %8d\n",
                        ptaux->paginas[i].pagina,
                        ptaux->paginas[i].acessos,
                        ptaux->paginas[i].nroPageFault,
                        ptaux->paginas[i].nroSubst);
                    if(result == EOF) {
                        printf("\nERRO: Não foi possivel gravar no arquivo de LOG (3).\n");
                        break;
                    }
                }
                result = fprintf(arq, "\n");
                if(result == EOF) {
                    printf("\nERRO: Não foi possivel gravar no arquivo de LOG (4).\n");
                    break;
                }
            }
        } else {
            printf("\nERRO: A lista de processos esta vazia.\n");
        }
        fclose(arq);
    } else {
        printf("\nERRO: Não foi possivel criar o arquivo de LOG.\n");
    }
}
