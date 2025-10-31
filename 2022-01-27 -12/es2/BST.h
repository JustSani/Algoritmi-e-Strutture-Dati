typedef struct binarysearchtree* BST;

BST BSTinit() ;
void BSTinsert_leafR(BST bst, int item);
void BSTfree(BST bst);
void printBSTInOrder(BST bst);
int f(BST bst);