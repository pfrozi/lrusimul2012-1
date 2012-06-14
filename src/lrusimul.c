#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lrusimul.h"
#include "../include/processos.h"

int         quant_frames;
tmemoria*   Memoria;
process*    Processos;

/*   Funções internas - INICIO     */
/*
    Função: criaMemoria
    Parâmetros: n(int)
    Descrição: Cria vetor que representa a memória física (RAM) com n quadros. Retorna um ponteiro para o vetor.
*/
tmemoria* criaMemoria(int n)
{
    int i;
    tmemoria* aux;

    aux = (tmemoria*)malloc(sizeof(tmemoria) * n);

    // Seta todos os quadros para disponível
    for(i = 0;i < n; i++){
        aux[i].pid     = DISPONIVEL;
		aux[i].pagina  = DISPONIVEL;
        aux[i].bitRef  = 0;
        aux[i].bitSujo = 0;
    }

    return aux;
}


/*      Funções internas - FIM     */
/*
    Função: memSize
    Parâmetros: size(int)
    Descrição: Define o tamanho da memória física (RAM) em size quadros.
*/
void memSize(int size)
{
    quant_frames = size;
    Memoria = criaMemoria(size);        // memoria
    Processos = criaLista();           // area de swap, onde os processos são inicializados
}

/*
    Função: procSize
    Parâmetros: id(int), size(int)
    Descrição: Cria processo identificado por id com size páginas. Considerase
                que essa criação coloca todas as páginas do processo no swap
                e não na memória RAM.
*/
void procSize(int id, int size)
{
    if (existe(Processos, id))
        printf("Processo %d jah existe e não pode ser criado\n",id);
    else
        insere(Processos, id, size);
}

/*
    Função: Read
    Parâmetros: page(int), id(int)
    Descrição: Realiza a leitura de uma posição de memória da página page
                do processo id. Se a página não estiver na memória, ela deve
                ser carregada. Se não houver quadros livres, o algoritmo LRU
                deve ser acionado para providenciar a substituição de uma outra
                página e a carga da página solicitada.
*/
void Read(int pagina, int id)
{
    int i;

    int frame;

    int pid_vitima,pag_vitima;
    process* vitProcess;

    int pageFault = 1;
    process* auxProcess;


    for(i = 0;i<quant_frames;i++){
        if((Memoria[i].pid == id) && (Memoria[i].pagina == pagina))   // não haverá page fault
        {
            pageFault = 0;
            break;
        }
    }

    auxProcess = consulta(Processos, id); // se não existe retorna nulo

    switch(pageFault)
    {
        case 0:                 // não ocorreu pageFault
        {
            auxProcess->paginas[pagina].acessos++;
            Memoria[i].bitRef = 1;
            break;
        }
        case 1:                 // Ocorreu pageFault
        {
            // verifica se solicitacao existe
            if(auxProcess==NULL)
            {
                printf("Solicitacao de leitura invalida! \n");
            }
            else
            {

                LRUclock(Memoria,&pid_vitima,&pag_vitima,&frame);

                vitProcess = consulta(Processos, pid_vitima);
                auxProcess->paginas[pagina].nroPageFault++;
                auxProcess->paginas[pagina].acessos++;
                auxProcess->paginas[pagina].local = 'M';
                Memoria[frame].pid = id;
                Memoria[frame].pagina = pagina;
                Memoria[frame].bitRef = 1;
                Memoria[frame].bitSujo = 0;

                vitProcess->paginas[pag_vitima].nroSubst++;
                vitProcess->paginas[pag_vitima].local = 'S';
            }
            break;
        }
    }
}

/*
    Função: Write
    Parâmetros: page(int), id(int)
    Descrição: Realiza a escrita em uma posição de memória na página page
                do processo id. Se a página não estiver na memória, ela deve
                ser carregada. Se não houver quadros livres, o algoritmo LRU
                deve ser acionado para providenciar a substituição de uma outra
                página e a carga da página solicitada.
*/
void Write(int pagina, int id)
{
    int i;

    int frame;
    int pageFault = 1;
    process* auxProcess;

    int pid_vitima,pag_vitima;
    process* vitProcess;

    for(i = 0;i<quant_frames;i++){
        if((Memoria[i].pid == id) && (Memoria[i].pagina == pagina))   // não haverá page fault
        {
            pageFault = 0;
            break;
        }
    }

    auxProcess = consulta(Processos, id); // se não existe retorna nulo

    switch(pageFault)
    {
        case 0:                 // não ocorreu pageFault
        {
            auxProcess->paginas[pagina].acessos++;
            Memoria[i].bitRef = 1;
            Memoria[i].bitSujo = 1;
            break;
        }
        case 1:                 // Ocorreu pageFault
        {
            // verifica se solicitacao existe
            if(auxProcess==NULL)
            {
                printf("Solicitacao de leitura invalida! \n");
            }
            else
            {

                LRUclock(Memoria,&pid_vitima,&pag_vitima,&frame);

                vitProcess = consulta(Processos, pid_vitima);
                auxProcess->paginas[pagina].nroPageFault++;
                auxProcess->paginas[pagina].acessos++;
                auxProcess->paginas[pagina].local = 'M';
                Memoria[frame].pid = id;
                Memoria[frame].pagina = pagina;
                Memoria[frame].bitRef = 1;
                Memoria[frame].bitSujo = 1;

                vitProcess->paginas[pag_vitima].nroSubst++;
                vitProcess->paginas[pag_vitima].local = 'S';
            }
            break;
        }
    }
}

/*
    Função: endProc
    Parâmetros: id(inteiro)
    Descrição: Termina a execução do processo id. Todos os quadros alocados
                a este processo devem ser liberados.
*/
void endProc(int id)
{
    int i ;
    // libera processo no swap
    process* auxProcess;

    if (existe(Processos, id)){
        printf("Processo %d nao existe logo nao pode ser finalizado!\n", id);
        return;
    }
    auxProcess = consulta(Processos, id);
    auxProcess->estado = ENCERRADO;

    // libera todos os quadros alocados a este processo
    for(i = 0;i<quant_frames;i++)
    {
        if (Memoria[i].pid == id)
            Memoria[i].pid = DISPONIVEL;
    }
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
    Função: LRUclock
    Parâmetros: Memoria(tmemoria*), vitima(int[]), frame(int*)
    Descrição:
*/
void LRUclock(tmemoria* Memoria,int* pid_vitima, int* pag_vitima,int* frame)
{
    int i;

    *pid_vitima = -1;
    *pag_vitima = -1;
    *frame = -1;

    //procura um quadro livre
    for(i = 0;i<quant_frames;i++)
    {
        if (Memoria[i].pid == DISPONIVEL){
            *frame = i;
            return;                         //encontrou frame livre
        }
    }
    for(i = 0;i<quant_frames * 2;i++)
    {
        if ((Memoria[i % quant_frames].bitRef == 0) && (Memoria[i % quant_frames].bitSujo == 0)){
            *pid_vitima = Memoria[i % quant_frames].pid;
            *pag_vitima = Memoria[i % quant_frames].pagina;
            *frame = i % quant_frames;
            return;
        }
        Memoria[i].bitRef = 0;
    }
    for(i = 0;i<quant_frames;i++)
    {
        if ((Memoria[i].bitRef == 0) && (Memoria[i].bitSujo == 1)){
            *pid_vitima = Memoria[i].pid;
            *pag_vitima = Memoria[i].pagina;
            *frame = i;
            return;
        }
    }

}

/*
    Função: mostraRelatorio();
    Parâmetros: Nenhum
    Descrição: Mostra o Relatório de Processos com as páginas e os acessos à
               memória na tela, usa a função imprimeCrescente().
*/
void mostraRelatorio() {
    imprimeCrescente(Processos);
}

/*
    Função: gravaRelatorio();
    Parâmetros: Nenhum
    Descrição: Grava o arquivo de LOG no local definido por ARQ_LOG. O arquivo
               contém o Relatório de Processos com as páginas e os acessos à
               memória, usa a função imprimeArquivo().
*/
void gravaRelatorio() {
    imprimeArquivo(ARQ_LOG, Processos);
}

/*
    Função:
    Parâmetros:
    Descrição:
*/
