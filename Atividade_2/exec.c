#include<unistd.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
	char *binaryPath = "/bin/ls"; //ponteiro de char que aponta pra pasta que eu quero executar
	char *args[] = {binaryPath, "-lh", "/home", NULL}; //argumentos que passa ao executar a "main"

	execv(binaryPath, args); //System call que executa o binário que eu especifiquei

	printf("Finishing process.");
}
