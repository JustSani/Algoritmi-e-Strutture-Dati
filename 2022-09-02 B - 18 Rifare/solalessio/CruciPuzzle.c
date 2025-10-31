#include "CruciPuzzle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 16
#define HORIZONTAL 0
#define VERTICAL 1
#define DIAGONAL 2

static char **PUZZLEinit(int r, int c) {
    char **mat = malloc(r * sizeof(char *));
    for (int i = 0; i < r; i++) {
        mat[i] = malloc(c * sizeof(char));
    }
    return mat;
}

Grid GRIDinit(int r, int c) {
    Grid grid = malloc(sizeof(struct grid));
    grid->r = r;
    grid->c = c;
    grid->crucipuzzle = PUZZLEinit(r, c);
    return grid;
}

void GRIDfree(Grid grid) {
    if (grid != NULL) {
        for (int i = 0; i < grid->r; i++) {
            free(grid->crucipuzzle[i]);
        }
        free(grid->crucipuzzle);
        free(grid);
    }
}

Words WORDSinit() {
    Words words = malloc(sizeof(struct words));
    words->n = 0;
    words->word = NULL;
    return words;
}

void WORDSfree(Words words) {
    if (words != NULL) {
        for (int i = 0; i < words->n; i++) {
            free(words->word[i].word);
        }
        free(words->word);
        free(words);
    }
}

Sol SOLinit(int max_words) {
    Sol sol = malloc(sizeof(struct sol));
    sol->n = 0;
    sol->total_val = 0;
    sol->word = malloc(max_words * sizeof(char *));
    sol->val = malloc(max_words * sizeof(int));
    for (int i = 0; i < max_words; i++) {
        sol->word[i] = malloc(MAX_WORD_LENGTH * sizeof(char));
        sol->val[i] = 0;
    }
    return sol;
}

void SOLfree(Sol sol) {
    if (sol != NULL) {
        for (int i = 0; i < sol->n; i++) {
            free(sol->word[i]);
        }
        free(sol->word);
        free(sol->val);
        free(sol);
    }
}

Grid GRIDload(FILE *fin) {
    int R, C;
    fscanf(fin, "%d %d", &R, &C);
    Grid G = GRIDinit(R, C);

    char buffer[256];
    fgets(buffer, sizeof(buffer), fin); // Legge il newline dopo R e C

    for (int i = 0; i < R; i++) {
        fgets(buffer, sizeof(buffer), fin);
        for (int j = 0; j < C; j++) {
            G->crucipuzzle[i][j] = buffer[j];
        }
    }
    return G;
}

Words WORDSload(FILE *fin) {
    Words W = WORDSinit();
    char word_buf[MAX_WORD_LENGTH];
    int value;

    while (fscanf(fin, "%s %d", word_buf, &value) == 2) {
        W->n++;
        W->word = realloc(W->word, W->n * sizeof(Word));
        W->word[W->n-1].word = malloc((strlen(word_buf) + 1) * sizeof(char));
        strcpy(W->word[W->n-1].word, word_buf);
        W->word[W->n-1].val = value;
    }
    return W;
}

int checkWordInGrid(Grid G, char *word, int i, int j, int type, int **used) {
    int len = strlen(word);

    if (type == HORIZONTAL && j + len > G->c) return 0;
    if (type == VERTICAL && i + len > G->r) return 0;
    if (type == DIAGONAL && (i + len > G->r || j + len > G->c)) return 0;

    // Controlla se la parola è presente
    for (int k = 0; k < len; k++) {
        int ci = i, cj = j;
        if (type == HORIZONTAL) cj = j + k;
        else if (type == VERTICAL) ci = i + k;
        else if (type == DIAGONAL) { ci = i + k; cj = j + k; }

        if (G->crucipuzzle[ci][cj] != word[k]) {
            return 0;
        }
    }

    // Controlla sovrapposizioni
    int overlap_count = 0;
    for (int k = 0; k < len; k++) {
        int ci = i, cj = j;
        if (type == HORIZONTAL) cj = j + k;
        else if (type == VERTICAL) ci = i + k;
        else if (type == DIAGONAL) { ci = i + k; cj = j + k; }

        if (used[ci][cj] == 1) {
            overlap_count++;
            if (overlap_count > 1) return 0;
        }
    }

    return 1;
}

void markWordInGrid(char *word, int i, int j, int type, int **used, int mark) {
    int len = strlen(word);
    for (int k = 0; k < len; k++) {
        int ci = i, cj = j;
        if (type == HORIZONTAL) cj = j + k;
        else if (type == VERTICAL) ci = i + k;
        else if (type == DIAGONAL) { ci = i + k; cj = j + k; }
        used[ci][cj] = mark;
    }
}

int findWordPosition(Grid G, Words W, int word_idx, int **used, Position *pos) {
    char *word = W->word[word_idx].word;
    int len = strlen(word);

    for (int i = 0; i < G->r; i++) {
        for (int j = 0; j < G->c; j++) {
            for (int type = 0; type < 3; type++) {
                if (checkWordInGrid(G, word, i, j, type, used)) {
                    pos->i = i;
                    pos->j = j;
                    pos->type = type;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int checkSOL(Grid G, Sol S, Words W) {
    // Crea matrice per tracciare le lettere usate
    int **used = malloc(G->r * sizeof(int *));
    for (int i = 0; i < G->r; i++) {
        used[i] = calloc(G->c, sizeof(int));
    }

    // Verifica ogni parola nella soluzione
    for (int i = 0; i < S->n; i++) {
        int found = 0;
        Position pos;

        // Cerca la parola nella griglia
        for (int type = 0; type < 3 && !found; type++) {
            for (int row = 0; row < G->r && !found; row++) {
                for (int col = 0; col < G->c && !found; col++) {
                    if (checkWordInGrid(G, S->word[i], row, col, type, used)) {
                        found = 1;
                        markWordInGrid(S->word[i], row, col, type, used, 1);
                    }
                }
            }
        }

        if (!found) {
            for (int i = 0; i < G->r; i++) free(used[i]);
            free(used);
            return 0;
        }
    }

    for (int i = 0; i < G->r; i++) free(used[i]);
    free(used);
    return 1;
}
void findMaxSolutionRecursive(Grid G, Words W, int **used, Sol current, Sol *best, int word_idx) {
    if (word_idx >= W->n) {
        // Fine della ricorsione
        if (current->total_val > (*best)->total_val ||
            (current->total_val == (*best)->total_val && current->n > (*best)->n)) {
            // Copia la soluzione corrente in best
            for (int i = 0; i < current->n; i++) {
                strcpy((*best)->word[i], current->word[i]);
                (*best)->val[i] = current->val[i];
            }
            (*best)->n = current->n;
            (*best)->total_val = current->total_val;
        }
        return;
    }

    // Prova ad aggiungere la parola corrente
    Position pos;
    if (findWordPosition(G, W, word_idx, used, &pos)) {
        // Marca la parola come usata
        markWordInGrid(W->word[word_idx].word, pos.i, pos.j, pos.type, used, 1);

        // Aggiungi la parola alla soluzione corrente
        strcpy(current->word[current->n], W->word[word_idx].word);
        current->val[current->n] = W->word[word_idx].val;
        current->total_val += W->word[word_idx].val;
        current->n++;

        // Ricorsione
        findMaxSolutionRecursive(G, W, used, current, best, word_idx + 1);

        // Backtrack
        markWordInGrid(W->word[word_idx].word, pos.i, pos.j, pos.type, used, 0);
        current->n--;
        current->total_val -= W->word[word_idx].val;
    }

    // Prova a saltare la parola corrente
    findMaxSolutionRecursive(G, W, used, current, best, word_idx + 1);
}

Sol findMaxSolution(Grid G, Words W) {
    // Inizializza matrice used
    int **used = malloc(G->r * sizeof(int *));
    for (int i = 0; i < G->r; i++) {
        used[i] = calloc(G->c, sizeof(int));
    }

    // Inizializza soluzioni
    Sol current = SOLinit(W->n);
    Sol best = SOLinit(W->n);

    // Trova soluzione ottima
    findMaxSolutionRecursive(G, W, used, current, &best, 0);

    // Pulizia
    for (int i = 0; i < G->r; i++) free(used[i]);
    free(used);
    SOLfree(current);

    return best;
}