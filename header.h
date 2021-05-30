/********** joint with cat **********/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define uint unsigned int
#define COMMAND_BUFF_LEN 14

#define log
#define print

#define ind(y, x) ((y) * nodes_cnt + (x))                                 // usato per trattare vettore dei vertici come una matrice
#define adr(matrix, y, x)   ( (matrix) + (y) * nodes_cnt + (x))

/********** header.h **********/

