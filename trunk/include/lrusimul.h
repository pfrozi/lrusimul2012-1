#define DISPONIVEL -1

typedef struct LRUclock {
    int  pid;
    int  pagina;
    int  bitRef;
    int  bitSujo;
} LRUclock;

typedef enum enumComandos {
    MEMSIZE,
    PROCSIZE,
    READ,
    WRITE,
    ENDPROC
}enumComandos;

// Estrutura para os elementos do vetor memoria, com quadro igual a indice
typedef struct tmemoria {
    int  pid;
    int  pagina;
    int  bitRef;
    int  bitSujo;
} tmemoria;

typedef struct page {
    int  pagina;
    int  acessos;
    int  nroPageFault;   // será no mínimo 1, quando a página é lida pela primeira vez
    int  nroSubst;       // Quantas vezes esta página foi escolhida como "vítima", caso não existam mais páginas disponíveis na memória RAM
    char local;          // Indica se a página está na memória 'M' ou no swap 'S', quando o processo é criado todas as páginas estão no swap
} page;


// procedimentos e funções de leitura do arquivo
void memSize(int size);
void procSize(int id, int size);
void Read(int id, int size);
void Write(int id, int size);
void endProc(int id);

// procedimento de criação do relatório
void criaRelatorio();

// procedimentos e funções auxiliares utilizados
void corta(char string[]);
