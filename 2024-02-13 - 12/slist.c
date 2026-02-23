slist.h
typedef Item *ITEM;

typedef Slist * SLIST;


slist.c
#include "slist.h"
#include "string.h"

typedef struct {char name[16]; int val} Item;

typedef struct {ITEM element, NODE next} node; 

typedef node * NODE;
typdef struct{
	NODE head;
	int n;
}Slist,


SLIST SLISTmerge(SLIST a, SLIST b){
	SLIST c = malloc(sizeof(c*));
	c->n = 0;
	NODE anode=a->head, bnode=b->head,cnode = NULL;
	
	c->head =  malloc(sizeof(cnode*);
	cnode = c->head;
	
	for(int i = 0; i < a->n + b->n; i++){
		if(anode != NULL && bnode != NULL && srtcmp(anode->name, bnode->name) == 0){
			strcpy(cnode->name, anode->name);
			cnode-> val = anode->val + bnode->val;	
			anode = anode->next;
			bnode = bnode->next;
		}
		else if(bnode == NULL || (anode != NULL && bnode != NULL && srtcmp(anode->name, bnode->name) == -1)){
			strcpy(cnode->name, anode->name);
			cnode-> val = anode->val;
			anode = anode->next;
		}
		else if(anode == NULL || (bnode != NULL && anode != NULL && srtcmp(anode->name, bnode->name) == -1)){
			strcpy(cnode->name, bnode->name);
			cnode-> val = bnode->val;
			bnode = bnode->next;
		}
		cnode->next= malloc(sizeof(cnode*);
		cnode = cnode->next;
		
	}
}
