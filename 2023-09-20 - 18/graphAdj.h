#include "stdio.h"
#include "malloc.h"

typedef struct graph * GRAPH;
GRAPH GraphLoad(FILE *fp);
void GraphPrint(GRAPH g);
void GraphFree(GRAPH g);
int GraphCheckSol(GRAPH g, GRAPH sol, int k);