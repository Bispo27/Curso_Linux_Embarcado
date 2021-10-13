#include "TCP_Lib.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    TCP_Handle_Typedef_Client newTCPClient;
    newTCPClient.port = (unsigned short) atoi(argv[1]);
    printf("[0]: %d   [1]: %d  ", atoi(argv[0]), atoi(argv[1]));

    printf("Iniciando o Cliente...\n\n");
    TCP_Init_Client(&newTCPClient);
    TCP_Open_Client(&newTCPClient);
    char msg[100];
    while(1){
        printf("mserv: ");
        scanf("%s", msg);
        //printf("mserv: %s\n", msg);
        TCP_SendMsg_Client(&newTCPClient, (uint8_t*)msg, sizeof(msg));
        TCP_RecvMsg_Client(&newTCPClient);
    }

    TCP_Close_Client(&newTCPClient);

}