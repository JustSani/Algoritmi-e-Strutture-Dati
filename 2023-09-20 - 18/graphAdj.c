#include "graphAdj.h"

typedef struct node *link;

struct node{
	int value;	
	link next;
};


struct graph{
	int V;
	int E;
	link* ladj;
	link z;
};


link LinkNew(int v, int wt, link next){
	link l = malloc(sizeof(*l));
	l-> value = v;
	l->wt = wt;
	l->next = next;
	return l;
}

GRAPH GraphInit(int V){
	GRAPH g = malloc(sizeof(*g));
	g->V = V;
	g->ladj = malloc(sizeof(link) * V);
	g->z = LinkNew(-1,-1,NULL);
	return g;
}

void LinkFree(link z){
	free(z);
}

int cmpLink(link a, link b){
	if(a->value == b->value && a-> wt == b->wt && a->next == b->next){
	return 1;

	}
	return 0;
}
void rListFree(link l, link z){
	if(cmpLink(l,z))
		return;
	rListFree(l->next,z);
	free(l);
}

void GraphFree(GRAPH g){
	int i;
	for(i = 0; i < g->V; i++){
		rListFree(g->ladj[i], g->z);
	}
	free(g->ladj);
	LinkFree(g->z);
	free(g);
}

void insertE(GRAPH g, int v1, int v2, int wt){
	g->ladj[v1] = LinkNew(v2, wt, g->ladj[v1]);
	g->ladj[v2] = LinkNew(v1, wt, g->ladj[v2]);
}

GRAPH GraphLoad(FILE *fp){
	int V;
	fscanf(fp,"%d\n", &V);
	GRAPH g = GraphInit(V);
	printf("%d\n",g->V);
	int v1, v2, wt;
	for(int i = 0; i < g->V; i++)
		g->ladj[i] = g->z;
	while(fscanf(fp,"%d %d %d\n", &v1, &v2, &wt) == 3){
		//printf("%d %d %d\n", v1, v2, wt);
		insertE(g, v1, v2, wt);
	}
	return g;
}

void GraphPrint(GRAPH g){
	printf("--Graph Print---------\n");
	link temp;
	for(int i = 0; i < g->V; i++){
		temp = g->ladj[i];
		printf("%d : ",i);
		while(!cmpLink(temp, g->z)){
			printf("(%d/%d),", temp->value, temp->wt);
			temp = temp->next;
		}
		printf("\n");
	}
}


int rCheckConnection(int* mark, GRAPH g,GRAPH sol,link current,link prec,int k, int *v){
	printf("DFS: c:%d p:%d\n",current->value, prec->value);

	int i = 0, val;
	for(i = 0; i < g->V; i++)
		printf("%d", mark[i]);
	printf("\n");
	if(*v > g->V)
		return 0;
	while(current != g->z){
		if(mark[current->value] == 0){
			mark[current->value] = 1;
			*v = *v + 1;
			val = rCheckConnection(mark,g,sol, sol->ladj[current->value],current, k, v);
			if(!val){
				printf("\n[loop]\n");
				return 0;
			}
			current = current->next;
		}else if(current->value != prec->value){
			return 1;
		}else return 0;
	}
	printf("qui");
	return 1;
}

int GraphCheckSol(GRAPH g, GRAPH sol, int k){
	int i,j, n;
	int *mark = malloc(sizeof(int)* g->V);
	int v;
	int sum = 0;
	for(i = 0; i < g->V; i++){
		for(j = 0; j < g->V; j++)
			mark[j] = 0;
		v = 0;
		rCheckConnection(mark, g, sol, g->ladj[i],g->z, k, &v);
		sum += v;
	}
	printf("%d \n", sum);
	free(mark);
	if(sum != g->V)
		return 0;
	return 1;
}



