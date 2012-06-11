typedef enum enumComandos{
    MEMSIZE,
    PROCSIZE,
    READ,
    WRITE,
    ENDPROC
}enumComandos;


typedef struct page{
    int pagina;
    int acessos;
    int nroPageFault; // será no mínimo 1, quando a página é lida pela primeira vez
    int nroSubst;     // Quantas vezes esta página foi escolhida como "vítima", caso não existam mais páginas disponíveis na memória RAM
} page;

typedef struct LDECpages{
    page        pg;
    LDECpages*  ant;
    LDECpages*  prox;
} LDECpages;

 typedef struct process{
    int pid;
    LDECpages paginas;
} process;
 
 


// procedimentos e funções de leitura do arquivo
void memSize(int size);
void procSize(int id, int size);
void Read(int id, int size);
void Write(int id, int size);
void endProc(int id);

// procedimentos e funções utilizados
void corta(char string[]);
