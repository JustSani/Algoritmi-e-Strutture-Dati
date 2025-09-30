#include "stdio.h"
#include "malloc.h"
const int n = 10;

int perm(int pos,char *val,char* sol,int *mark, int n, int cnt);

int check_sol(char *sol);
int findPos(char *sol, char letter);

int main(void) {
    
    // vettore
    
    char val[] = { 'S','E','N','D','M','O','R','Y','-','-' };

    int *mark = malloc(n *sizeof(int));
    char *sol = malloc(n *sizeof(char));
    for(int i = 0; i < n; i++) mark[i] = 0;

    int cnt = perm(0, val, sol, mark, n, 0);

    free(mark);
    free(sol);
    return 0;
}

int perm(int pos,char *val,char* sol,int *mark, int n, int cnt){
        
    int i;
    if(pos>=n){
        if(check_sol(sol) == 0){
            for(i = 0; i < n; i++) printf("%d ", i);
            printf("\n");
            for(i = 0; i < n; i++) printf("%c ", sol[i]);
            printf("\n");
            
            int add1 = 0;
            add1 = findPos(sol, 'S');
            add1 = add1 * 10 + findPos(sol, 'E');
            add1 = add1 * 10 + findPos(sol, 'N');
            add1 = add1 * 10 + findPos(sol, 'D');
            int add2 = 0;
            add2 = findPos(sol, 'M');
            add2 = add2 * 10 + findPos(sol, 'O');
            add2 = add2 * 10 + findPos(sol, 'R');
            add2 = add2 * 10 + findPos(sol, 'E');
            int sumFound = 0;
            sumFound = findPos(sol, 'M');
            sumFound = sumFound * 10 + findPos(sol, 'O');
            sumFound = sumFound * 10 + findPos(sol, 'N');
            sumFound = sumFound * 10 + findPos(sol, 'E');
            sumFound = sumFound * 10 + findPos(sol, 'Y');
            printf("SEND: %d  + MORE: %d = MONEY: %d", add1, add2, sumFound);
            printf("\n");
            return cnt +1;    
        }        
    }
    //for(i = 0; i < n; i++) printf("%c ", sol[i]);
    //printf("\n");
    for(i = 0; i < n; i++){
        if(mark[i] == 0){
            mark[i] = 1;
            sol[pos] = val[i];
            cnt = perm(pos+1, val, sol, mark, n, cnt);
            mark[i] = 0;
        }
    }
    return cnt;

}


int check_sol(char *sol){
    int add1 = 0;
    add1 = findPos(sol, 'S');
    add1 = add1 * 10 + findPos(sol, 'E');
    add1 = add1 * 10 + findPos(sol, 'N');
    add1 = add1 * 10 + findPos(sol, 'D');

    int add2 = 0;
    add2 = findPos(sol, 'M');
    add2 = add2 * 10 + findPos(sol, 'O');
    add2 = add2 * 10 + findPos(sol, 'R');
    add2 = add2 * 10 + findPos(sol, 'E');

    
    int sumFound = 0;
    sumFound = findPos(sol, 'M');
    sumFound = sumFound * 10 + findPos(sol, 'O');
    sumFound = sumFound * 10 + findPos(sol, 'N');
    sumFound = sumFound * 10 + findPos(sol, 'E');
    sumFound = sumFound * 10 + findPos(sol, 'Y');

    int sumCalc = add1 + add2;
    if(sumFound == sumCalc)
        return 0;

    //printf("nope\n");
    return 1;
}

int findPos(char *sol, char letter){
    for(int i = 0; i < n; i++){
        if(sol[i] == letter)
            return i; 
    } 
    return -1;
    
}