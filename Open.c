/********** joint with cat **********/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
    #define PRINT(msg)  printf("%4u: %4i\n", __LINE__, msg)
#else
    #define LOG(msg) 
#endif

/********** support.h **********/

typedef struct HeapStruct{
    int node;
    uint weight;                                                // TODO: rinominare weight -> key per l'utilizzo con heap diversi?
}heapStruct;
typedef struct{
    heapStruct* data;
    int length;
    int size;
}Heap;

// daily reminder: le macro sono golose di parentesi o di errori
#define chLeft(n)           (2*(n)+1)           //
#define chRight(n)          (2*(n)+2)           // macro per genitori e figli rimappati per vettore 0 based
#define parent(n)           (((n)-1)>>1)        //
#define heapMin(heap)       (*((heap).data))
#define isSmaller(heap,a,b) ((heap).data[(a)].weight < (heap).data[(b)].weight)

void heapSwap       (Heap heap, int a, int b);
void createMinHeap  (Heap heap);
void minHeapify     (Heap heap, int n);
void heapInsert     (Heap heap, heapStruct  el);
void* deleteMin     (Heap heap, heapStruct* el);

void heapSwap(Heap heap, int a, int b){
    heapStruct C =              { .node = heap.data[a].node, .weight = heap.data[a].weight};
    heap.data[a] = (heapStruct) { .node = heap.data[b].node, .weight = heap.data[b].weight};
    heap.data[b] = (heapStruct) { .node =            C.node, .weight =            C.weight};
}          

void createMinHeap(Heap heap){
    heap.size = heap.length;                        // poni logicamente lo heap sul vettore (il vettore DEVE essere inizializzato)
    for(int i = (parent(heap.length-1)); i > -1; i--)
        minHeapify(heap, i);
}

void minHeapify(Heap heap, int n){
    int pos_min;
    int l = chLeft(n);
    int r = chRight(n);
    if (l <= heap.size && isSmaller(heap, l, n))
        pos_min = l;
    else pos_min = n;
    if (r <= heap.size && isSmaller(heap, r, pos_min))
        pos_min = r;
    if (pos_min != n){
        heapSwap(heap, pos_min, n);
        minHeapify(heap, pos_min);
    }
}

void* deleteMin(Heap heap, heapStruct* el){
    if(heap.size < 1) return NULL;
    *el = (heapStruct){ .node = heapMin(heap).node, heapMin(heap).node};
    heapMin(heap) = (heapStruct){ .node = heap.data[heap.size-1].node, .weight = heap.data[heap.size-1].weight};
    heap.size--;
    minHeapify(heap,0);
    return el;
};

void heapInsert(Heap heap, heapStruct el){
    int i = ++heap.size;    // heap.size ++; int i = heap.size;
    heap.data[heap.size] = (heapStruct){ .node = el.node, .weight = el.weight};
    while (i > 0 && isSmaller(heap, parent(i), i)){
        heapSwap(heap, parent(i), i);
        i = parent(i);
    }
}

/********** heapHandler.c **********/

char AggiungiGrafo[] = "AggiungiGrafo";
char TopK[]          = "TopK";

int nodes_cnt;                                                         // perdoname madre por mi variable non locale (da usare in ind(y,x))
uint* graph_matrix;
Heap node_heap;

void parse();

int main(){
    int K;
    char command_buffer[COMMAND_BUFF_LEN];                              // temporaneo tampone per distinguere i comandi
    scanf("%u %u\n",&nodes_cnt, &K);
    PRINT(nodes_cnt);
    PRINT(K);

    graph_matrix     = (uint*)malloc(nodes_cnt*nodes_cnt*sizeof(uint));     // alloca matrice di incidenza
    node_heap.data   = (heapStruct*) malloc(nodes_cnt*sizeof(heapStruct));  // alloca heap di nodi
    node_heap.length = nodes_cnt;

    while(scanf("%s\n", command_buffer)>0){
        if(!strncmp(command_buffer, AggiungiGrafo, COMMAND_BUFF_LEN)){
            for(int i=0; i<nodes_cnt; i++){
                for(int j=0; j<nodes_cnt; j++){
                    parse(adr(graph_matrix,i,j));                       // TODO: si può migliorare la lettura?
                }
            }
        }else if(!strncmp(command_buffer, TopK, COMMAND_BUFF_LEN)){
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

