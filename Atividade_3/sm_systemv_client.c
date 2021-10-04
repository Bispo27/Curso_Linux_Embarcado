/*
 * client.c: Client program
 *           to demonstrate interprocess communication
 *           with System V shared memory
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHARED_MEMORY_KEY 0x00001234
#define SHARED_MEMORY_PERMISSIONS 0660
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE

#define SERVER_SEMAPHORE_KEY 0x00005678
#define CLIENT_SEMAPHORE_KEY 0x00006789
#define SEMAPHORE_PERMISSIONS 0660

struct shared_memory {
    char buf[MSG_BUFFER_SIZE];
};

struct sembuf sem_up[1];
struct sembuf sem_down[1];

void close_client(int sig) {
    printf("\n");
    printf("Client: Got signal %d.\n", sig);
    printf("Client: Finished.\n");
    exit(0);
}

int main (int argc, char **argv) {
    int shmid, semid_server, semid_client;
    struct shared_memory *shared_memory_ptr;
    char temp_buf[10];

    signal(SIGINT, close_client);
    
    sem_up[0].sem_num = 0;
    sem_up[0].sem_op = 1;
    sem_up[0].sem_flg = 0;

    sem_down[0].sem_num = 0;
    sem_down[0].sem_op = -1;
    sem_down[0].sem_flg = 0;

    if ((semid_server = semget(SERVER_SEMAPHORE_KEY, 1, IPC_CREAT | SEMAPHORE_PERMISSIONS)) == -1) {
        perror("semget - SERVER_SEMAPHORE_KEY");
        exit(1);
    }

    if ((semid_client = semget(CLIENT_SEMAPHORE_KEY, 1, IPC_CREAT | SEMAPHORE_PERMISSIONS)) == -1) {
        perror("semget - CLIENT_SEMAPHORE_KEY");
        exit(1);
    }
  
    if ((shmid = shmget(SHARED_MEMORY_KEY, sizeof(struct shared_memory), IPC_CREAT | SHARED_MEMORY_PERMISSIONS)) == -1) {
        perror("shmget");
        exit(1);
    }

    if ((shared_memory_ptr = (struct shared_memory *) shmat(shmid, NULL, 0)) == (struct shared_memory *) -1) {
        perror("shmat");
        exit(1);
    }
    
    printf ("Ask for a token (Press <ENTER>).");

    while (fgets(temp_buf, 2, stdin)) {
    	if (semop(semid_client, sem_down, 1 ) == -1) {
    	    perror("semop - semid_client - sem_down");
	    exit(1);
        }

        printf("Token received from server: %s\n\n", shared_memory_ptr->buf);  
        
        if (semop(semid_server, sem_up, 1 ) == -1) {
    	    perror("semop - semid_server - sem_up");
	    exit(1);
        } 
        
        printf("Ask for a token (Press <ENTER>).");
    }
}
