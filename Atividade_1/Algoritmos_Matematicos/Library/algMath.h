#ifndef _ALGMATH__
#define _ALGMATH__

#include <complex.h>
#include <math.h>

typedef struct {
    /* Essa estrutura compõe o vetor polinômio na forma:
     * a0*X^0 + a1*X¹ + a2*X² + ... + an*X^n
     * onde size é a ordem - 1 do polinômio
     */
    char size;
    double poly[1000];
}Poly;

void BriotRuffini(Poly poly, double complex x0, Poly * polyDst);

void DiffPoly(Poly poly, Poly *PolyDst);

void SumPoly(Poly a, Poly b, Poly *dst);

void MinPoly(Poly a, Poly b, Poly *dst);

double complex FuncVal(Poly a, double complex x0);

void NewthonRaphson(Poly poly, double complex *raizes);

#endif