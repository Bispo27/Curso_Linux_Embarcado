#include <stdio.h>
#include "TCP_Lib.h"
#include <pthread.h>
#include <string.h>

#define MAX_PORTS 3
#define NUM_THREADS MAX_PORTS

int indexTCP = -1;
unsigned short PORT_CONNECTED[MAX_PORTS];

pthread_mutex_t mutex;

int VerificaPorta(unsigned short port);

typedef struct{
    TCP_Handle_Typedef_Server newTCPServer;
    int indexPort;
} thread_arg;

void *process_server(void *arg){
    //pthread_mutex_lock(&mutex);
    thread_arg *targ = (thread_arg *) arg;
    printf("Recebido do cliente %d: ", targ->newTCPServer.client.sin_port);
    printf("%s", targ->newTCPServer.recvbuf);
    char msg[] = "Server --->  Client | Token: ";
    msg[strlen(msg)-1] = targ->indexPort + '0';
    TCP_SendMsg_Server(&(targ->newTCPServer), (uint8_t*)msg, sizeof(msg));

    pthread_mutex_unlock(&mutex);
}

void process_Servidor();

int main(){

//TCP_Handle_Typedef_Server newTCPServer;
    pthread_t process_server_thread[MAX_PORTS];
    thread_arg newThread_arg;
    pthread_mutex_init(&mutex, NULL);
    printf("Iniciando o servidor...\n\n");
    TCP_Init_Server(&(newThread_arg.newTCPServer));
    printf("Abrindo conexão...\n");
        TCP_Open_Server(&(newThread_arg.newTCPServer));
    
    while(1){
        
        TCP_RecvMsg_Server(&(newThread_arg.newTCPServer));
        
        int ret = VerificaPorta(newThread_arg.newTCPServer.port);
        if(ret == -1){
            PORT_CONNECTED[++indexTCP] = newThread_arg.newTCPServer.port;
        } 
        else if(indexTCP >= MAX_PORTS)
        {
            char msg[] = "Falha de conexão... \nnúmero máximo de clientes acessando o servidor\n";
            TCP_SendMsg_Server(&(newThread_arg.newTCPServer), (uint8_t*)msg, sizeof(msg));
        }
    
        pthread_mutex_lock(&mutex);
        void *ret_thread;
        newThread_arg.indexPort = ret;
        pthread_create(&(process_server_thread[indexTCP]), NULL, process_server, &(newThread_arg));
        pthread_join(process_server_thread[indexTCP], &ret_thread);
        
        
    }
    printf("\nFechando conexão\n\n");
    TCP_Close_Server(&(newThread_arg.newTCPServer));

    //char msg[] = "Servidor ---ack-->  Cliente";
    //TCP_SendMsg_Server(&newTCPServer, (uint8_t*)msg, sizeof(msg));

    

}

 int VerificaPorta(unsigned short port){
    for(int i = 0; i < indexTCP; i++){
        if(PORT_CONNECTED[i] == port)
            return i;
    }
    return -1;
 }