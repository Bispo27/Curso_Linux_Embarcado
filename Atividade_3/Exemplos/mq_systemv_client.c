/*
 * client.c: Client program
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

int qid_client;

void close_client(int sig) {
    printf("\n");
    printf("Client: Got signal %d.\n", sig);
    printf("Client: Removing client queue.\n");

    if (msgctl(qid_client, IPC_RMID, NULL) == -1) {
            perror("client: msgctl");
            exit(1);
    }

    printf("Client: Finished.\n");
    exit(0);
}

int main (int argc, char **argv) {
    int qid_server;
    char temp_buf[10];
    struct message message;

    signal(SIGINT, close_client);
    
    if ((qid_server = msgget(SERVER_QUEUE_KEY, 0)) == -1) {
        perror ("msgget: qid_server");
        exit (1);
    }

    if ((qid_client = msgget(IPC_PRIVATE, 0660)) == -1) {
        perror ("msgget: qid_client");
        exit (1);
    }

    message.message_type = 1;
    message.message_text.qid = qid_client;

    printf ("Ask for a token (Press <ENTER>).");

    while (fgets(temp_buf, 2, stdin)) {
        if (msgsnd(qid_server, &message, sizeof(struct message_text), 0) == -1) {
            perror("msgsnd");
            exit(1);
        }

        if (msgrcv(qid_client, &message, sizeof(struct message_text), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        printf("Token received from server: %s\n\n", message.message_text.buf);  

        printf("Ask for a token (Press <ENTER>).");
    }
}
