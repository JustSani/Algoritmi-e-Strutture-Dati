#include "stdio.h"
#include "malloc.h"

int perm(int pos,int *val,int *sol,int *mark, int n, int cnt);
const int n = 5;

int main(){
    
    int *val = malloc(n * sizeof(int));
    int *sol = malloc(n * sizeof(int));
    int *mark = calloc(n, sizeof(int));
    
    for(int i = 0; i< n; i++) val[i] = i;

    perm(0,val,sol,mark,n,0);
    
    free(val);
    free(sol);
    free(mark);
    return 0;
}

int perm(int pos, int* val, int *sol, int *mark, int n, int count){
    int i;
    if(pos>=n){
        for(i = 0; i < n; i++) printf("%d ", sol[i]);
        printf("\n");
        return count +1;
    }
    for(i = 0; i < n; i++){
        if(mark[i] == 0){
            mark[i] = 1;
            sol[pos] = val[i];
            count = perm(pos+1,val,sol,mark,n,count+1);
            mark[i] = 0;
        }
    }
    return count;
}