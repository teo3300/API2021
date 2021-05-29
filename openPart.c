uint nodes_cnt;                                                         // perdoname madre por mi variable non locale (da usare in ind(y,x))

void parse();

int main(){
    uint topK,
         cnt = 0;
    char command_buffer[COMMAND_BUFF_LEN];                              // temporaneo tampone per distinguere i comandi
    scanf("%u %u\n",&nodes_cnt, &topK);
    //PRINT(nodes_cnt);
    //PRINT(topK);

    uint graph_matrix[nodes_cnt*nodes_cnt];                             // salva la matrice di incidenza come un VLA

    while(scanf("%s\n", command_buffer)>0){
        if((*command_buffer) == 'A'){
            cnt++;
            for(int i=0; i<nodes_cnt; i++){
                for(int j=0; j<nodes_cnt; j++){
                    parse(adr(graph_matrix,i,j));
                    //parse(&graph_matrix[ind(i,j)]);                     // TODO: si può migliorare ancora?
                    //printf("%5u ", graph_matrix[ind(i,j)]);
                }
            //printf("\n");
            }
            //printf("\n");
        }else if((*command_buffer) == 'T'){
            
        }
    }
    return 0;
}

void parse(uint* ret){                                                  // scanf merda
    *ret=0;
    int c = getchar();
    while(c != '\n' && c != ','){
        *ret = (*ret)*10 + c -'0';
        c = getchar();
    }
}

/********** OpenPart.c **********/

