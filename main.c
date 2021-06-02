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

#define HEAP            (*heap)                                                     // usa heap[0] per salvare lunghezza e dimensione
#define LEFT(n)         (2*(n))
#define RIGHT(n)        (2*(n)+1)
#define PARENT(n)       ((n)>>1)
#define SMALLER(a,b)    (heap[(a)].dist < heap[(b)].dist)                           // per tenere separato il criterio di ordinamento
#define SWAP(a,b)       {Nodo C = heap[(a)]; heap[(a)] = heap[(b)]; heap[(b)] = C;}

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

typedef union NodoLista{
    struct{
        uint peso;
        union NodoLista* next;
    };
    struct{
        uint length;
        union NodoLista* first;
    };
}nodoLista;
typedef nodoLista* Pila;

uint**  allocaMatrice(uint dim);
uint**  liberaMatrice(uint** matrice, uint dim);
void    riempiMatrice(uint** matrice, uint dim);
void    stampaMatrice(uint** matrice, uint dim);
uint    calcolaMinSpanTree(uint** matrice, Heap heap, uint dim);
Heap    allocaHeap(uint dim);
Heap    liberaMinHeap(Heap heap);
void    costruisciMinHeap(Heap heap);
void    minHeapify(Heap heap, uint n);
void    controllaMin(Heap heap, Nodo* ret);
uint    cancellaMin(Heap heap, Nodo* ret);
void    decrementaPri(Heap heap, uint i);
void    inserisciHeap(Heap heap, uint labl, uint dist);
void    stampaMinHeap(Heap heap);
void    stampaResiduo(Heap heap);
uint    DijkstraQueue(uint** matrice, Heap heap, uint dim);
uint    DijkstraQuad(uint** matrice, Heap heap, uint dim);
Pila    creaPila();
void    pushPila(Pila pila, uint val);
uint    popPila(Pila pila);
uint    dimensionePila(Pila);

int main(){
    uint    indice = 0, heap_top = 0;
    uint    peso_grafo;
    uint    numero_nodi;
    uint    K;
    char    comando[LUNGHEZZA_MAX_COMANDI];
    uint**  matrice_adiacenza;
    Heap    heap_supporto;
    Heap    heap_classifica;
    Pila    top_pila;
    //*leggere i valori di dimensione dei grafi e della lunghezza della classifica
    //*leggere comando
    //*se "AggiungiGrafo":
    //*     riempi la matrice di adiacenza coi valori inseriti
    //*     calcola l'albero dei cammini minimi
    //      se #grafi < dimensione top:
    //          push grafo
    //      se #grafi > dimensione top:
    //          copia pila su max heap
    //          ordina heap
    //          se peso nuovo grafo < peso max:
    //              rimuovi max, e aggiungi nuovo (con rispettive max heapyfy e bubble up)
    //*se "TopK":
    //      se #grafi < dimensione top:
    //          stampa lista
    //      se #grafi > dimensione top
    //          stampa heap
    //*se sconosciuto o finiti gli input esci altrimenti leggi nuovo comando

    if(scanf("%u %u\n", &numero_nodi, &K) == EOF) return 1; 
    //printf("Nodi: %u, Classifica: %u\n", numero_nodi, lunghezza_classifica);
    matrice_adiacenza = allocaMatrice(numero_nodi);
    heap_supporto     = allocaHeap(numero_nodi-1);                                    // heap non deve contenere il nodo 0
    top_pila          = creaPila();

    while(scanf("%s\n", comando) != EOF){
        if(! strncmp(comando, AggiungiGrafo, LUNGHEZZA_MAX_COMANDI)){
            riempiMatrice(matrice_adiacenza, numero_nodi);                          // stampaMatrice(matrice_adiacenza, numero_nodi);
            //printf("%4u %u\n", indice, calcolaMinSpanTree(matrice_adiacenza, heap_supporto, numero_nodi));
            peso_grafo = calcolaMinSpanTree(matrice_adiacenza, heap_supporto, numero_nodi);
            if(indice < K){
                pushPila(top_pila, peso_grafo);
            }else if(indice == K){
                heap_classifica = allocaHeap(K);
                heap_top = 1;
            }
            indice++;
        }else if(! strncmp(comando, TopK, LUNGHEZZA_MAX_COMANDI)){
            while(dimensionePila(top_pila)){
                printf("Pop da pila (%u): %u\n", --indice, popPila(top_pila));
            }
        }else return 1;                                                             // comando inatteso
    }
    if(heap_top){
        free(heap_classifica);
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
            if(scanf("%u,", &matrice[i][j]));
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
    for(uint i=1; i<dim; i++){
        heap[i] = (Nodo){.labl = i, .dist = matrice[0][i]};
    }
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
    return tmp;
}

Heap liberaMinHeap(Heap heap){
    free(heap);
    return NULL;
}

void costruisciMinHeap(Heap heap){
    HEAP.size = HEAP.length;
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

void controllaMin(Heap heap, Nodo* ret){
    *ret = heap[1];
}

uint cancellaMin(Heap heap, Nodo* ret){
    if(HEAP.size < 1){
        return 0;               // non è stato cancellato alcun valore poichè lo hep è vuoto
    }
    *ret = heap[1];
    heap[1] = heap[HEAP.size];
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

void inserisciHeap(Heap heap, uint labl, uint dist){
    uint i = ++HEAP.size;
    heap[i] = (Nodo){.labl = labl, .dist = dist};
    decrementaPri(heap, i);
}

void stampaMinHeap(Heap heap){
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

Pila creaPila(){
    Pila pila = (Pila) malloc(sizeof(nodoLista));
    pila->length = 0;
    pila->next = NULL;
    return pila;
}

void pushPila(Pila pila, uint valore){
    nodoLista* nodo = (nodoLista*) malloc(sizeof(nodoLista));
    nodo->peso = valore;
    nodo->next = pila->first;
    pila->first = nodo;
    pila->length++;
}

uint popPila(Pila pila){
    uint ret = pila->first->peso;
    nodoLista* ToS = pila->first->next;
    free(pila->first);
    pila->first = ToS;
    pila->length--;
    return ret;
}

uint dimensionePila(Pila pila){
    return pila->length;
}