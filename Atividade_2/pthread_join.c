#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3

typedef struct {
	int idx, value;
} thread_arg;

void *thread_func(void *arg) {
	thread_arg *targ = (thread_arg *) arg;
	int *pvalue = (int *)malloc(sizeof(int));
	*pvalue = targ->value;
	printf("[Thread ID: %ld] Index: %d – Value: %d\n", pthread_self(), targ->idx, targ->value);
	pthread_exit(pvalue);
}

int main(int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS];
	thread_arg arguments[NUM_THREADS];
	int i;
	void *ret;
	for(i=0; i<NUM_THREADS; i++) {
		arguments[i].idx = i;
		arguments[i].value = i*10;
		pthread_create(&(threads[i]), NULL, thread_func, &(arguments[i]));
	}
	for(i=0; i<NUM_THREADS; i++) {
		if (pthread_join(threads[i], &ret) == 0) {
			printf("Thread ID: %ld - Return: %d\n", threads[i], *(int *)ret);
		}
	}
}
