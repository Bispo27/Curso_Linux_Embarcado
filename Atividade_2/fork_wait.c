#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<stdio.h>

void main(char *path, char *argv[]) { 
	int status;
	pid_t ret = fork(); 
	if (ret < 0) { 
		perror("Fork failed: ");
		exit(-1);
	} else {
		if (ret == 0) {
			printf("Child PID: %d - Fork return: %d\n", getpid(), ret);
			exit(1);
		} else {
			printf("Parent PID: %d - Fork return: %d\n", getpid(), ret);
			wait(&status);
			if (WIFEXITED(status)) {
				printf("Child return: %d\n", WEXITSTATUS(status));
			}
		}
	}
	printf("[PID: %d] Finishing process.\n", getpid()); 
}
