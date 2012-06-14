#define INICIALIZADO   1
#define ENCERRADO      0

#define ARQ_LOG "../perf/log.txt"

#include "../include/lrusimul.h"



typedef struct process {
    int         pid;
    int         size;
    int         estado;
    int         quant_pages;
    page*       paginas;
    process*    prox;
} process;
  
// procedimentos e funções da lista de processos
process* criaLista(void);
process* insere(process *l, int pid, int size);
process* remove(process* l, int pid);
process* destroi(process* l);

void imprimeCrescente(process* l);
void gravaLOG(process* l);