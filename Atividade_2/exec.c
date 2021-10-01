#include<unistd.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
	char *binaryPath = "/bin/ls";
	char *args[] = {binaryPath, "-lh", "/home", NULL};

	execv(binaryPath, args);

	printf("Finishing process.");
}
