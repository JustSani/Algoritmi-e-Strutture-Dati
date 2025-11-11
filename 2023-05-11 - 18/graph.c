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
	printf("  | ");
	for(i = 0; i < g->V; i++) printf("%d ",i);
	printf("\n--+");
	for(i = 0; i < g->V; i++)printf("--");
	printf("\n");
	for(i = 0;i < g->V; i++){
		printf("%d | ",i);
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

int isKalreadyInUse(int * solV,int n, int k){
	int i;
	for(i = 0; i < n; i++){
		if(solV[i] == k)
			return 1;
	}
	return 0;
} 

void recursiveCheckIfTriangle(Graph sol,int i, int j,int n,int* solV, int **mark, int *triangles){
	int c = 0, k;
	if (n == 3){
		if(j == i || sol->matj[j][i] == 1){
			mark[solV[0]][solV[1]] = 1;
			mark[solV[1]][solV[0]] = 1;
			mark[solV[1]][solV[2]] = 1;
			mark[solV[2]][solV[1]] = 1;
			mark[solV[2]][solV[0]] = 1;
			mark[solV[0]][solV[2]] = 1;
			for(k = 0; k < 3; k++)
				printf("%d ", solV[k]);
			printf("\n");
			(*triangles)++;
		}
	}
	else{
		for(k = 0; k < sol->V; k++){
			if(isKalreadyInUse(solV,n, k) == 0 && mark[j][k] == 0 && sol->matj[j][k] == 1){
				solV[n] = k;
				recursiveCheckIfTriangle(sol, i, k, n+1,solV, mark, triangles);
			}
		}
	}
}

int countTrianglePackings(Graph sol){
	int i,j,k,error;
	int numberOfTrianglePacking = 0;
	int **mark = malloc(sizeof(int *) * sol->V);
	int *solV = malloc(sizeof(int)* 3);

	for(i = 0; i < sol->V; i++){
		mark[i] = malloc(sizeof(int)* sol->V);
		for(j = 0; j < sol->V; j++){
			mark[i][j] = 0;
		}
	}

	
	for( i = 0; i < sol->V; i++){
		solV[0] = i;
		recursiveCheckIfTriangle(sol, i, i, 1,solV, mark, &numberOfTrianglePacking);
	}

	for(i = 0; i < sol->V; i++){	
		free(mark[i]);	
	}
	free(mark);
	free(solV);

	return numberOfTrianglePacking;
}


























