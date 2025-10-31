#include "stdio.h"
#include "malloc.h"

int perm(int pos, int * val, int *sol, int *mark,int n, int count, int *differenza_massima_trovata);

int main(){
    int n = 7;
    int i;
    int val[]= {10, 12, -12, -10, -23 , -24, +10};
 
    int *sol = malloc(sizeof(int) * n);
    int *mark = malloc(sizeof(int) * n);
    for(i = 0; i < n; i++) mark[i] = 0;

    int *diff_max = malloc(sizeof(int));
    *diff_max = __INT32_MAX__;


    int count = perm(0, val, sol, mark, n, 0, diff_max);
    
    
    free(sol);
    free(mark);
    free(diff_max);
    return 0;
}

int calc_saldo_massimo(int *sol, int n){
    int i;
    int sum_max = 0, sum = 0;
    for(i = 0; i < n; i++){
        sum += sol[i];
        if(sum > sum_max)
            sum_max = sum;
    }

    return sum_max;
}

int calc_saldo_minimo(int *sol, int n){
    int i;
    int sum_min = __INT32_MAX__, sum = 0;
    for(i = 0; i < n; i++){
        sum += sol[i];
        if(sum < sum_min)
            sum_min = sum;
    }

    return sum_min;
}

int perm(int pos, int * val, int *sol, int *mark,int n, int count, int *differenza_massima_trovata){
    int i;
    if(pos>=n){
        int diff = calc_saldo_massimo(sol, n) - calc_saldo_minimo(sol, n);
        if(diff <  *differenza_massima_trovata){
            for(i = 0; i < n; i++) printf("%d ", sol[i]);
            printf(" min: %d  max:%d dif:%d\n", calc_saldo_minimo(sol, n), calc_saldo_massimo(sol, n), diff);
            *differenza_massima_trovata = diff;
            return count+1;
            
        }
        return count;
    }
    for(i = 0; i < n; i++){
        if(mark[i] == 0){
            mark[i] = 1;
            sol[pos] = val[i];
            count = perm(pos+1, val,sol,mark,n,count+1, differenza_massima_trovata);
            mark[i] = 0;
        }
    }

    return count;

}