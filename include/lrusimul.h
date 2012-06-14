#define DISPONIVEL -1
#define ARQ_LOG    "../perf/log.txt"

#define MEMSIZE     1
#define PROCSIZE    2
#define READ        3
#define WRITE       4
#define ENDPROC     5

// Estrutura para os elementos do vetor memoria, com quadro igual a indice
typedef struct tmemoria {
    int  pid;     // PID do Processo cuja página ocupa a célula da memória
    int  pagina;  // Página do processo que está ocupando a célula
    int  bitRef;  // Bit de Referência, indica se a página foi ou não acessada recentemente
    int  bitSujo; // Bit de Sujo, indica se a página foi alterada recentemente
} tmemoria;

// procedimentos e funções de leitura do arquivo
void memSize(int size);
void procSize(int id, int size);
void Read(int pagina, int id);
void Write(int pagina, int id);
void endProc(int id);

// algoritmo LRU segunda chace modificado
void LRUclock(tmemoria* Memoria,int* pid_vitima, int* pag_vitima,int* frame);

// procedimento de criação do relatório
void mostraRelatorio();
void gravaRelatorio();

// procedimentos e funções auxiliares utilizados
void corta(char string[]);

