#include <stdlib.h> /* malloc , free , exit */
#include <stdio.h> /* printf */
#include <math.h> /* sqrt */
#include "ponto.h"

struct ponto {
	float x;
	float y;
};

 Ponto* ponto_cria (float x, float y)
 {
 	Ponto* p = (Ponto *) malloc(sizeof(Ponto));
 	if (p == NULL) {
 		printf("Memória insuficiente !\n");
 		exit (1);
 	}
 	p->x = x;
 	p->y = y;
 	return p;
 }

 void ponto_libera (Ponto* p)
 {
 	free(p);
 }

 void ponto_acessa (Ponto* p, float* x, float* y)
 {
 	*x = p->x;
 	*y = p->y;
 }

 void ponto_atribui (Ponto* p, float x, float y)
 {
 	p->x = x;
 	p->y = y;
 }

 float ponto_distancia (Ponto* p1, Ponto* p2)
 {
 	float dx = p2->x - p1->x;
 	float dy = p2->y - p1->y;
 	return sqrt(dx*dx + dy*dy);
 }
