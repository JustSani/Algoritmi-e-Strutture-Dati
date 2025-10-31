#include "stdio.h"
#include "BST.h"
int main(){

    BST t = BSTinit();

    BSTinsert_leafR(t,0);
    BSTinsert_leafR(t,1);
    BSTinsert_leafR(t,2);
    BSTinsert_leafR(t,3);
    BSTinsert_leafR(t,4);
    BSTinsert_leafR(t,10);
    BSTinsert_leafR(t,8);
    BSTinsert_leafR(t,9);

    printBSTInOrder(t);
    int check = f(t);
    if(check)
        printf("E' un BST");
    else
        printf("Non è un BST");
    
    BSTfree(t);


    
    return 0;
}




