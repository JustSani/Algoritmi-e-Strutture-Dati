#include "stdio.h"
#include "malloc.h"
int *merge3 (int *a, int *b, int *c, int na, int nb, int nc);

int main(){
    int na = 3, nb= 5 , nc= 8;
    int *a = malloc(sizeof(int) * na), *b =malloc(sizeof(int) * nb), *c = malloc(sizeof(int) * nc);
    
    int i;
    for(i = 0; i < na; i++) a[i] = i*4;
    for(i = 0; i < nb; i++) b[i] = i*2;
    for(i = 0; i < nc; i++) c[i] = i*3;
    

    int *merged = merge3 (a,b,c,na,nb,nc);

    for(i = 0; i < na+nb+nc; i++) printf("%d ", merged[i]);
    free(merged);
    free(a);
    free(b);
    free(c);
    return 0;
}



int *merge3 (int *a, int *b, int *c, int na, int nb, int nc){
    int i, j, k, l;
    int nm = na+nb+nc;
    int *m = malloc(sizeof(int) *nm);

    for(i = 0, j = 0, k = 0, l = 0; i < nm; i++){
        if(j < na && a[j] <= b[k] && a[j] <= c[l])
            m[i] = a[j++];
        else if(k < nb && b[k] <= a[j] && b[k] <= c[l])
            m[i] = b[k++];
        else
            m[i] = c[l++];
    }

    return m;    
}

