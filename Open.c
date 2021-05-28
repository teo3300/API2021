#include <stdio.h>
#define uint unsigned int
#define COMMAND_BUFF_LEN 15

#define log
#define print

#ifdef log
    #define LOG(msg)    printf("%4u: %s\n", __LINE__, msg)
#else
    #define LOG(msg) 
#endif

#ifdef print
    #define PRINT(msg)    printf("%4u\n", msg)
#else
    #define LOG(msg) 
#endif

#define ind(y, x) (y*mat_size+x)
/****************************************************** FINE HEADER ***********************************************************************************/

typedef struct GraphData{
    uint index;
    uint total_weight;
}graphData;

// YAY, implementiamo gli heap

typedef struct MinHeap{
    void* data;
    uint len;
    uint heapsize;
    uint chunk_size;
}minHeap;

#define childLeft(n) (2*n)
#define childRight(n) (2*n+1)
#define heapMin(heap)  (*heap)
void createMinHeap(minHeap* heap);                                                  // TODO: sto seriamente pensando di usare Heap[0] per paddare (potrei metterci i metadati)
void minHeapify(minHeap* heap, uint position);                                      //
void deleteMin(minHeap* heap);                                                      //
void insert(minHeap* heap, uint key);                                               // non verrà usato

uint mat_size;                                                                      // perdoname madre por mi variable non locale (da usare in ind(y,x))

int main(){
    uint topK;
    char command_buffer[COMMAND_BUFF_LEN];                                          // usato solo come tampone per distinguere i 2 comandi
    fscanf(stdin, "%u %u\n", &mat_size, &topK);                                     // ottieni dimensione matrice e topK
    PRINT(mat_size);
    PRINT(topK);
    graphData Top[topK+1];                                                          // prototipo: heap classifica
    uint matrix[mat_size*mat_size];                                                 // matrice di interi senza segno a 32 bit come VLA

    while(fscanf(stdin, "%s\n", command_buffer)>0 && (*command_buffer) == 'A' ){    // consuma le linee di comando (quando raggiungi topK esci)
        for (int i=0; i<mat_size; i++){                                             // TODO: incapsulare parser ?
            for(int j=0; j<mat_size; j++){                                          // TODO: cercare di migliorare la lettura della matrice (possibile operare su matrice incompleta?)
                fscanf(stdin, "%u,", &matrix[ind(i,j)]);                            // riempi la matrice volta per volta (probabile brutto brutto)
                printf("%5u ", matrix[ind(i,j)]);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;                                                                       // no errors
}
