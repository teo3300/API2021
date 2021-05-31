#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define uint                    unsigned int        // abbreviazione unsigned int
#define LUNGHEZZA_MAX_COMANDI   14                  // lunghezza massima della stringa di comando
#define INFINITO                ((uint)-1)
#define AggiungiGrafo           "AggiungiGrafo"
#define TopK                    "TopK"

typedef union{
    struct{
        uint labl;
        uint dist;
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
Heap    allocaMinHeap(uint dim);
Heap    liberaMinHeap(Heap heap);
void    costruisciMinHeap(Heap heap);
void    minHeapify(Heap heap, uint n);
void    controllaMin(Heap heap, Nodo* ret);
uint    cancellaMin(Heap heap, Nodo* ret);
void    inserisciHeap(Heap heap, uint labl, uint dist);
void    stampaMinHeap(Heap heap);

int main(){
    uint    numero_nodi;
    uint    lunghezza_classifica;
    char    comando[LUNGHEZZA_MAX_COMANDI];
    uint**  matrice_adiacenza;
    Heap    heap_supporto;
    //*leggere i valori di dimensione dei grafi e della lunghezza della classifica
    //*leggere comando
    //*se "AggiungiGrafo":
    //*     riempi la matrice di adiacenza coi valori inseriti
    //      calcola l'albero dei cammini minimi
    //      aggiorna la classifica
    //*se "TopK":
    //      stampa la classifica
    //*se sconosciuto o finiti gli input esci altrimenti leggi nuovo comando

    scanf("%u %u\n", &numero_nodi, &lunghezza_classifica);  //printf("Nodi: %u, Classifica: %u\n", numero_nodi, lunghezza_classifica);
    matrice_adiacenza = allocaMatrice(numero_nodi);
    heap_supporto     = allocaMinHeap(numero_nodi-1);       // heap non deve contenere il nodo 0


    while(scanf("%s\n", comando) != EOF){
        if(! strncmp(comando, AggiungiGrafo, LUNGHEZZA_MAX_COMANDI)){
            riempiMatrice(matrice_adiacenza, numero_nodi); //stampaMatrice(matrice_adiacenza, numero_nodi);
            calcolaMinSpanTree(matrice_adiacenza, heap_supporto, numero_nodi);
        }else if(! strncmp(comando, TopK, LUNGHEZZA_MAX_COMANDI)){

        }
    }
    heap_supporto     = liberaMinHeap(heap_supporto);
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
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            scanf("%u,", &matrice[i][j]);
        }
    }
}

void stampaMatrice(uint** matrice, uint dim){
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            printf("%5u ", matrice[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/************* calcolo minimum spanning tree ************/

uint calcolaMinSpanTree(uint** matrice, Heap heap, uint dim){
    for(uint i=1; i<dim; i++){
        if(matrice[0][i])
            heap[i] = (Nodo){i, matrice[0][i]};
        else
            heap[i] = (Nodo){i, -1};
    }
    costruisciMinHeap(heap);
    //stampaMinHeap(heap);
}

/********************* heap *****************************/

Heap allocaMinHeap(uint dim){
    Heap tmp = (Heap) malloc((dim+1)*sizeof(Nodo));  // rende lo heap 1-based e utilizza heap[0] per salvare lunghezza e dimensione
    tmp[0].length = dim;
    return tmp;
}

Heap liberaMinHeap(Heap heap){
    free(heap);
    return NULL;
}

void costruisciMinHeap(Heap heap){
    heap[0].size = heap[0].length;
    for(int i=(heap[0].size)>>1; i>0; i--){
        minHeapify(heap,i);
    }
}

#define LEFT(n)         (2*(n))
#define RIGHT(n)        (2*(n)+1)
#define PARENT(n)       ((n)>>1)
#define SMALLER(a,b)    (heap[(a)].dist < heap[(b)].dist)                           // per tenere separato il criterio di ordinamento
#define SWAP(a,b)       {Nodo C = heap[(a)]; heap[(a)] = heap[(b)]; heap[(b)] = C;}
/*void swap(Heap heap, uint a, uint b){
  /*Nodo C  =       {heap[a].labl, heap[a].dist};
    heap[a] = (Nodo){heap[b].labl, heap[b].dist};
    heap[b] = (Nodo){      C.labl,       C.dist};
}*/

void minHeapify(Heap heap, uint n){
    uint l = LEFT(n);
    uint r = RIGHT(n);
    uint posmin;
    if(l <= heap[0].size && SMALLER(l,n))
        posmin = l;
    else posmin = n;
    if(r <= heap[0].size && SMALLER(r,posmin))
        posmin = r;
    if(posmin != n){
        SWAP(n, posmin);
        minHeapify(heap, posmin);
    }
}

void controllaMin(Heap heap, Nodo* ret){
    *ret = heap[1];
    //*ret = (Nodo){heap[1].labl, heap[1].dist};
}

uint cancellaMin(Heap heap, Nodo* ret){
    if(heap[0].size < 1)
        return 0;               // non è stato cancellato alcun valore poichè lo hep è vuoto
    *ret = heap[1];
    heap[1] = heap[heap[0].size];
    //*ret = (Nodo){heap[1].labl, heap[1].dist};
    //heap[1] = (Nodo){heap[heap[0].size].labl, heap[heap[0].size].dist};
    heap[0].size--;
    minHeapify(heap, 1);
    return 1;                   // un elemento è stato cancellato
}

void inserisciHeap(Heap heap, uint labl, uint dist){
    uint i = ++heap[0].size;
    heap[i] = (Nodo){labl, dist};
    while(i > 1 && SMALLER(PARENT(i), i)){
        SWAP(PARENT(i),i);
        i = PARENT(i);
    }
}

void stampaMinHeap(Heap heap){
    printf("Size:   %u\nLength: %u\n", heap[0].size, heap[0].length);
    for(int i=1; i<=heap[0].size; i++){
        printf("<%u, %u>\n", heap[i].labl, heap[i].dist);
    }
    printf("\n");
}