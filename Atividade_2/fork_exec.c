#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

void main (int argc, char * argv[]) { 
	char *binaryPath = "/bin/ls";
	char *args[] = {binaryPath, "-lh", "/home", NULL};

	pid_t ret = fork(); 
	if (ret < 0) { 
		perror("Fork failed: ");
		exit(-1);
	} else {
		if (ret == 0) { 
			printf("Child PID: %d - Fork return: %d\n", getpid(), ret); 
			execv(binaryPath, args); // Eu coloco o processo filho para executar a função do arquivo "binaryPath"
		} else { 
			printf("Parent PID: %d - Fork return: %d\n", getpid(), ret);
		}
	}
	printf("[PID: %d] Finishing process.\n", getpid()); 
}
