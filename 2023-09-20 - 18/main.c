#include "stdio.h"
#include "graphAdj.h"

int main(){
	
	FILE *fp = fopen("grafo.txt", "r");
	
	GRAPH g = GraphLoad(fp);
	
	FILE *fp2 = fopen("sol.txt", "r");
	GRAPH sol = GraphLoad(fp2);
	
	
	GraphPrint(g);
	GraphPrint(sol);
	int check = GraphCheckSol(g, sol, 3);
	printf("\ncheck: %d\n",check);
	GraphFree(g);
	GraphFree(sol);
	fclose(fp2);
	fclose(fp);

	return 0;

}