#include "stdio.h"
#include "lista.h"
#include "string.h"
#include "malloc.h"

typedef struct node *link;

struct node{
    char cognome[20];
    char nome[20];

    link next;
};

struct lista_t {
    link HEAD;
    int n;
};

lista_t* creaLista(){
    lista_t *lista = malloc(sizeof(lista_t));
    lista->HEAD = NULL;
    lista->n = 0;
    return lista;
}

link newNode(char val[20],char val2[20], link next){
    link x = malloc(sizeof *x);
    if (x==NULL)
    return NULL;
    else {
        strcpy(x->cognome, val);
        strcpy(x->nome, val2);
        x->next = next;
    }
    return x;
}
void stampLista(lista_t *lista){
    int i;
    link cnode = lista->HEAD;
    for(i = 0; i < lista->n; i++){
        printf("%s %s\n",cnode->cognome, cnode->nome);
        cnode = cnode->next;
    }
}
int inserisciInOrdine (lista_t *lista, char *cognome, char *nome){
    link cnode = lista->HEAD;
    link lastNode = NULL;

    // Caso lista vuota
    if(cnode == NULL){
        lista->HEAD = newNode(cognome, nome, NULL);
        lista->n++;
        return 0;
    }
    
    while(cnode != NULL){
        if(strcmp(cnode->cognome, cognome) == 0)
            return 1;
        else if(strcmp(cnode->cognome, cognome) > 0){ // inserimento ordinato
            link nuovo = newNode(cognome, nome, cnode);
            if (lastNode == NULL)
                lista->HEAD = nuovo;
            else
                lastNode->next = nuovo;
            lista->n++;
            return 0;
        }
        lastNode = cnode;
        cnode = cnode->next;
    }

    // Inserimento in coda
    lastNode->next = newNode(cognome, nome, NULL);
    lista->n++;
    return 0;
}

void LISTfree(lista_t *k){
    link nodec = k->HEAD; 
    link next = NULL;
    while(nodec != NULL){
        next = nodec->next;
        free(nodec);
        nodec = next;
    };
    free(k);
}