/*
 * client.c: Client program
 *           to demonstrate interprocess communication
 *           with POSIX shared memory
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define SHARED_MEMORY_NAME "/posix-shared-memory"
#define SHARED_MEMORY_PERMISSIONS 0660
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE

#define SERVER_SEMAPHORE_NAME "/posix-server-semaphore"
#define CLIENT_SEMAPHORE_NAME "/posix-client-semaphore"
#define SEMAPHORE_PERMISSIONS 0660

struct shared_memory {
    char buf[MSG_BUFFER_SIZE];
};

void close_client(int sig) {
    printf("\n");
    printf("Client: Got signal %d.\n", sig);
    printf("Client: Finished.\n");
    exit(0);
}

int main (int argc, char **argv) {
    int shmid;
    sem_t *semid_server, *semid_client;
    struct shared_memory *shared_memory_ptr;
    char temp_buf[10];

    signal(SIGINT, close_client);
    
    if ((semid_server = sem_open(SERVER_SEMAPHORE_NAME, O_CREAT, SEMAPHORE_PERMISSIONS, 0)) == SEM_FAILED) {
        perror("sem_open - SERVER_SEMAPHORE_NAME");
        exit(1);
    }

    if ((semid_client = sem_open(CLIENT_SEMAPHORE_NAME, O_CREAT, SEMAPHORE_PERMISSIONS, 0)) == SEM_FAILED) {
        perror("sem_open - CLIENT_SEMAPHORE_NAME");
        exit(1);
    }
  
    if ((shmid = shm_open(SHARED_MEMORY_NAME, O_RDWR | O_CREAT, SHARED_MEMORY_PERMISSIONS)) == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(shmid, sizeof(struct shared_memory)) == -1) {
        perror("ftruncate");
        exit(1);
    }

    if ((shared_memory_ptr = mmap(NULL, sizeof(struct shared_memory), PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0)) == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    
    printf ("Ask for a token (Press <ENTER>).");

    while (fgets(temp_buf, 2, stdin)) {
    	if (sem_wait(semid_client) == -1) {
    	    perror("sem_wait - semid_client");
	    exit(1);
        }

        printf("Token received from server: %s\n\n", shared_memory_ptr->buf);  
        
        if (sem_post(semid_server) == -1) {
    	    perror("sem_post - semid_server");
	    exit(1);
        } 
        
        printf("Ask for a token (Press <ENTER>).");
    }
}
