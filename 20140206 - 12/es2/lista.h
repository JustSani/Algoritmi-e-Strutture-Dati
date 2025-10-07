typedef struct lista_t lista_t;

lista_t* creaLista();
int inserisciInOrdine (lista_t *lista, char *cognome, char *nome);
void stampLista(lista_t *lista);
void LISTfree(lista_t *k);