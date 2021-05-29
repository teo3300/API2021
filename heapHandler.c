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

