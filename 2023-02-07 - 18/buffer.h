#include "malloc.h"
#include "stdio.h"
#include "string.h"

typedef struct buffer *BUFFER;
typedef struct grid *GRID;
typedef struct mark *MARK;

GRID gridInit(FILE* gridfp);
void gridFree(GRID g);
void gridPrint(GRID g);
BUFFER bufferInit();
void bufferFree(BUFFER v);

MARK markInit(int n);
void markPrint(MARK g);
void markFree(MARK g);


BUFFER * bonusLoad(FILE *bonusfp,int *nBonus);
void bonusPrint(BUFFER* vbonus,int nBonus);
void bonusFree(BUFFER* vbonus,int nBonus);

int checkBuffer(int L, BUFFER buf, GRID grid);
void calcPoints(BUFFER soluzione, BUFFER* bonus, int nBonus);
void recursiveSoluzione(int L,int pos,int l,int k, BUFFER soluzione,GRID grid,BUFFER* bonus,int nBonus, int *punteggioMax, MARK mark);