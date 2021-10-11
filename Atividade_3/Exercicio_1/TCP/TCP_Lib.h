#include <netinet/in.h>

typedef struct{
    unsigned short port;
    char sendbuf[1024];
    char recvbuf[1024];
    struct sockaddr_in client;
    struct sockaddr_in server;
    int s;  /* Socket para aceitar conexoes       */
    int ns; /* Socket conectado ao cliente        */
    int namelen;
} TCP_Handle_Typedef_Server;

typedef struct{
    char userName[50];
    unsigned short port;       
    char sendbuf[1024];              
    char recvbuf[1024];              
    struct hostent *hostnm;    
    struct sockaddr_in server; 
    int s; //socket para aceitar conexão
}TCP_Handle_Typedef_Client;

 enum HeaderMsg{
    CMD = 0x00, START, STOP, SYNC
};

void TCP_Init_Server(TCP_Handle_Typedef_Server * TCP);

void TCP_SendMsg_Server(TCP_Handle_Typedef_Server * TCP, uint8_t * buff, uint16_t size);

void TCP_RecvMsg_Server(TCP_Handle_Typedef_Server * TCP);

void TCP_Open_Server(TCP_Handle_Typedef_Server * TCP);

void TCP_Close_Server(TCP_Handle_Typedef_Server * TCP);

void TCP_Init_Client(TCP_Handle_Typedef_Client * TCP);

void TCP_SendMsg_Client(TCP_Handle_Typedef_Client * TCP, uint8_t * buff, uint16_t size);

void TCP_RecvMsg_Client(TCP_Handle_Typedef_Client * TCP);

void TCP_Open_Client(TCP_Handle_Typedef_Client * TCP);

void TCP_Close_Client(TCP_Handle_Typedef_Client * TCP);

