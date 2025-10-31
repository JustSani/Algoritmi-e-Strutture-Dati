#include "stdio.h"
#include "malloc.h"
int NR, NC;

int **readGriglia(FILE *fp);
void freeGriglia(int ** griglia);

void printGriglia(int ** griglia);
char * readSoluzione(FILE *fp);

int validaSoluzione(int ** griglia, char* sol);


struct soluzione{
    int lato;
    int riga;
    int colonna; 
}sol;

int main(){
    FILE *fp = fopen("griglia.txt", "r");
    FILE *fp2 = fopen("soluzione.txt","r");


    int ** griglia = readGriglia(fp);
    char * sol = readSoluzione(fp2);

    int ok = validaSoluzione(griglia, sol);

    for(int i = 0; i < NR*NC; i++){
        printf("%c ", sol[i]);
        if((i + 1)%4==0) printf("\n");
        }

    printGriglia(griglia);
    
    if(ok)
        printf("soluzione OK");
    else printf("errore nella soluzione");

    free(sol);
    freeGriglia(griglia);
    fclose(fp);
    fclose(fp2);

    return 0;
}

int validaSoluzione(int ** griglia, char* sol){
    int i, j, k;
    int ** griglia_sol = malloc(sizeof(int*) * NR);
    for(i = 0; i < NR; i++)
        griglia_sol[i] = malloc(sizeof(int) *NC);

    for(i = 0; i < NR*NC; i++)
    {
        k = i / NC; // riga
        j = i % NC; // colonna
        if(sol[i] == 'U')
            griglia_sol[k][j]=0;
        else if(sol[i] == 'D')
        {
            griglia_sol[k][j] = 0;
            griglia_sol[k+1][j] = 0;
            griglia_sol[k][j+1] = 0;
            griglia_sol[k+1][j+1] = 0;
        }
        else if(sol[i] == '1')
            griglia_sol[k][j] = 1;
        else if(sol[i] == '0')
            griglia_sol[k][j] = 0;
    }

    for(i = 0; i < NR; i++){
        for(j = 0; j < NC; j++){
            if(griglia[i][j] != griglia_sol[i][j]){
                freeGriglia(griglia_sol);
                return 0;
            }
        }
    }

    freeGriglia(griglia_sol);
    return 1;
}

char * readSoluzione(FILE* fp){
    int i;
    char * sol = malloc(sizeof(char)* NC*NR);
    for(i = 0; i < NC*NR; i++)
        fscanf(fp,"%c ", &sol[i]);
    
    return sol;
}
void printGriglia(int ** griglia){
    int i, j;
    for(i = 0; i < NR; i++){
        for(j = 0; j < NC; j++)
            printf("%d ", griglia[i][j]);
        printf("\n");    
    }
}

int **readGriglia(FILE *fp){
    int i, j;
    fscanf(fp, "%d %d\n", &NR, &NC);
    int** griglia = malloc(sizeof(int *) * NR);

    for(i = 0; i < NR; i++){
        griglia[i] = malloc(sizeof(int) * NC);
        for(j = 0; j < NC; j++)
            fscanf(fp, "%d", &griglia[i][j]);
        fscanf(fp, "\n");
    }
    return griglia;
}

void freeGriglia(int ** griglia){
    int i, j;
    for(i = 0; i < NR; i++)
        free(griglia[i]);

    free(griglia);
}