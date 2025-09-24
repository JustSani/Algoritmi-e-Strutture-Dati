#include "stdio.h"
#include "math.h"

typedef struct { int X, Y; } punto_t;
    void puntoScan(FILE *fp, punto_t *pp) {
    fscanf(fp, "%d%d", &pp->X, &pp->Y);
}
void puntoPrint(FILE *fp, punto_t p) {
    fprintf(fp, "(%d,%d)", p.X, p.Y);
}
float puntoDist(punto_t p0, punto_t p1) {
    int d2 = (p1.X-p0.X)*(p1.X-p0.X) +
    (p1.Y-p0.Y)*(p1.Y-p0.Y);
    return ((float) sqrt((double)d2));
}