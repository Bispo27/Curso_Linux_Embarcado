#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

void main(int argc, char *argv[]) { 
	pid_t ret = fork(); // system call que começa um processo filho e retorna o processe ID da task filho
	if (ret < 0) { //  Verifica se a task filho foi criada com sucesso
		perror("Fork failed: ");
		exit(-1);
	} else { // Se chegou aqui, o processo filho está rodando junto
		if (ret == 0) { //Se ret == 0, então é o processo filho que está rodando
			printf("Child PID: %d - Fork return: %d\n", getpid(), ret); 
		} else { // Se ret != 0, então é o processo pai que está rodando
			printf("Parent PID: %d - Fork return: %d\n", getpid(), ret);
		}
	}
	printf("[PID: %d] Finishing process.\n", getpid()); //Aqui as tasks finalizam e é printado o PID do processo
} 
