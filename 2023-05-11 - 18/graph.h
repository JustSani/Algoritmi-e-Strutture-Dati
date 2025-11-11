#include "stdio.h"

typedef struct edge {int v; int w;} Edge;
typedef struct graph *Graph;

Graph GRAPHinit(int v);
void GRAPHfree(Graph g);
Graph GRAPHload(FILE *fin);
void GRAPHprint(Graph g);
Graph SOLload(FILE * file);
int countTrianglePackings(Graph sol);