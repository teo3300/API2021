#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define uint                    unsigned int                                        // abbreviazione unsigned int
#define LUNGHEZZA_MAX_COMANDI   14                  // lunghezza massima della stringa di comando
#define INFINITO                ((uint)-1)
#define AggiungiGrafo           "AggiungiGrafo"
#define TopK                    "TopK"

#define HEAP                (*heap)                                                     // usa heap[0] per salvare lunghezza e dimensione
#define LEFT(n)             (2*(n))
#define RIGHT(n)            (2*(n)+1)
#define PARENT(n)           ((n)>>1)
#define SMALLER(a,b)        (heap[(a)].dist < heap[(b)].dist)
#define GREATER(a,b)        ((heap[(a)].dist > heap[(b)].dist) || ((heap[(a)].dist == heap[(b)].dist) && (heap[(a)].labl > heap[(b)].labl)))
#define SWAP(a,b)           {Nodo C = heap[(a)]; heap[(a)] = heap[(b)]; heap[(b)] = C;}

//  Utilizza la stessa definizione sia per i dati che per i metadati
typedef union{
    struct{
        uint dist;
        uint labl;
    };
    struct{
        uint length;
        uint size;
    };
}Nodo;
typedef Nodo* Heap;

uint**  allocaMatrice(uint dim);
uint**  liberaMatrice(uint** matrice, uint dim);
void    riempiMatrice(uint** matrice, uint dim);
void    stampaMatrice(uint** matrice, uint dim);
uint    calcolaMinSpanTree(uint** matrice, Heap heap, uint dim);
Heap    allocaHeap(uint dim);
Heap    liberaHeap(Heap heap);
void    costruisciMinHeap(Heap heap);
void    cleanHeap(Heap heap);
void    minHeapify(Heap heap, uint n);
uint    cancellaMin(Heap heap, Nodo* ret);
void    decrementaPri(Heap heap, uint i);
void    incrementaPri(Heap heap, uint i);
void    stampaHeap(Heap heap);
void    stampaResiduo(Heap heap);
uint    DijkstraQueue(uint** matrice, Heap heap, uint dim);
uint    DijkstraQuad(uint** matrice, Heap heap, uint dim);
void    costruisciMaxHeap(Heap heap);
void    maxHeapify(Heap heap, uint n);
Nodo*   heapMax(Heap heap);
uint    cancellaMax(Heap heap);
void    inserisciMaxHeap(Heap heap, uint labl, uint dist);
uint    inserisciFuoriOrdine(Heap heap, uint labl, uint dist);
void    outHeap(Heap heap);

int main(){
    uint    indice = 0, peso_grafo;
    uint    numero_nodi;
    uint    K;
    char    comando[LUNGHEZZA_MAX_COMANDI];
    uint**  matrice_adiacenza;
    Heap    heap_supporto;
    Heap    heap_classifica;

    if(scanf("%u %u\n", &numero_nodi, &K) == EOF) return 1; 
    //printf("Nodi: %u, Classifica: %u\n", numero_nodi, lunghezza_classifica);
    matrice_adiacenza = allocaMatrice(numero_nodi);
    heap_supporto     = allocaHeap(numero_nodi-1);                                    // heap non deve contenere il nodo 0
    heap_classifica   = allocaHeap(K+1);                                              // guess I'll die

    while(scanf("%s\n", comando) != EOF){
        if(! strncmp(comando, AggiungiGrafo, LUNGHEZZA_MAX_COMANDI)){
            riempiMatrice(matrice_adiacenza, numero_nodi);
            //printf("%4u %u\n", indice, calcolaMinSpanTree(matrice_adiacenza, heap_supporto, numero_nodi));
            peso_grafo = calcolaMinSpanTree(matrice_adiacenza, heap_supporto, numero_nodi);
            if(indice < K){
                //printf("indice:%u K:%u\n", indice, K);
                inserisciFuoriOrdine(heap_classifica, indice, peso_grafo);
            }else{
                if(indice == K){
                    costruisciMaxHeap(heap_classifica);
                    //stampaHeap(heap_classifica);
                }
                inserisciMaxHeap(heap_classifica, indice, peso_grafo);
                cancellaMax(heap_classifica);
            }
            indice++;
        }else if(! strncmp(comando, TopK, LUNGHEZZA_MAX_COMANDI)){
            outHeap(heap_classifica);
        }else return 1;                                                               // comando inatteso
    }
    heap_classifica   = liberaHeap(heap_classifica);
    heap_supporto     = liberaHeap(heap_supporto);
    matrice_adiacenza = liberaMatrice(matrice_adiacenza, numero_nodi);
}

/************* matrice di adiacenza ********************/

uint** allocaMatrice(uint dim){
    uint** tmp;
    tmp = (uint**) malloc(dim*sizeof(uint*));
    for(int i=0; i<dim; i++){
        tmp[i] = (uint*) malloc(dim*sizeof(uint));
    }
    return tmp;
}

uint** liberaMatrice(uint** matrice, uint dim){
    for(int i=0; i<dim; i++){
        free(matrice[i]);
    }
    free(matrice);
    return NULL;
}

void riempiMatrice(uint** matrice, uint dim){
    uint val;
    char c;
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            val = 0;
            c=getchar_unlocked();
            while(c!=',' && c != '\n'){
                val = val*10 + c - '0';
                c=getchar_unlocked();
            }
            matrice[i][j] = val;
            if(!matrice[i][j]) matrice[i][j] = INFINITO;
        }
    }
}

void stampaMatrice(uint** matrice, uint dim){
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            if(matrice[i][j] == INFINITO){
                printf("  inf ");
            }else{
                printf("%5u ", matrice[i][j]);
            }
        }
        printf("\n");
    }
}

/************* calcolo minimum spanning tree ************/

uint calcolaMinSpanTree(uint** matrice, Heap heap, uint dim){
    cleanHeap(heap);
    for(uint i=1; i<dim; i++)
        inserisciFuoriOrdine(heap, i, matrice[0][i]);
    costruisciMinHeap(heap);
    return DijkstraQueue(matrice, heap, dim);
    //return DijkstraQuad(matrice, heap, dim);
}

uint DijkstraQueue(uint** matrice, Heap heap, uint dim){
    uint ret = 0;
    Nodo tmp;
    while (cancellaMin(heap, &tmp) && tmp.dist < INFINITO){
        for(uint i=1; i<=HEAP.size; i++){
            uint step = matrice[tmp.labl][heap[i].labl];
            if(step < INFINITO && tmp.dist + step < heap[i].dist){
                heap[i].dist = tmp.dist + step;
                decrementaPri(heap, i);
            }
        }
        heap[HEAP.size+1] = tmp;
    }
    for(uint i=HEAP.size+1; i<=HEAP.length; i++){
        if(heap[i].dist != INFINITO)                // NON TOGLIERE QUESTO CONFRONTO (necessario per impossibilità di riconoscere causa di uscita dal while)
            ret += heap[i].dist;
    }
    return ret;
}

uint DijkstraQuad(uint** matrice, Heap heap, uint dim){
    uint ret = 0;
    uint distTmp = 0;
    uint min = 1;
    uint mindist = INFINITO;
    while(1){
        uint checkAllZeroOrInfinite = 0;
        for(uint i=1; i<dim && !checkAllZeroOrInfinite; i++){
            if(heap[i].dist != 0 && heap[i].dist != INFINITO){
                checkAllZeroOrInfinite = 1;
            }
        }
        if(!checkAllZeroOrInfinite) return ret;
        for(uint i=1; i<dim; i++){
            if(heap[i].dist != 0 && heap[i].dist < mindist){        // ignorare nodi rimossi
                min = i;                                            // aggiorna max
                mindist = heap[min].dist;                           // e il suo valore
            }
        }
        ret += heap[min].dist;                                       // salva cammino minimo
        distTmp = heap[min].dist;                                    // salva dist per calcolo
        heap[min].dist = 0;                                          // rimuovi nodo
        mindist = INFINITO;                                          // riprepara per prossimo ciclo
        for(uint i=1; i<dim; i++){
            if(i != min && heap[i].dist != 0){                       // ignora autoanelli e nodi rimossi
                uint step = matrice[min][i];
                if(distTmp + step < heap[i].dist && step < INFINITO){
                    heap[i].dist = distTmp + step;
                }
            }
        }
    }
}

/********************* heap *****************************/

Heap allocaHeap(uint dim){
    Heap tmp = (Heap) malloc((dim+1)*sizeof(Nodo));  // rende lo heap 1-based e utilizza heap[0] per salvare lunghezza e dimensione
    tmp[0].length = dim;
    tmp[0].size   = 0;
    return tmp;
}

Heap liberaHeap(Heap heap){
    free(heap);
    return NULL;
}

void costruisciMinHeap(Heap heap){
    for(int i=(HEAP.size)>>1; i>0; i--){
        minHeapify(heap, i);
    }
}

void minHeapify(Heap heap, uint n){
    uint l = LEFT(n);
    uint r = RIGHT(n);
    uint posmin;
    if(l <= HEAP.size && SMALLER(l,n))
        posmin = l;
    else posmin = n;
    if(r <= HEAP.size && SMALLER(r,posmin))
        posmin = r;
    if(posmin != n){
        SWAP(n, posmin);
        minHeapify(heap, posmin);
    }
}

uint cancellaMin(Heap heap, Nodo* ret){
    if(HEAP.size < 1){
        return 0;               // non è stato cancellato alcun valore poichè lo hep è vuoto
    }
    *ret = heap[1];
    heap[1] = heap[HEAP.size];
    //printf("Heap: pop di: (%u, %u)\n", ret->labl, ret->dist);
    HEAP.size--;
    minHeapify(heap, 1);
    return 1;                   // un elemento è stato cancellato
}

void decrementaPri(Heap heap, uint i){
    while(i > 1 && SMALLER(i, PARENT(i))){
        SWAP(PARENT(i),i);
        i = PARENT(i);
    }
}

void incrementaPri(Heap heap, uint i){
    while(i > 1 && GREATER(i, PARENT(i))){
        SWAP(PARENT(i),i);
        i = PARENT(i);
    }
}

void stampaHeap(Heap heap){
    printf("\n");
    for(int i=1; i<=HEAP.size; i++){
        printf("[%3u,%10u]\n", heap[i].labl, heap[i].dist);
    }
}

void stampaResiduo(Heap heap){
    if(HEAP.size == HEAP.length) return;
    for(int i=HEAP.size+1; i<=HEAP.length; i++){
        printf("(%3u,%10u)\n", heap[i].labl, heap[i].dist);
    }
}

void costruisciMaxHeap(Heap heap){
    for(int i=(HEAP.size)>>1; i>0; i--){
        maxHeapify(heap, i);
    }
}

void maxHeapify(Heap heap, uint n){
    uint l = LEFT(n);
    uint r = RIGHT(n);
    uint posmax;
    if(l <= HEAP.size && GREATER(l, n))
        posmax = l;
    else posmax = n;
    if(r <= HEAP.size && GREATER(r, posmax))
        posmax = r;
    if(posmax != n){
        SWAP(n, posmax);
        maxHeapify(heap, posmax);
    }
}

Nodo* heapMax(Heap heap){
    return &heap[1];
}

uint cancellaMax(Heap heap){
    if(HEAP.size < 1){
        return 0;               // non è stato cancellato alcun valore poichè lo hep è vuoto
    }
    heap[1] = heap[HEAP.size];
    HEAP.size--;
    maxHeapify(heap, 1);
    return 1;                   // un elemento è stato cancellato
}

void inserisciMaxHeap(Heap heap, uint labl, uint dist){
    uint i = ++HEAP.size;
    heap[i] = (Nodo){.labl = labl, .dist = dist};
    incrementaPri(heap, i);
}

uint inserisciFuoriOrdine(Heap heap, uint labl, uint dist){
    if(HEAP.size < HEAP.length){
        heap[++HEAP.size] = (Nodo){.labl = labl, .dist = dist};
        //printf("<%u, %u>\n", labl, dist);
        return 1;
    }
    else return 0;
}

void cleanHeap(Heap heap){
    heap[0].size = 0;
}
void outHeap(Heap heap){
    if(!heap->size){printf("\n"); return;}
    uint i;
    for(i=1; i<heap->size; i++){
        printf("%u ", heap[i].labl);
    }
    printf("%u\n", heap[i].labl);
}