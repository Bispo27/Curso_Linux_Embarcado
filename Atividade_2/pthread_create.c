#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3

typedef struct {
	int idx, value;
} thread_arg;

//Função da thread
void *thread_func(void *arg) {
	thread_arg *targ = (thread_arg *) arg;
	printf("[Thread ID: %ld] Index: %d – Value: %d\n", pthread_self(), targ->idx, targ->value);
}

int main(int argc, char *argv[]) {
	pthread_t threads[NUM_THREADS]; //vetor de threads
	thread_arg arguments[NUM_THREADS]; //vetor da struct thread_arg
	int i;
	for(i=0; i<NUM_THREADS; i++) {
		arguments[i].idx = i;
		arguments[i].value = i*10;
		pthread_create(&(threads[i]), NULL, thread_func, &(arguments[i])); //Função que cria a thread
	}
	for(i=0; i<NUM_THREADS; i++) {
		pthread_join(threads[i], NULL); //Função que coloca a thread pra rodar
	}
}
