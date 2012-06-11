typedef enum enumComandos{
    MEMSIZE,
    PROCSIZE,
    READ,
    WRITE,
    ENDPROC
}enumComandos;

 typedef struct process{
    int pid;
    
} process;
 
 typedef struct page{
    int pagina;
    int acessos;
    int nroPageFault; // será no mínimo 1, quando a página é lida pela primeira vez
    int nroSubst;     // Quantas vezes esta página foi escolhida como "vítima", caso não existam mais páginas disponíveis na memória RAM
} page;

typedef struct LDECpages{

} LDECpages;