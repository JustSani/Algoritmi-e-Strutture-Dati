#include "stdio.h"
#include "graph.h"


int main(){
	FILE *fp = fopen("grafo.txt","r");

	Graph g = GRAPHload(fp);


	GRAPHprint(g);



	GRAPHfree(g);
	fclose(fp);

	return 0;
}



