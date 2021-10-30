all: mainTesteServidor

all: mainTesteCliente

mainTesteServidor: mainTesteServidor.o
	gcc -o mainTesteServidor mainTesteServidor.o -lTCP -lpthread

mainTesteServidor.o:	mainTesteServidor.c
	gcc -c mainTesteServidor.c -libTCP


mainTesteCliente: mainTesteCliente.o
	gcc -o mainTesteCliente mainTesteCliente.o -lTCP -lpthread

mainTesteCliente.o:		mainTesteCliente.c
	gcc -c mainTesteCliente.c -libTCP

clean:
	rm -rf *.o


