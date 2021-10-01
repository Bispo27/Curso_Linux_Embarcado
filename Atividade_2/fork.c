#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

void main(int argc, char *argv[]) { 
	pid_t ret = fork(); 
	if (ret < 0) { 
		perror("Fork failed: ");
		exit(-1);
	} else {
		if (ret == 0) { 
			printf("Child PID: %d - Fork return: %d\n", getpid(), ret); 
		} else { 
			printf("Parent PID: %d - Fork return: %d\n", getpid(), ret);
		}
	}
	printf("[PID: %d] Finishing process.\n", getpid()); 
} 
