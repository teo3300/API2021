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

