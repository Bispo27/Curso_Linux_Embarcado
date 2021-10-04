/*
 * client.c: Client program
 *           to demonstrate interprocess communication
 *           with POSIX message queues
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define SERVER_QUEUE_NAME "/sp-example-server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE

char client_queue_name[64];
mqd_t qd_client;

void close_client(int sig) {
    printf("\n");
    printf("Client: Got signal %d.\n", sig);
    printf("Client: Removing client queue.\n");

    if (mq_close(qd_client) == -1) {
        perror("mq_close");
        exit(1);
    }

    if (mq_unlink(client_queue_name) == -1) {
        perror("mq_unlink");
        exit(1);
    }
    
    printf("Client: Finished.\n");
    exit(0);
}

int main (int argc, char **argv) {
    mqd_t qd_server;
    char in_buffer[MSG_BUFFER_SIZE];
    char temp_buf[10];
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;
    
    signal(SIGINT, close_client);

    sprintf(client_queue_name, "/sp-example-client-%d", getpid());

    if ((qd_client = mq_open(client_queue_name, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        perror("mq_open - client");
        exit(1);
    }

    if ((qd_server = mq_open(SERVER_QUEUE_NAME, O_WRONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        perror("mq_open - server");
        exit(1);
    }

    printf ("Ask for a token (Press <ENTER>).");

    while (fgets(temp_buf, 2, stdin)) {
        if (mq_send(qd_server, client_queue_name, strlen(client_queue_name)+1, 0) == -1) {
            perror("mq_send");
            continue;
        }

        if (mq_receive(qd_client, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
            perror("mq_receive");
            exit(1);
        }
        
        printf("Token received from server: %s\n\n", in_buffer);
        
        printf("Ask for a token (Press <ENTER>).");
    }
}
