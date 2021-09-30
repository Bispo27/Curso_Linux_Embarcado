all: algMath.so


algMath.so: algMath.o 
	gcc -shared -o libAlgMath.so algMath.o

algMath.o: algMath.c
	gcc -c -Wall -Werror -fpic algMath.c -lm

clean:
	rm algMath.o algMath.so


