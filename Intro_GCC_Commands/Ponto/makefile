#makefile

all: ExecPontoProg

ExecPontoProg: ponto.o progponto.o
	gcc -o ExecPontoProg ponto.o progponto.o -lm

progponto.o: progponto.c
	gcc -c progponto.c

ponto.o: ponto.c
	gcc -c ponto.c

clean: 
	rm -rf *.o

rmproper: clean
	rm -rf ExecPontoProg

run: ExecPontoProg
	./ExecPontoProg

