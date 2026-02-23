Si chiustifichi la scelta del modello combinatorioa dottato.
il modello è le disposizioni con k che varia.


Criteri di pruning
Il pruning lo facciamo nel momento che andiamo a ricorrere, verifichiamo, come richiesto dal
esercizio, che l'ultima lettera se termina con vocale, la seconda non puà iniziare con vocale.



void findSOL(char **parole,int nparole,int* sol,int* mark,int pos,int *nElementi, int*bestSol){
	int i;
	if(calcolaNumeroDiLettere(parole,sol,k) > calcolaNumeroDiLettere(parole,sol,nElementi)){
		for(i = 0; i < k; i++)
			bestSol[i] = sol[i];
		*nElementi = k;
	}

	for(i = 0; i < nparole; i++){
		int lenParola = strlen(parole[i]);
		if(mark[i] == 0)
		if(pos == 0 || !(isVocale(parole[i][lenParola]) && isVocale(parole[sol[pos-1]][0]) )){
			mark[i] = 1;
			sol[pos] = parole[i];
			
			findSol(parole,nparole,sol,mark, pos+1, nElementi);
			mark[i] = 0;
		}
		
	
	}
}	


char *bestConcat(char **parole, int nparole){
	int sol* = malloc(sizeof(int)* nparole);
	int bestSol* = malloc(sizeof(int)* nparole);
	int mark* = malloc(sizeof(int) * nparole);


	int nElementi = 0;
	findSOL(parole, nparole, sol, mark, 0, &nElementi, bestSol);
	
	char * bestConcat = malloc(sizeof(calcolaNumeroDiLettere(parole,bestSol,nElementi));
	
	// costruiamo la soluzione
	int l = 0, size = 0;
	for(int i = 0; i < nElementi){
		for(int j = 0; j < strlen(nElementi); j++){
			bestConcat[size++] = bestSol[i][j];
		}
	}
	free(sol);
	free(mark);
	return bestConcat;
}