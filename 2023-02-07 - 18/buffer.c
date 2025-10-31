#include "buffer.h"

struct buffer{
	int id;
	char **token;
	int points;
	
	int n;
};
struct grid{
	char ***tokenGrid;
	int n;
};
struct mark{
	int **markGrid;
	int n;
};

GRID gridInit(FILE * gridfp){
	int i, j;
	GRID g = malloc(sizeof(struct grid));
	fscanf(gridfp, "%d", &g->n);
	
	g->tokenGrid = malloc(sizeof(char**)* g->n);
	for(i = 0; i < g->n; i++){
		g->tokenGrid[i] = malloc(sizeof(char *)*g->n);
		for(j = 0; j < g->n; j++){
			g->tokenGrid[i][j] = malloc(sizeof(char )*3);
			fscanf(gridfp, "%2s", g->tokenGrid[i][j]);
			g->tokenGrid[i][j][2] = '\0';
		}
	}
	return g;
}

MARK markInit(int n){
	int i, j;
	MARK g = malloc(sizeof(struct mark));
	g->n = n;
	g->markGrid = malloc(sizeof(int*)* g->n);
	for(i = 0; i < g->n; i++){
		g->markGrid[i] = malloc(sizeof(int)*g->n);
		for(j = 0; j < g->n; j++){
			g->markGrid[i][j]= 0;
		}
	}
	return g;
}

void markFree(MARK g){
	int i,j;
	for(i = 0; i < g->n; i++){
		free(g->markGrid[i]);
	}
	free(g->markGrid);
	free(g);
}

void markPrint(MARK g){
	int i,j;
	for(i = 0; i < g->n; i++){
		for(j = 0; j < g->n;j++)
			printf("%d ", g->markGrid[i][j]);
		printf("\n");
	}
}

void gridFree(GRID g){
	int i,j;
	for(i = 0; i < g->n; i++){
		for(j = 0; j < g->n; j++){
			free(g->tokenGrid[i][j]);
		}
		free(g->tokenGrid[i]);
	}
	free(g->tokenGrid);
	free(g);
}

void gridPrint(GRID g){
	int i,j;
	for(i = 0; i < g->n; i++){
		for(j = 0; j < g->n; j++){
			printf("%s ", g->tokenGrid[i][j]);
		}
		printf("\n");
	}
}

BUFFER bufferInit(int L){
	BUFFER v = malloc(sizeof(struct buffer));
	v->n = 0;

	v->token = malloc(sizeof(char **)* (L+1));
	for(int i = 0; i < L; i++)
		v->token[i] = malloc(sizeof(char *));
	return v;
}

void bufferFree(BUFFER v){
	for(int i = 0; i < v->n; i++)
		free(v->token[i]);
	free(v->token);
	free(v);
}


BUFFER *bonusLoad(FILE *bonusfp, int *nBonus) {
    int i, j;
    fscanf(bonusfp, "%d", nBonus);
    
    // Allocazione corretta dell'array di strutture
    BUFFER *buffer_array = malloc(sizeof(BUFFER) * (*nBonus));
    if (!buffer_array) return NULL;

    for(i = 0; i < *nBonus; i++) {
        j = 0;
        
        // Allocazione per ogni elemento dell'array
        buffer_array[i] = malloc(sizeof(struct buffer));
        if (!buffer_array[i]) return NULL;
        
        fscanf(bonusfp, "%d %d", &buffer_array[i]->id, &buffer_array[i]->points);
        
        // Allocazione corretta per l'array di stringhe
        buffer_array[i]->token = malloc(sizeof(char *) * 5);
        if (!buffer_array[i]->token) return NULL;
        
        char temp;
        do {
            buffer_array[i]->token[j] = malloc(sizeof(char) * 3);
            if (!buffer_array[i]->token[j]) return NULL;
            
            fscanf(bonusfp, "%2s", buffer_array[i]->token[j]);
            j++;
            
            // Leggi il prossimo carattere
            temp = fgetc(bonusfp);
            
        } while(temp != '\n' && temp != EOF && j < 5); // Aggiunti controlli di sicurezza
        
        buffer_array[i]->n = j;
    }
    
    return buffer_array;
}

void bonusPrint(BUFFER* vbonus,int nBonus){
	int i,j;
	
	for(i = 0; i < nBonus; i++){
		for(j = 0; j < vbonus[i]->n; j++){
			printf("%s ", vbonus[i]->token[j]);
		}
		printf("\n");
	}
	
}


void bonusFree(BUFFER* vbonus,int nBonus){
	int i;
	
	for(i = 0; i < nBonus; i++){
		bufferFree(vbonus[i]);
	}
	free(vbonus);
	
}



int checkBuffer(int L, BUFFER buf, GRID grid){
	if(L < buf->n)
		return 0;

	int i;
	int l,k, last_l = 0,last_k = 0;
	int found;
	for(i = 0; i < buf->n; i++){
		found = 0;
		if(i%2 == 0){ // ricerca orizzontale
			l = last_l;
			k = 0;
			//printf("\n[");
			for(k = 0; k < grid->n; k++){
				if(strcmp(grid->tokenGrid[l][k], buf->token[i]) == 0){
					found = 1;
					last_k = k;
				}
				//printf("%s-%s %d,",grid->tokenGrid[l][k],buf->token[i], found);
			}
			//printf("]\n");
		} // ricerca verticale
		else{
			l = 0;
			k = last_k;
			//printf("\n[");
			for(l = 0; l < grid->n; l++){
				if(strcmp(grid->tokenGrid[l][k], buf->token[i]) == 0){
					found = 1;
					last_l = l;
				}
				//printf("%s-%s %d,",grid->tokenGrid[l][k],buf->token[i], found);
			}
			//printf("]\n");
		}
		if(found == 0){
			//printf("non valido %d\n",i);
			return 0;
		}
		
	}

	return 1;
}

/*
struct buffer{
	int id;
	char **token;
	int points;
	
	int n;
};

*/
void calcPoints(BUFFER soluzione, BUFFER* bonus, int nBonus){
	int i,j, l, points = 0;
	for(i = 0; i < nBonus; i++){
		l = 0;
		if(bonus[i]->n <= soluzione->n)
			for(j = 0; j < soluzione->n && l==j && l < bonus[i]->n ;j++)
				if(strcmp(soluzione->token[j],bonus[i]->token[l]) == 0)
				{
					l++;
				}
		if(l == bonus[i]->n)
			points+=bonus[i]->points;
	}
	soluzione->points = points;

}

void recursiveSoluzione(int L,int pos,int l,int k, BUFFER soluzione,GRID grid,BUFFER* bonus,int nBonus, int *punteggioMax, MARK mark){
	int i,j;
	int gridLength = (grid->n)*(grid->n);
	soluzione->n = pos;
	

	if(soluzione->n >= L){

		calcPoints(soluzione, bonus, nBonus);
		if(soluzione->points > *punteggioMax){
			for(j = 0; j < soluzione->n; j++){
				printf("%s ", soluzione->token[j]);
			}
			*punteggioMax = soluzione->points;
			printf(" p: %d\n", soluzione->points);
		}

	}
	else{
		for(i = 0; i < grid->n; i++){
				
		
			if(pos%2==0){ // movimento sulle colonne
				//printf("pos: %d l: %d i: %d    %s\n",pos, l, i, grid->tokenGrid[l][i]);
				//markPrint(mark);
				if(mark->markGrid[l][i] == 1) continue;
				mark->markGrid[l][i] = 1;
				soluzione->token[pos] = grid->tokenGrid[l][i];
				recursiveSoluzione(L,pos+1,l,i, soluzione, grid, bonus,nBonus, punteggioMax, mark);
				mark->markGrid[l][i] = 0;
			}else{
				//printf("pos: %d i: %d k: %d   %s\n",pos, i, k, grid->tokenGrid[i][k]);
				//markPrint(mark);
				if(mark->markGrid[i][k] == 1) continue;
				mark->markGrid[i][k] = 1;
				soluzione->token[pos] = grid->tokenGrid[i][k];
				recursiveSoluzione(L,pos+1,i,k, soluzione, grid, bonus,nBonus, punteggioMax, mark);
				mark->markGrid[i][k] = 0;
			}
		}


		
	}


}
