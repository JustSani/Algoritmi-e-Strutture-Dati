#include "stdio.h"
#include "puzzle.h"

int main(){
	FILE *fp = fopen("grid.txt", "r");
	printf("--grid.txt-----------\n");
	PUZZLE p = PUZZLEload(fp);
	
	PUZZLEprint(p);

	FILE *fp2 = fopen("sol.txt", "r");
	int size;
	char *sol = SOLload(fp2, &size);
	printf("--sol.txt------------\n");
	SOLprint(sol,size);
	printf("--PUZZLE-------------\n");
	PUZZLEprintReadable(p);

	printf("--checkSol-----------\n");
	int chk = CHECKsol(p, sol, size);
	
	printf("check return: %d",chk);
	
	SOLfree(sol);
	PUZZLEfree(p);
	fclose(fp);
	fclose(fp2);
	return 0;
}