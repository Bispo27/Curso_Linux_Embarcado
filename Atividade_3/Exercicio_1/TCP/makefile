libTCP.so: TCP_Lib.o
	gcc -shared -o libTCP.so TCP_Lib.o
TCP_Lib.o:	TCP_Lib.c
	gcc -c -Wall -Werror -fpic TCP_Lib.c

clean:
	rm -rf *.o

