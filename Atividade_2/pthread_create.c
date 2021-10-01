#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3

typedef struct {
	int idx, value;
} thread_arg;

void *thread_func(void *arg) {
	thread_arg *targ = (thread_arg *) arg;
	printf("[Thread ID: %ld] Index: %d – Value: %d\n", pthread_self(), targ->idx, targ->value);
}

int main(int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS];
	thread_arg arguments[NUM_THREADS];
	int i;
	for(i=0; i<NUM_THREADS; i++) {
		arguments[i].idx = i;
		arguments[i].value = i*10;
		pthread_create(&(threads[i]), NULL, thread_func, &(arguments[i]));
	}
	for(i=0; i<NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}
}
