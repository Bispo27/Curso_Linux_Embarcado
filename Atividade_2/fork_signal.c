#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<stdio.h>

void child_handler(int sig) {
	int status;
	wait(&status);
	if (WIFEXITED(status)) {
		printf("Child return: %d\n", WEXITSTATUS(status));
	}
}

void main(char *path, char *argv[]) { 
	int status;
	pid_t ret = fork(); 
	if (ret < 0) { 
		perror("Fork failed: ");
		exit(-1);
	} else {
		if (ret == 0) { 
			printf("Child PID: %d - Fork return: %d\n", getpid(), ret);
			sleep(5);
			exit(1);
		} else { 
			signal(SIGCHLD, child_handler); /* System call que deixa a task pai em wait até que o filho termine de 								    executar e returna "exit"
							    O primeiro filho que retornar o exit, ativa o signal
							  */
			printf("Parent PID: %d - Fork return: %d\n", getpid(), ret);
			while(1) { }
		}
	} 
	printf("[PID: %d] Finishing process.\n", getpid()); 
}
