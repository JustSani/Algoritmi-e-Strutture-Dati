#include "stdio.h"
#include "malloc.h"

typedef struct graph *GRAPH;
typedef struct tree_partition * TPARTITION;
typedef struct tree_partition_array * TPARTARRAY;


GRAPH graphRead(FILE *fp);
void graphFree(GRAPH g);
void graphPrint(GRAPH g);