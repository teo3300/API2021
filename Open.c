#include <stdio.h>

#define uint unsigned int
#define COMMAND_BUFF_LEN 15

#define log
#define print

#define ind(y, x) (y*nodes_cnt+x)                                 // usato per trattare vettore dei vertici come una matrice

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

uint nodes_cnt;                                                     // perdoname madre por mi variable non locale (da usare in ind(y,x))

int main(){
    uint topK,
         cnt = 0;
    char command_buffer[COMMAND_BUFF_LEN];                          // temporaneo tampone per distinguere i comandi
    scanf("%u %u\n",&nodes_cnt, &topK);
    PRINT(nodes_cnt);
    PRINT(topK);

    uint graph_matrix[nodes_cnt*nodes_cnt];

    while(scanf("%s\n", command_buffer)>0){
        if((*command_buffer) == 'A'){
            cnt++;
            for(int i=0; i<nodes_cnt; i++){
                for(int j=0; j<nodes_cnt; j++){
                    scanf("%u,", &graph_matrix[ind(i,j)]);           // TODO: possibile operare su matrice incompleta?
                }
            }
        }else if((*command_buffer) == 'T'){
            
        }
    }
    return 0;
}

/********** OpenPart.c **********/

