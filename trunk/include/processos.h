#define INICIALIZADO   1
#define ENCERRADO      0

#include "../include/lrusimul.h"

typedef struct process{
    int         pid;
    int         size;
    int         estado;
    page*       paginas;
    process*    prox;
} process;
 
int pid_contador;
 
// procedimentos e funções da lista de processos
process* cria_lista(void);
process* insere(process *l, int pid, int size, int page* paginas);
process* remove(process* l, int pid);
void imprimeCrescente(process* l);
process* destroi(process* l);