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

void PUZZLEprintReadable(PUZZLE p) {
    	int i, j, sum;
    	for (i = 0; i < p->N * p->N; i++) {
		if(i%p->N == 0 )
			printf("\n");
		sum = 0;
        	for (j = 0; j < 4; j++) {
			sum += p->schede[i][j] * pow(10,j);
        	}
		switch(sum){
			case 0:
				printf("  ");
			break;
			case 110:
				printf("\\ ");
			break;
			case 101:
				printf("/ ");
			break;
			case 1100:
				printf("- ");
			break;
			case 11:
				printf("| ");
			break;
			case 1010:
				printf("/ ");
				break;
			case 1001:
				printf("\\ ");
				break;
			default:
				printf("o ",sum);
			break;
				
		}

    	}
	printf("\n");
}



// direzionePrecedente: -1 (qualsiasi direzione), 0 Nord, 1 Sud, 2 Ovest, 3 Est
int checkConnection(PUZZLE p, int node, int direzionePrecedente){
	//printf("%d\n", node);
	int foundDirection = 0, recursiveCheck = 0;	
	int i, r = p->N;
	int k,l;

	k = node / r;
	l = node % r;	
	// caso terminale, la scheda è vuota;
	if(isCardEmpty(p->schede[r*k + l])){
		return  -4;
	}
	
	if(isHead(p->schede[node]) == 1 && direzionePrecedente != -1){
		for(i = 0; p->schede[node][i] != 1; i++);
		if(i == direzionePrecedente)
			return 1;
		else return -3;
	}

	for(i = 0; i < 4; i++){
		if(p->schede[node][i] == 1){
			// check se abbiamo trovato un allineamento
			if(i == direzionePrecedente){
				foundDirection = 1;
			}
			else{
				//printf("node: %d",node);
				//printf("i:%d\n",i);
				switch(i){
					case 0: //n
						//printf("yes");
						if(k != 0 && !isCardEmpty(p->schede[r * (k-1) + l])){
							//printf("yes");
							recursiveCheck = checkConnection(p, r *(k-1) + l, 1);
						}else printf("nope");
					break;
					case 1: //s
						if(k != r -1 && !isCardEmpty(p->schede[r*(k+1) + l])){
							recursiveCheck = checkConnection(p, r *(k+1) + l, 0);
						} 
					break;
					case 2: // o
						if(l != 0 && !isCardEmpty(p->schede[r*k + l - 1])) {
							recursiveCheck = checkConnection(p, r*k + l - 1, 3);
						} 
					break;
					case 3: //e
						if(l != r - 1 && !isCardEmpty(p->schede[r*k + l + 1])){

							recursiveCheck = checkConnection(p, r*k + l + 1, 2);
						}
					break;
				}
			}
		}
	}
	if(direzionePrecedente == -1)
		return recursiveCheck;
	if(foundDirection == 1 && recursiveCheck == 1)
		return 1;
	//printf("end: i= %d", i);
	return 0;
}


/* returns:
	-1: errore negli input (valori accettati NSEO)
	-2: Sequenza porta ad una certa al non cambio di stato del problema (si fa un movimento inutile che non cambia il problema tra una fase e l'altra)
	-3: La soluzione non è valida, non vi è connessione tra la testa di partenza e la fine

*/
int CHECKsol(PUZZLE p, char *sol, int N){
	int i, j, k;
	int movement;
	
	// numero di righe della matrice
	int r = p->N;
	
	// numero di carte vuote
	int mCN= (p->N * p->N) - p->T;
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
						if(i != 0 && !isCardEmpty(p->schede[r*i + j]) && isCardEmpty(p->schede[r * (i-1) + j])   ){
							CardToEmpty[movingCardsCounter] = r*i + j;
							CardToFill[movingCardsCounter] = r*(i-1) + j;
							movingCardsCounter++;
							movement++;
						}
					break;
					case 'E':
						if(j != r-1 && !isCardEmpty(p->schede[r*i + j]) && isCardEmpty(p->schede[r*i + j + 1])){
							CardToEmpty[movingCardsCounter] = r*i + j;
							CardToFill[movingCardsCounter] = r*i + j + 1;
							movingCardsCounter++;
							movement++;
						} 
					break;
					case 'O':
						if(j != 0 && !isCardEmpty(p->schede[r*i + j]) && isCardEmpty(p->schede[r*i + j - 1])){
							CardToEmpty[movingCardsCounter] = r*i + j;
							CardToFill[movingCardsCounter] = r*i + j - 1;
							movingCardsCounter++;
							movement++;
						}
					break;
					case 'S':
						if(i != r-1 && !isCardEmpty(p->schede[r*i + j]) && isCardEmpty(p->schede[r*(i+1) + j])){
							CardToEmpty[movingCardsCounter] = r*i + j;
							CardToFill[movingCardsCounter] = r*(i+1) + j;
							movingCardsCounter++;
							movement++;
						} 
					break;
					default:
						return -1;
					break;

				}
			}
		}
		if(movement == 0) return -2;

		for(j = 0; j < movement; j++){
			//printf("switching %d %d\n", CardToEmpty[j], CardToFill[j]);
			switchCards(p, CardToEmpty[j], CardToFill[j]);
		}
	}

	// siamo nell ordinamento finale, ora verichiamo se il labirinto si completa

	// cerchiamo una testa
	i = 0;
	while(!isHead(p->schede[i])){
		i++;
	}
	
	PUZZLEprint(p);
	PUZZLEprintReadable(p);

	// controlliamo se partendo dalla testa arriviamo alla coda
	return checkConnection(p, i, -1);
}
