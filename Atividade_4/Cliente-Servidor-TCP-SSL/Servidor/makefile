all: mainServidorSSL

mainServidorSSL: mainServidorSSL.c
	gcc -Wall -o mainServidorSSL mainServidorSSL.c -L/usr/lib -lssl -lcrypto
	
clean:
	rm -rf *.o


