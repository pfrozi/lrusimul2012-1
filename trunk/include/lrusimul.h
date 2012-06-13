#DEFINE DISPONIVEL -1

typedef struct LRUclock{
    int  pid;
    int  pagina;
    int  bitRef;
    int  bitSujo;
}LRUclock;

typedef enum enumComandos{
    MEMSIZE,
    PROCSIZE,
    READ,
    WRITE,
    ENDPROC
}enumComandos;

// Estrutura para os elementos do vetor memoria, com quadro igual a indice
typedef struct tmemoria{
    int  pid;
    int  pagina;
} tmemoria;

typedef struct page{
    int  pagina;
    int  acessos;
    int  nroPageFault;   // ser� no m�nimo 1, quando a p�gina � lida pela primeira vez
    int  nroSubst;       // Quantas vezes esta p�gina foi escolhida como "v�tima", caso n�o existam mais p�ginas dispon�veis na mem�ria RAM
    char SwapMem;
    int  bitRef;
    int  bitSujo;
} page;

 typedef struct process{
    int         pid;
    page*       paginas;
    process*    prox;
    process*    ant;
} process;
 
 

// procedimentos e fun��es de leitura do arquivo
void memSize(int size);
void procSize(int id, int size);
void Read(int id, int size);
void Write(int id, int size);
void endProc(int id);

// procedimentos e fun��es auxiliares utilizados
void corta(char string[]);
