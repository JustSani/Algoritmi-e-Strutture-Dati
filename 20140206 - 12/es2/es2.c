#include "stdio.h"
#include "lista.h"


int main(){

    lista_t *lista = creaLista();

    int i = inserisciInOrdine(lista,"Sanino", "Fabio");
    i = inserisciInOrdine(lista,"Serra", "Fabio");
    i = inserisciInOrdine(lista,"Porcodio", "Fabio");
    i = inserisciInOrdine(lista,"Frocio", "Fabio");
    stampLista(lista);


    LISTfree(lista);


    return 0;
}



