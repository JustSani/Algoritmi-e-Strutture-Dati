//bst.c

typedef struct node * LINK;
typedef struct bst * BST;

//bst.h
struct node{
	int n;
	LINK left;
	LINK right;
};

struct bst{
	LINK head;
	int n;
};


void getDepth(LINK node,LINK * kLevelNodes,int k,int i,int *n){
	if(node == null)
		returm;
	
	if(k == i){
		kLevelNodes[*n] = node;
		(*n)++;
		return;
	}

	getDepth(node->left,kLevelNodes,k+1,i,n);
	
	getDepth(node->right,kLevelNodes,k+1,i,n);

}

LINK * BSTlevelizedNodes(BST b){
	LINK * vNodes = malloc(sizeof(LINK) * b->n);
	
	LINK cNode = b->head;

	int f = 0;
	int i = 0,k,l, n;
	do{
		n = 0;
		LINK * kLevelNodes = malloc(sizeof(LINK) * (2^i));
		// otteniamo tutti gli elementi di una determinata depth
		getDepth(, kLevelNodes ,0,i, &n);
		
		// li sortiamo
		for(k = 0; k < n; k++){
			int min = k;
			for(l = k + 1; l < n; l++){
				if(kLevelNodes[min]->n > kLevelNodes[l]->n){
					min = l;
				}
			}
			LINK temp = kLevelNodes[k];
			kLevelNodes[k] = kLevelNodes[min];
			kLevelNodes[min] = kLevelNodes[k];
		}

		// li salviamo nel valore di return;
		for(k = 0; k < n; k++, f++){
			vNodes[f] = kLevelNodes[k];
		} 


		free(kLevelNodes);
		
		i++;
	}while(n != 0)
	
	return vNodes;
}

