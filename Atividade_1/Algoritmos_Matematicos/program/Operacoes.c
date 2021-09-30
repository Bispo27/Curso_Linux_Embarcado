#include "../Library/algMath.h"
#include <stdio.h>


int main(){
    int sizePoly;
    Poly newPoly;
    printf("Esse programa calcula a derivada de um polinômio qualquer \n na forma: a0 + a1*X + a2*X² + ... + an X^n \n Digite o número de coeficientes que seu polinômio possui: ");
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

    printf("Calculando a derivada do polinômio... \n");
    DiffPoly(newPoly, &newPoly);

    printf("A derivada do polinômio é: ");
    for(int i = newPoly.size; i > -1; i--){
        if(newPoly.poly[i] != 0){
            if(newPoly.poly[i] == 1)
                printf("X^ %i + ", i);
            else
                printf("%.2f * X^ %i + ", newPoly.poly[i], i);

        }
    }

}