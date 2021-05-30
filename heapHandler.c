typedef struct HeapStruct{
    int node;
    uint weight;
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

