#include "stdio.h"
#include "malloc.h"

void f(int **M, int r, int c, int **M_1,int *r1, int *c1);

int main(){
    int ** M;
    int i, j,r=5,c=5;
    M = malloc(sizeof(int*) *r );
    for(i = 0; i < r; i++){
        M[i]= malloc(sizeof(int)* c);

        for(j = 0; j < c; j++){
            M[i][j] = i+j;
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

    M[0][0] = 0;
    M[1][1] = 0;
    M[3][4] = 0;

    int r1, c1;
    int **M_1;
    f(M,r,c,M_1,&r1,&c1);

    for(i = 0; i < c; i++){
        free(M[i]);
        free(M_1[i]);
    }
    free(M);
    free(M_1);

    return 0;
}

void f(int **M, int r, int c, int **M_1,int *r1, int *c1){

    int i, j;
    
    M_1 = malloc(sizeof(int*) * r);
    for(i = 0; i < r; i++){
        M_1[i] = malloc(sizeof(int) * c);    
        for(j = 0; j < c; j++)
            M_1[i][j] = 0;
    }
    
    
    // segnalatori di eventuali righe o colonne da eliminare
    int* mark_riga = malloc(sizeof(int) * r);
    int* mark_colonna = malloc(sizeof(int) * c);
    // assegnazione di 0
    for(i = 0; i < r; i++)
        mark_riga[i] = 0;
    for(i = 0; i < c; i++)
        mark_colonna[i] = 0;
    
    // assegnazione ai marker delle righe e colonne da eliminare
    int righe_rimosse = 0, colonne_rimosse = 0;
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
            if(M[i][j] == 0){
                righe_rimosse++;
                colonne_rimosse++;
                mark_riga[i] = 1;
                mark_colonna[j] = 1;
            }
    }

    // mentre si scorre la matrice elemento per elemento, se una riga/colonna è segnata
    // la ingorimao e passiamo a quella successiva

    int k = 0,l = 0;
    for(i = 0; k < r - righe_rimosse; i++, k++){
        if(mark_riga[i] == 1)
            k++;
        for(j = 0, l= 0; l < c - colonne_rimosse; j++, l++){
            if(mark_colonna[j] == 1)
                l++;
            M_1[i][j] = M[k][l];
        }
    }

    printf("\nrisultato:\n");

    for(i = 0; i < r - righe_rimosse; i++){
        for(j = 0; j < c - colonne_rimosse; j++){
            printf("%d ", M_1[i][j]);
        }
        printf("\n");
    }

    *r1 = r-righe_rimosse;
    *c1 = c-righe_rimosse;
    free(mark_riga);
    free(mark_colonna);
}