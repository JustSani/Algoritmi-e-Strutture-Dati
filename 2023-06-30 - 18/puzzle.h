typedef struct puzzle * PUZZLE;



PUZZLE PUZZLEload(FILE *fp);

void PUZZLEfree(PUZZLE p);
void PUZZLEprint(PUZZLE p);
void SOLprint(char *sol, int size);
char * SOLload(FILE *fp2, int *size);
void SOLfree(char *sol);
void PUZZLEprintReadable(PUZZLE p);
int CHECKsol(PUZZLE p, char *sol, int N);