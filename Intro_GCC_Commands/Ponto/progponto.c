#include <stdio.h>
#include "ponto.h"

int main(){

	Ponto * p = ponto_cria(10.00, 6.00);
	Ponto * q = ponto_cria(9.00, 11.00);

	float dist = ponto_distancia(p,q);
	printf("A distancia entre p e q é: %f\r\n", dist);
	ponto_libera(p);
	ponto_libera(q);
	return 0;
}
