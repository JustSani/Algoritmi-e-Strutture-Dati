#include "stdio.h"
#include "malloc.h"

void disp_ripetizione(int pos, char *val, char *sol, int n, int k, int **mat, int **marked);
int ** readGriglia(char * file, int* n);

void freeGriglia(int **mat, int n);
int getCordX( int ** mat,char * sol,int n);
int getCordY( int ** mat,char * sol,int n);

int sizeMatrx = 7;
int calcpathsize(int ** matrice, int n){
    int pathsize = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(matrice[i][j] != 1)
                pathsize++;
    return pathsize;
}

int main(){
    int n;
    int **matrice = readGriglia("griglia.txt", &n);
    int **marked = malloc(sizeof(int*) * n);

    for(int i = 0; i < n; i++){
        marked[i] = malloc(sizeof(int) * n);
        for(int j = 0; j < n; j++)
            marked[i][j] = 0;
    }
    marked[0][0] = 1;

    int pathSize = calcpathsize(matrice, n);
    printf("pathsize: %d\n", pathSize);
    char val [4]= {'n', 's','o','e'};

    char *sol = malloc(sizeof(char) * pathSize);

    disp_ripetizione(0, val, sol, 4, pathSize, matrice, marked);
    
    freeGriglia(matrice, n);
    free(sol);
    return 0;
}   

int calcTurns(char * sol,int k){
    int i, turns=0;
    for(i = 1; i < k; i++)
        if(sol[i] != sol[i-1])
            turns++;
    return turns;
}
void disp_ripetizione(int pos, char *val, char *sol, int n, int k , int **mat,int** marked){
    int i, x, y;
    if(pos>=k - 1){
        for(i = 0; i < k; i++){
            printf("%c ", sol[i]);
        }
        printf("  turns; %d\n", calcTurns(sol,k));
    }
    else
        for(i = 0; i < n; i++){
            sol[pos] = val[i];
            x = getCordX(mat, sol, pos + 1);
            y = getCordY(mat, sol, pos + 1);
            if(x != -1 && y != -1 && marked[y][x] == 0){
                marked[y][x] = 1;
                disp_ripetizione(pos+1, val, sol, n, k, mat, marked);
                marked[y][x] = 0;
            }
        }
}

int ** readGriglia(char * file, int* n){
    FILE *fp = fopen("griglia.txt", "r");
    fscanf(fp,"%d\n", n);

    int **mat = malloc(sizeof(int*)* (*n));
    for(int i = 0; i < *n; i++){
        mat[i] = malloc(sizeof(int) * (*n));

        for(int j = 0; j < *n; j++){
            fscanf(fp,"%d",&mat[i][j]);
            printf("%d ", mat[i][j]);
        }
        printf("\n");
        fgetc(fp);
    }

    fclose(fp);
    return mat;
}


void freeGriglia(int **mat, int n){
    for(int i = 0; i < n; i++){
        free(mat[i]);
    }
    free(mat);
}

int getCordX( int ** mat,char * sol,int n){
    int x = 0, y = 0;
    for(int i = 0; i < n; i++)
        if(sol[i] == 'n')
            y--;
        else if(sol[i] == 's')
            y++;
        else if(sol[i] == 'e')
            x++;
        else if(sol[i] == 'o')
            x--;
    if(x < 0 || x > sizeMatrx - 1 || y < 0 || y > sizeMatrx - 1)
        return -1;
    if(mat[y][x] == 1)
        return -1;
    return x;
}

int getCordY( int ** mat,char * sol,int n){
    int x = 0, y = 0;
    for(int i = 0; i < n; i++)
        if(sol[i] == 'n')
            y--;
        else if(sol[i] == 's')
            y++;
        else if(sol[i] == 'e')
            x++;
        else if(sol[i] == 'o')
            x--;
    if(x < 0 || x > sizeMatrx - 1 || y < 0 || y > sizeMatrx - 1)
        return -1;
    if(mat[y][x] == 1)
        return -1;
    return y;
}
