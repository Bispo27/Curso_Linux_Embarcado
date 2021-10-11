#include <netinet/in.h>

typedef struct
{
    unsigned short port;
    char sendbuf[1024];
    char recvbuf[1024];
    struct sockaddr_in client;
    struct sockaddr_in server;
    int s;  /* Socket para aceitar conexoes       */
    int ns; /* Socket conectado ao cliente        */
    int namelen;
} TCP_Typedef_Handle;