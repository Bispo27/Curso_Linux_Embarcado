/*
 * server.c: Server program
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

mqd_t qd_server; 

void close_server(int sig) {
    printf("\n");
    printf("Server: Got signal %d.\n", sig);
    printf("Server: Removing server queue.\n");

    if (mq_close(qd_server) == -1) {
        perror("mq_close");
        exit(1);
    }

    if (mq_unlink(SERVER_QUEUE_NAME) == -1) {
        perror("mq_unlink");
        exit(1);
    }
    
    printf("Server: Finished.\n");
    exit(0);
}

int main (int argc, char **argv) {
    mqd_t qd_client;
    char in_buffer[MSG_BUFFER_SIZE];
    char out_buffer[MSG_BUFFER_SIZE];
    long token_number = 1;
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    printf("Server: Started.\n");

    signal(SIGINT, close_server);

    if ((qd_server = mq_open(SERVER_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        perror("mq_open - server");
        exit(1);
    }

    while(1) {
        if (mq_receive(qd_server, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
            perror("mq_receive");
            exit(1);
        }

        printf("Server: Received client_queue_name (%s).\n", in_buffer);

        if ((qd_client = mq_open(in_buffer, O_WRONLY)) == 1) {
            perror("mq_open - client");
            continue;
        }

        sprintf(out_buffer, "%ld", token_number);

        if (mq_send(qd_client, out_buffer, strlen(out_buffer)+1, 0) == -1) {
            perror("mq_send");
            continue;
        }

        printf("Server: Token %ld sent to client.\n", token_number);
        token_number++;
    }
}
