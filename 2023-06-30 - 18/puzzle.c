#include <stdio.h>
#include <stdlib.h>
#include "puzzle.h"
#include "math.h"


struct puzzle {
	int ** schede;    	
    	int N;
	int T;
};

PUZZLE PUZZLEload(FILE *fp) {
    	int i, j;
	int card[4];
	int sum;
    	PUZZLE p = malloc(sizeof(struct puzzle));
	fscanf(fp, "%d %d\n", &p->N, &p->T);
	int nCards = p->N * p->N;

	
	p->schede = malloc(sizeof(int *) * nCards);

	
	for(i = 0; i < nCards; i++){
		p->schede[i] = malloc(sizeof(int) * 4);
		for(j = 0; j < 4; j++){
			fscanf(fp, "%d",&(p->schede[i][j]));
			fgetc(fp);
		}
	}

	
    	return p;
}

void PUZZLEfree(PUZZLE p) {
    	int i;
	for(i = 0; i < p->N * p->N; i++){
		free(p->schede[i]);
	}
    	free(p->schede);

    	free(p);
}

void PUZZLEprint(PUZZLE p) {
    	int i, j;
    	printf("%d %d\n", p->N, p->T);
    	for (i = 0; i < p->N * p->N; i++) {
        	for (j = 0; j < 4; j++) {
        		printf("%d ", p->schede[i][j]);
        	}
        	printf("\n");
    	}
}


char * SOLload(FILE *fp2, int *size){
	fscanf(fp2,"%d\n", size);
	char * sol = malloc(sizeof(char)* (*size));
	for(int i = 0; i < *size; i++){
		fscanf(fp2, "%c ", &(sol[i]));
	}
	return sol;
}


void SOLfree(char *sol){
	free(sol);
}

void SOLprint(char *sol, int size){
	for(int i = 0; i < size; i++)
		printf("%c ", sol[i]);
	printf("\n");
}

int isCardEmpty(int* scheda){
	if(scheda[0] == 0 && scheda[1] == 0 && scheda[2] == 0 && scheda[3] == 0)
		return 1;
	return 0;
}
void switchCards(PUZZLE p,int CardToEmpty,int CardToFill){
	int i;
	for(i = 0; i < 4; i++){
		p->schede[CardToFill][i] = p->schede[CardToEmpty][i];
		p->schede[CardToEmpty][i] = 0; 
	}

}

int isHead(int *scheda){
	int i = 0, count = 0;
	for(i = 0; i < 4; i++)
		if(scheda[i] == 1)
			count ++;
	if(count == 1) return 1;
	return 0;
}


int CHECKsol(PUZZLE p, char *sol, int N){
	int i, j, k;
	int movement;
	
	// numero di righe della matrice
	int r = p->N;
	
	// numero di carte vuote
	int mCN= (p->N * p->N)/p->T;
	// vettori rispettivamente col i esimo elemento della 
	int CardToEmpty[mCN], CardToFill[mCN];
	int movingCardsCounter;
	for(k = 0; k < N; k++){
		movement = 0;
		movingCardsCounter = 0;
		for(i = 0; i < r; i++){
			for(j = 0; j < r; j++){
				switch (sol[k]){
					case 'N':
						if(i != 0 && !isCardEmpty(p->schede[r*i + j] && isCardEmpty(p->schede[r * (i-1) + j]){
							CardToEmpty[movingCardsCounter] = r*i + j;
							CardToFill[movigCardsCounter] = r*(i-1) + j;
							movigCardsCounter++;
							movement++;
						}
					break;
					case 'E':
						if(j != r && !isCardEmpty(p->schede[r*i + j] && isCardEmpty(p->schede[r*i + j + 1]){
							CardToEmpty[movingCardsCounter] = r*i + j;
							CardToFill[movigCardsCounter] = r*i + j + 1;
							movigCardsCounter++;
							movement++;
						} 
					break;
					case 'O':
						if(j != 0 && !isCardEmpty(p->schede[r*i + j] && isCardEmpty(p->schede[r*i + j - 1]){
							CardToEmpty[movingCardsCounter] = r*i + j;
							CardToFill[movigCardsCounter] = r*i + j - 1;
							movigCardsCounter++;
							movement++;
						} 
					break;
					case 'S':
						if(i != r && !isCardEmpty(p->schede[r*i + j] && isCardEmpty(p->schede[r*(i+1) + j]){
							CardToEmpty[movingCardsCounter] = r*i + j;
							CardToFill[movigCardsCounter] = r*(i+1) + j;
							movigCardsCounter++;
							movement++;
						} 
					break;
					case default:
						return 0;
					break;
				}			
			}
			if(movement == 0) return 0;
			for(j = 0; j < mCN; j++){
					switchCards(p, CardToEmpty[j], CardToFill[j]);
			}
		}
	}


	// siamo nell ordinamento finale, ora verichiamo se il labirinto si completa

	// cerchiamo una testa
	i = 0;
	while(!isHead(p->schede[i])){
		i++;
	}

	// controlliamo se la testa si connette alla prossima
	return checkConnection(p, i, -1);
}

int checkConnection(PUZZLE p, int node, -1){
	int i;
	int vet[4] = {0,0,0,0};
	for(i = 0; i < 4; i++){
		vet[i] = checkConnection(PUZZLE p, int 
	}
	if(p->scheda[node][0])
	}
}



