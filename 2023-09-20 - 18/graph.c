#include "graph.h"

struct graph{
	int **matj;
	int V;
	int E;
};


struct tree_partition{
	int **Edges;
	int n;
};

struct tree_partition_array{
	TPARTITION v;
	int n;
};

GRAPH graphRead(FILE *fp){
	int i,j, a1,a2,a3;
	GRAPH g = malloc(sizeof(struct graph));
	fscanf(fp,"%d\n", &g->V);
	g->matj = malloc(sizeof(int*)* g->V);
	for(i = 0; i < g->V; i++)
		g->matj[i] = malloc(sizeof(int)* g->V);
	for(i = 0; i < g->V; i++)
		for(j = 0; j < g->V; j++)
			g->matj[i][j] = 0;
	g->E = 0;
	while(fscanf(fp, "%d %d %d\n", &a1,&a2,&a3) == 3){
		//printf("%d %d %d\n",a1,a2,a3);
		g->matj[a1][a2] = a3;
		g->matj[a2][a1] = a3;
		g->E++;
	}
	return g;
	
}

void graphFree(GRAPH g){
	int i;
	for(i = 0; i < g->V; i++)
		free(g->matj[i]);
	free(g->matj);
	free(g);
}
void graphPrint(GRAPH g){
	int i, j;
	for(i = 0; i < g->V; i++){
		for(j = 0; j < g->V; j++)
			printf("%d ", g->matj[i][j]);
		printf("\n");
	}

}