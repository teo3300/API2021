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

