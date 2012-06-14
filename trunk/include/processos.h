#define INICIALIZADO   1
#define ENCERRADO      0


typedef struct page {
    int  pagina;
    int  acessos;
    int  nroPageFault;   // será no mínimo 1, quando a página é lida pela primeira vez
    int  nroSubst;       // Quantas vezes esta página foi escolhida como "vítima", caso não existam mais páginas disponíveis na memória RAM
    char local;          // Indica se a página está na memória 'M' ou no swap 'S', quando o processo é criado todas as páginas estão no swap
} page;

typedef struct process {
    int         pid;
    int         size; // Quantidade de páginas
    int         estado;
    page*       paginas;
    struct process*    prox;
} process;

int pid_contador;

// procedimentos e funções da lista de processos
process* criaLista(void);
process* insere(process *l, int pid, int size);
process* removeProc(process* l, int pid);
process* destroi(process* l);
process* consulta(process* l, int pid);
int existe(process* l, int pid);
int existePagina(process* l, int pid, int page);

void imprimeCrescente(process* l);
void imprimeArquivo(char* nome_arquivo, process* l);
