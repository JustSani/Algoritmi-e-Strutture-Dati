#ifndef ES_CRUCIPUZZLE_H
#define ES_CRUCIPUZZLE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct grid *Grid;
struct grid {
    char **crucipuzzle;
    int r;
    int c;
};

typedef struct word {
    char *word;
    int val;
} Word;

typedef struct words *Words;
struct words {
    Word *word;
    int n;
};

typedef struct sol *Sol;
struct sol {
    char **word;
    int *val;
    int n;
    int total_val;
};

typedef struct position {
    int i;
    int j;
    int type; // 0: orizzontale, 1: verticale, 2: diagonale
} Position;
Grid GRIDinit(int r, int c);
void GRIDfree(Grid grid);
Words WORDSinit();
void WORDSfree(Words words);
Sol SOLinit(int max_words);
void SOLfree(Sol sol);
Grid GRIDload(FILE *fin);
Words WORDSload(FILE *fin);
int checkWordInGrid(Grid G, char *word, int i, int j, int type, int **used);
void markWordInGrid(char *word, int i, int j, int type, int **used, int mark);
int findWordPosition(Grid G, Words W, int word_idx, int **used, Position *pos);
int checkSOL(Grid G, Sol S, Words W);
void findMaxSolutionRecursive(Grid G, Words W, int **used, Sol current, Sol *best, int word_idx);
Sol findMaxSolution(Grid G, Words W);
#endif