#include "graph.h"
#include "malloc.h"

struct graph{
	int V;
	int E;
	int **matj;
};


Graph GRAPHinit(int v){
	Graph g = malloc(sizeof(Graph*));
	g->V = v;
	g->matj = malloc(sizeof(int *)*v);

	for(int i = 0; i < v; i++){
		g->matj[i] = malloc(sizeof(int)*v);
		for(int j=0; j < v; j++){
			g->matj[i][j] = 0;
		}
	}
	return g;
}

void GRAPHfree(Graph g){
	for(int i = 0; i < g->V; i++){
		free(g->matj[i]);
	}
	free(g->matj);

	free(g);
}

Graph GRAPHload(FILE *fin){
	int v, v1,v2, e = 0;
	fscanf(fin, "%d\n",&v);
	Graph g = GRAPHinit(v);
	while(!feof(fin)){
		fscanf(fin,"%d,%d\n",&v1,&v2);

		g->matj[v1][v2] = 1;
		g->matj[v2][v1] = 1;

		e++;
	}
	return g;
	
}

void GRAPHprint(Graph g){
	int i,j;
	printf("/ ");
	for(i = 0; i < g->V; i++) printf("%d ",i);
	printf("\n");
	for(i = 0;i < g->V; i++){
		printf("%d ",i);
		for(j = 0; j < g->V;j++)
			printf("%d ", g->matj[i][j]);
		printf("\n");
	}
}



Graph SOLload(FILE * file){
	int i,j, v;

	fscanf(file,"%d\n", &v);
	Graph sol = malloc(sizeof(Graph*));
	sol->matj = malloc(sizeof(int*)*v);
	sol->V = v;
	for(i = 0; i < v; i++){
		sol->matj[i] = malloc(sizeof(int) * v);
		
		for(j = 0; j < v; j++){
			fscanf(file, "%d ",&sol->matj[i][j]);	
		}
	}
	return sol;

}

int SOLcheck(Graph sol){
	int i,j,k,error;


	for(i=0;i< sol->V; i++)
		for(j = 0; j < sol->V; j++){
			if(i<j){
				if(sol->matj[i][j] > 0){
					k = 0;
					error = 1
					for(k = 0; k < 	
				}	
			}
		}
	
	
	return 0;
}

