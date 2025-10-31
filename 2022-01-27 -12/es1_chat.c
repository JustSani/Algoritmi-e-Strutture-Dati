#include <stdio.h>
#include <stdlib.h>

int **f(int **M, int r, int c, int *r1, int *c1);

int main(void){
    int **M;
    int i, j, r = 5, c = 5;

    /* allocazione matrice M */
    M = malloc(r * sizeof *M);
    for(i = 0; i < r; i++){
        M[i] = malloc(c * sizeof *M[i]);
        for(j = 0; j < c; j++){
            M[i][j] = i + j;
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }

    /* metto alcuni zeri di test */
    M[0][0] = 0;
    M[1][1] = 0;
    M[3][4] = 0;

    printf("\nM dopo inserimento zeri:\n");
    for(i = 0; i < r; i++){
        for(j = 0; j < c; j++) printf("%d ", M[i][j]);
        printf("\n");
    }

    int r1, c1;
    int **M_1 = f(M, r, c, &r1, &c1);

    printf("\nRisultato (%d x %d):\n", r1, c1);
    if(M_1){
        for(i = 0; i < r1; i++){
            for(j = 0; j < c1; j++) printf("%d ", M_1[i][j]);
            printf("\n");
        }
    } else {
        printf("Matrice risultante vuota (tutte le righe o colonne rimosse)\n");
    }

    /* free */
    for(i = 0; i < r; i++) free(M[i]);
    free(M);

    if(M_1){
        for(i = 0; i < r1; i++) free(M_1[i]);
        free(M_1);
    }

    return 0;
}

int **f(int **M, int r, int c, int *r1, int *c1){
    int i, j;

    /* marker per righe/colonne da rimuovere */
    int *mark_riga = calloc(r, sizeof *mark_riga);
    int *mark_colonna = calloc(c, sizeof *mark_colonna);
    if(!mark_riga || !mark_colonna){ perror("calloc"); exit(EXIT_FAILURE); }

    /* segna righe/colonne che contengono zero (una sola volta ciascuna) */
    for(i = 0; i < r; i++){
        for(j = 0; j < c; j++){
            if(M[i][j] == 0){
                mark_riga[i] = 1;
                mark_colonna[j] = 1;
            }
        }
    }

    /* conta righe/colonne rimosse */
    int righe_rimosse = 0, colonne_rimosse = 0;
    for(i = 0; i < r; i++) righe_rimosse += mark_riga[i];
    for(j = 0; j < c; j++) colonne_rimosse += mark_colonna[j];

    *r1 = r - righe_rimosse;
    *c1 = c - colonne_rimosse;
    if(*r1 <= 0 || *c1 <= 0){
        free(mark_riga);
        free(mark_colonna);
        return NULL;
    }

    /* allocazione M_1 */
    int **M_1 = malloc((*r1) * sizeof *M_1);
    if(!M_1){ perror("malloc"); exit(EXIT_FAILURE); }
    for(i = 0; i < *r1; i++){
        M_1[i] = malloc((*c1) * sizeof *M_1[i]);
        if(!M_1[i]){ perror("malloc"); exit(EXIT_FAILURE); }
    }

    /* copia saltando righe/colonne marcate */
    int di = 0, dj;
    for(i = 0; i < r; i++){
        if(mark_riga[i]) continue;
        dj = 0;
        for(j = 0; j < c; j++){
            if(mark_colonna[j]) continue;
            M_1[di][dj] = M[i][j];
            dj++;
        }
        di++;
    }

    free(mark_riga);
    free(mark_colonna);
    return M_1;
}
