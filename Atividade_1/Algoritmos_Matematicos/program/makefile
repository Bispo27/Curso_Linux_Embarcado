all: Operacoes.exe


Operacoes.exe: Operacoes.o
			   gcc -Wall -o Derivada Operacoes.c -lAlgMath

Operacoes.o: Operacoes.c
			 gcc -c Operacoes.c
clean:
	rm Operacoes.o Operacoes.c

run: Operacoes
	./Operacoes