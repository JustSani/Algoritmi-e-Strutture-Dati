#include "stdio.h"
#include "buffer.h"


int main(){

	FILE * gridfp = fopen("grid.txt", "r");
	FILE * bonusfp = fopen("bonus.txt", "r");
	//FILE * bonusfp = fopen("grid.txt", "r");
	
	int L = 5;
	
	GRID grid = gridInit(gridfp);
	printf("- Grid ------------------\n");
	gridPrint(grid);

	int nBonus;
	BUFFER * bonus = bonusLoad(bonusfp, &nBonus);
	printf("- Bonuses ---------------\n");
	bonusPrint(bonus, nBonus);
	

	printf("-------------------------\n");
	int check = checkBuffer(L,bonus[0],grid);
	if(check)
		printf("BUFFER valido\n");
	else
		printf("BUFFER NON valido\n");

	MARK mark = markInit(3);



	printf("- Soluzioni -------------\n");
	BUFFER soluzione = bufferInit(L);
	int punteggioMax = 0;
	recursiveSoluzione(L,0,0,0, soluzione, grid, bonus,nBonus, &punteggioMax, mark);
	//markPrint(mark);



	markFree(mark);
	bufferFree(soluzione);
	bonusFree(bonus,nBonus);
	gridFree(grid);

	fclose(gridfp);	
	fclose(bonusfp);

	return 0;

}