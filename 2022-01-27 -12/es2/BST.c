#include "stdio.h"
#include "BST.h"
#include "malloc.h"

typedef struct BSTnode* link;

struct BSTnode{
    int item;
    link l;
    link r;
};
struct binarysearchtree{link root;link z;};


static link NEW(int ITEM, link L, link R){
    link nlink = malloc(sizeof(*nlink));
    nlink->item = ITEM;
    nlink->l = L;
    nlink->r = R;
    return nlink;
}

BST BSTinit(){
    BST bst = malloc(sizeof(*bst));
    bst->z = NEW(-1,NULL,NULL);
    bst->root = bst->z;
    return bst;
}

link insertR(link node, int item, link z){
    if(node == z)
        return NEW(item,z,z);
    if(node->item > item)
        node->l = insertR(node->l, item, z);
    else if(node->item < item)
        node->r = insertR(node->r, item, z);
    
    return node;
}

void BSTinsert_leafR(BST bst, int item){
    bst->root = insertR(bst->root, item, bst->z);
}

void linkfreeR(link h, link z){
    if(h != z){
        linkfreeR(h->l,z);
        linkfreeR(h->r,z);
        free(h);
    }
}
void BSTfree(BST bst){
    linkfreeR(bst->root,bst->z);
    free(bst->z);
    free(bst);
}
void visitNodeInOrder(link h, link z){
    if(h == z)
        return;
    visitNodeInOrder(h->l,z);
    printf("%d ", h->item);
    visitNodeInOrder(h->r,z);
}

void printBSTInOrder(BST bst){
    visitNodeInOrder(bst->root,bst->z);
    printf("\n");

}

int checklink(link h, link z){
    if(h == z)
        return 1;

    if(h->l != z && h->item < h->l->item)
        return 0;
    if(h->r != z && h->item > h->r->item)
        return 0;

    if(checklink(h->l, z) && checklink(h->r, z))
        return 1;
    
    return 0;    

}
int f(BST bst){
    return checklink(bst->root, bst->z);
}