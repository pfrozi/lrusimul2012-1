typedef enum enumComandos{
    MEMSIZE,
    PROCSIZE,
    READ,
    WRITE,
    ENDPROC
}enumComandos;

typedef struct ListMEMO{
    int  pagina;
    int  bitRef;
    int  bitMod;
    ListMEMO* prox;
}ListMEMO;

typedef struct page{
    //int  pagina;
    int  quadro;
    int  acessos;
    int  nroPageFault;   // será no mínimo 1, quando a página é lida pela primeira vez
    int  nroSubst;       // Quantas vezes esta página foi escolhida como "vítima", caso não existam mais páginas disponíveis na memória RAM
    char SwapMem;
} page;

typedef struct TABpages{
    page        pg;
    LDECpages*  ant;
    LDECpages*  prox;
} TABpages;

 typedef struct process{
    int pid;
    TABpages* paginas;
} process;
 
 

// procedimentos e funções de leitura do arquivo
void memSize(int size);
void procSize(int id, int size);
void Read(int id, int size);
void Write(int id, int size);
void endProc(int id);

// procedimentos e funções auxiliares utilizados
void corta(char string[]);
