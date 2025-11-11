#include "stdio.h"
#include "graph.h"


int main(){
	FILE *fp = fopen("grafo.txt","r");

	Graph g = GRAPHload(fp);
	
	FILE *fp1 = fopen("sol.txt","r");
	Graph sol = SOLload(fp1);

	printf("---Grafo---------\n");
	GRAPHprint(g);
	printf("---Sol-----------\n");
	GRAPHprint(sol);
	printf("-----------------\n");
	
	int ntpcking = countTrianglePackings(sol);
	printf("Trovati un totale di %d Triangle Packings\n", ntpcking);
	
	ntpcking = countTrianglePackings(g);
	printf("Trovati un totale di %d Triangle Packings\n", ntpcking);
	
	GRAPHfree(sol);
	GRAPHfree(g);

	fclose(fp1);
	fclose(fp);

	return 0;
}



