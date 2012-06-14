#define INICIALIZADO   1
#define ENCERRADO      0

#include "../include/lrusimul.h"

typedef struct page {
    int  pagina;
    int  acessos;
    int  nroPageFault;   // será no mínimo 1, quando a página é lida pela primeira vez
    int  nroSubst;       // Quantas vezes esta página foi escolhida como "vítima", caso não existam mais páginas disponíveis na memória RAM
    char local;          // Indica se a página está na memória 'M' ou no swap 'S', quando o processo é criado todas as páginas estão no swap
} page;

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
void imprimeArquivo(char* nome_arquivo, process* l);