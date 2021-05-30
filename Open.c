/********** joint with cat **********/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define uint unsigned int
#define COMMAND_BUFF_LEN 14

#define log
#define print

#define ind(y, x) ((y) * nodes_cnt + (x))                                 // usato per trattare vettore dei vertici come una matrice
#define adr(matrix, y, x)   ( (matrix) + (y) * nodes_cnt + (x))

/********** header.h **********/

#ifdef log
    #define LOG(msg)    printf("%4u: %s\n", __LINE__, msg)
#else
    #define LOG(msg) 
#endif

#ifdef print
    #define PRINT(msg)  printf("%4u: %4u\n", __LINE__, msg)
#else
    #define LOG(msg) 
#endif

/********** support.h **********/

typedef struct NodeHeapStruct{
        uint node;
        uint weight;
}nodeHeapStruct;
typedef nodeHeapStruct* nodeHeap;

#define chLeft(n)       (2*n)
#define chRight(n)      (2*n+1)
#define heapMin(heap)   (*heap)
void createMinHeap  (nodeHeap heap);
void minHeapify     (nodeHeap heap, uint position);
void deleteMin      (nodeHeap heap);
void heapInsert     (nodeHeap heap, uint key);

/********** heapHandler.c **********/

uint nodes_cnt;                                                         // perdoname madre por mi variable non locale (da usare in ind(y,x))
uint* graph_matrix;

void parse();

int main(){
    uint topK;
    char command_buffer[COMMAND_BUFF_LEN];                              // temporaneo tampone per distinguere i comandi
    scanf("%u %u\n",&nodes_cnt, &topK);
    PRINT(nodes_cnt);
    PRINT(topK);

    graph_matrix = (uint*)malloc(nodes_cnt*nodes_cnt*sizeof(uint));     // alloca matrice di incidenza
    while(scanf("%s\n", command_buffer)>0){
        if((*command_buffer) == 'A'){
            for(int i=0; i<nodes_cnt; i++){
                for(int j=0; j<nodes_cnt; j++){
                    parse(adr(graph_matrix,i,j));                       // TODO: si può migliorare la lettura?
                }
            }
        }else if((*command_buffer) == 'T'){
        }
    }
    free(graph_matrix);
    return 0;
}

void parse(uint* ret){                                                  // scanf merda (davvero parsare tutto direttamente da stdin è più veloce?)
    *ret=0;
    int c = getchar();
    while(c != '\n' && c != ','){
        *ret = (*ret)*10 + c -'0';
        c = getchar();
    }
}

/********** OpenPart.c **********/

