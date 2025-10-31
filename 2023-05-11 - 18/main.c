#include "stdio.h"
#include "graph.h"


int main(){
	FILE *fp = fopen("grafo.txt","r");

	Graph g = GRAPHload(fp);
	
	FILE *fp1 = fopen("sol.txt","r");
	Graph sol = SOLload(fp1);

	GRAPHprint(g);
	GRAPHprint(sol);


	GRAPHfree(sol);
	GRAPHfree(g);

	fclose(fp1);
	fclose(fp);

	return 0;
}



