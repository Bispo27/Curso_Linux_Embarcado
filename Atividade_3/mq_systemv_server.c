/*
 * server.c: Server program
 *           to demonstrate interprocess communication
 *           with System V message queues
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SERVER_QUEUE_KEY 0x00001234
#define QUEUE_PERMISSIONS 0660
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE

struct message_text {
    int qid;
    char buf[MSG_BUFFER_SIZE];
};

struct message {
    long message_type;
    struct message_text message_text;
};

int qid_server;

void close_server(int sig) {
    printf("\n");
    printf("Server: Got signal %d.\n", sig);
    printf("Server: Removing server queue.\n");

    if (msgctl(qid_server, IPC_RMID, NULL) == -1) {
            perror("client: msgctl");
            exit(1);
    }

    printf("Server: Finished.\n");
    exit(0);
}

int main (int argc, char **argv) {
    int qid_client;
    long token_number = 1;
    struct message message;

    printf("Server: Started.\n");
    
    signal(SIGINT, close_server);

    if ((qid_server = msgget(SERVER_QUEUE_KEY, IPC_CREAT | QUEUE_PERMISSIONS)) == -1) {
        perror("msgget");
        exit(1);
    }

    while(1) {
        if (msgrcv(qid_server, &message, sizeof(struct message_text), 0, 0) == -1) {
            perror("msgrcv");
            exit (1);
        }

        printf("Server: Received qid_client (%d).\n", message.message_text.qid);

        sprintf(message.message_text.buf, "%ld", token_number);

        qid_client = message.message_text.qid;

        if (msgsnd(qid_client, &message, sizeof (struct message_text), 0) == -1) {  
            perror("msgsnd");
            continue;
        }

        printf("Server: Token %ld sent to client.\n", token_number);
        token_number++;
    }
}
