#include <stdio.h>
#include "algMath.h"


int main(){
    int sizePoly = 0;
    Poly newPoly;
    printf("Esse programa calcula as raizes de um polinômio qualquer \n na forma: a0 + a1*X + a2*X² + ... + an X^n \n Digite o número de coeficientes que seu polinômio possui: ");
    scanf("%d", &sizePoly);
    newPoly.size = sizePoly;
    float val;
    for(int i = 0; i < sizePoly; i++){
        printf("Digite o coeficiente a %d: ", i);
        scanf("%f", &val);
        newPoly.poly[i] = (double)val;
    }
    printf("O polinômio inserido foi: ");
    for(int i = newPoly.size-1; i > 0; i--){
        if(newPoly.poly[i] != 0){
            if(newPoly.poly[i] == 1)
                printf("X^ %i + ", i);
            else
                printf("%.2f * X^ %i + ", newPoly.poly[i], i);

        }
    }
    printf("%.2f \n\n\n", newPoly.poly[0]);

    printf("Calculando as raízes do polinômio... \n");

    double complex raizes[newPoly.size];
    NewthonRaphson(newPoly, raizes);
    printf("As raízes do polinômio são: ");

    for(int i = 0; i < newPoly.size; i++){
        printf("%.2f + %.2fi\n", creal(raizes[i]), cimag(raizes[i]));
    }
}