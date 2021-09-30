#include "algMath.h"
#include <math.h>
#include <complex.h>
#include <stdio.h>
#include <string.h>

/*
Algorítmo de Briot-Ruffini é um algorítmo que diminui o grau de um polinômio
*/
void BriotRuffini(Poly poly, double complex x0, Poly * polyDst){
    
    memcpy(&(polyDst->poly[0]), &(poly.poly[0]), sizeof(poly.poly[0]));
    for(int i = 1; i < poly.size; i++){
        polyDst->poly[i] = polyDst->poly[i-1]*x0 + poly.poly[i];
    }
}

void DiffPoly(Poly poly, Poly *PolyDst){
    printf("%i \n", poly.size);
    for(int i = 0; i < poly.size; i++){
        PolyDst->poly[i] = poly.poly[i+1] * (i+1);
    }
}

double complex FuncVal(Poly a, double complex x0){
    double complex val = a.poly[0];

    for(int i = 1; i < a.size; i++){
        val += a.poly[i] * pow(x0, i);
    }
    return val;
}

void NewthonRaphson(Poly poly, double complex *raizes){
    double complex x0 = (100000.00 + I * 100000.00);
    double complex x = FuncVal(poly, x0);;
    int it = 1000; //numero de iterações máxima

    Poly diffpoly;
    DiffPoly(poly, &diffpoly); //polinômio da derivada
    int pos = 0;

    while(it > 0){
        DiffPoly(poly, &diffpoly); //polinômio da derivada
        x = x0 - (FuncVal(poly, x0) / FuncVal(diffpoly, x0));
        printf("x: %.2f + %.2fi \n", creal(x), cimag(x));
        if(x == x0){ //Pensar em melhorar essa condição com o buffer de convergência
            raizes[pos++] = x;
            BriotRuffini(poly, x, &poly);
            printf("Achei uma raíz");
            if(cimag(x)!= 0){
                x = creal(x) + I * -cimag(x);
                raizes[pos++] = x;
                BriotRuffini(poly, x, &poly);
            }
        }
        if(pos == poly.size - 1)
            {
                it = 0;
                return;
            }
        x0 = x;
        printf("%.2f + %.2fi \n", creal(x), cimag(x));
        it--;
    }

    return;
}