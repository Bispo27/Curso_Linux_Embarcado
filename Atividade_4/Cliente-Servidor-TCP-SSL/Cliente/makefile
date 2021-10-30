all: mainClienteSSL

mainClienteSSL: mainClienteSSL.c
	gcc -Wall -o mainClienteSSL mainClienteSSL.c -L/usr/lib -lssl -lcrypto
	
clean:
	rm -rf *.o


