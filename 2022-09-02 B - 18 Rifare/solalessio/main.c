#include "CruciPuzzle.h"
int main() {
    FILE *fgriglia = fopen("griglia.txt", "r");
    FILE *fparole = fopen("parole.txt", "r");
    FILE *fproposta = fopen("proposta.txt", "r");

    if (!fgriglia || !fparole || !fproposta) {
        printf("Errore nell'apertura dei file\n");
        return 1;
    }

    Grid G = GRIDload(fgriglia);
    Words W = WORDSload(fparole);

    // Carica proposta (formato: numero parole seguito da lista parole)
    int n_proposta;
    fscanf(fproposta, "%d", &n_proposta);
    Sol proposta = SOLinit(n_proposta);
    proposta->n = n_proposta;
    for (int i = 0; i < n_proposta; i++) {
        fscanf(fproposta, "%s", proposta->word[i]);
    }

    // Verifica proposta
    if (checkSOL(G, proposta, W)) {
        printf("Proposta valida\n");
    } else {
        printf("Proposta non valida\n");
    }

    // Trova soluzione ottima
    Sol ottima = findMaxSolution(G, W);
    printf("Soluzione ottima trovata con %d parole e valore %d\n", ottima->n, ottima->total_val);

    // Pulizia
    fclose(fgriglia);
    fclose(fparole);
    fclose(fproposta);
    GRIDfree(G);
    WORDSfree(W);
    SOLfree(proposta);
    SOLfree(ottima);

    return 0;
}