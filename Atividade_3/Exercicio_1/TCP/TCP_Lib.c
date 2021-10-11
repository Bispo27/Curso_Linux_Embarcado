#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include "TCP_Lib.h"





void TCP_Init_Server(TCP_Handle_Typedef_Server * TCP){

    TCP->port = (unsigned short) 50000;//(unsigned short) atoi(argv[1]);

    /*
     * Cria um socket TCP (stream) para aguardar conexoes
     */
    if ((TCP->s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket()");
        exit(2);
    }

   /*
    * Define a qual endereco IP e porta o servidor estara ligado.
    * IP = INADDDR_ANY -> faz com que o servidor se ligue em todos
    * os enderecos IP
    */
    TCP->server.sin_family = AF_INET;   
    TCP->server.sin_port   = htons(TCP->port);       
    TCP->server.sin_addr.s_addr = INADDR_ANY;


}

void TCP_Close_Server(TCP_Handle_Typedef_Server * TCP){
/* Fecha o socket conectado ao cliente */
    close(TCP->ns);

    /* Fecha o socket aguardando por conexões */
    close(TCP->s);

    printf("Servidor terminou com sucesso.\n");
    exit(0);

}

void TCP_Open_Server(TCP_Handle_Typedef_Server * TCP){
    /*
     * Liga o servidor a porta definida anteriormente.
     */
    if (bind(TCP->s, (struct sockaddr *)&(TCP->server), sizeof(TCP->server)) < 0)
    {
       perror("Bind()");
       exit(3);
    }

    /*
     * Prepara o socket para aguardar por conexoes e
     * cria uma fila de conexoes pendentes.
     */
    if (listen(TCP->s, 1) != 0)
    {
        perror("Listen()");
        exit(4);
    }

    /*
     * Aceita uma conexao e cria um novo socket atraves do qual
     * ocorrera a comunicacao com o cliente.
     */
    TCP->namelen = sizeof(TCP->client);
    if ((TCP->ns = accept(TCP->s, (struct sockaddr *)&(TCP->client), (socklen_t *)&(TCP->namelen))) == -1)
    {
        perror("Accept()");
        exit(5);
    }
    char msg[] = "Conexão estabelecida";
    TCP_SendMsg_Server(TCP, (uint8_t*)msg, sizeof(msg));
}

void TCP_SendMsg_Server(TCP_Handle_Typedef_Server * TCP, uint8_t * buff, uint16_t size){
    memcpy(TCP->sendbuf, (char*)buff, size);

    /* Envia uma mensagem ao cliente atraves do socket conectado */
    if (send(TCP->ns, TCP->sendbuf, strlen(TCP->sendbuf)+1, 0) < 0)
    {
        perror("Send()");
        exit(7);
    }

}



void TCP_RecvMsg_Server(TCP_Handle_Typedef_Server * TCP){
    /* Recebe uma mensagem do cliente atraves do novo socket conectado */
    if (recv(TCP->ns, TCP->recvbuf, sizeof(TCP->recvbuf), 0) == -1)
    {
        perror("Recv()");
        exit(6);
    }
    printf("%s\n", TCP->recvbuf);

}



void TCP_Init_Client(TCP_Handle_Typedef_Client * TCP){

    char host[] = "localhost";

    TCP->hostnm = gethostbyname(host);

    if (TCP->hostnm == (struct hostent *) 0)
    {
        fprintf(stderr, "Gethostbyname failed\n");
        exit(2);
    }
    //TCP->port = (unsigned short) 50000;

    /*
     * Define o endereco IP e a porta do servidor
     */
    TCP->server.sin_family      = AF_INET;
    TCP->server.sin_port        = htons(TCP->port);
    TCP->server.sin_addr.s_addr = *((unsigned long *)(TCP->hostnm->h_addr));

    /*
     * Cria um socket TCP (stream)
     */
    if ((TCP->s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket()");
        exit(3);
    }
}

void TCP_Open_Client(TCP_Handle_Typedef_Client * TCP){
/* Estabelece conexao com o servidor */
    if (connect(TCP->s, (struct sockaddr *)&(TCP->server), sizeof(TCP->server)) < 0)
    {
        perror("Connect()");
        exit(4);
    }

    strcpy(TCP->sendbuf, "Abrindo conexão");
    /* Envia a mensagem no buffer de envio para o servidor */
    if (send(TCP->s, TCP->sendbuf, strlen(TCP->sendbuf)+1, 0) < 0)
    {
        perror("Send()");
        exit(5);
    }
    printf("%s\n", TCP->sendbuf);
}

void TCP_RecvMsg_Client(TCP_Handle_Typedef_Client * TCP){
/* Recebe a mensagem do servidor no buffer de recepcao */
    if (recv(TCP->s, TCP->recvbuf, sizeof(TCP->recvbuf), 0) < 0)
    {
        perror("Recv()");
        exit(6);
    }
    printf("%s\n", TCP->recvbuf);
}

void TCP_Close_Client(TCP_Handle_Typedef_Client * TCP){
    //Fecha o socket
    close(TCP->s);
    printf("Fechando a conexão TCP");
}

void TCP_SendMsg_Client(TCP_Handle_Typedef_Client * TCP, uint8_t * buff, uint16_t size){
    memcpy(TCP->sendbuf, (char*)buff, size);
    
    if (send(TCP->s, TCP->sendbuf, strlen(TCP->sendbuf)+1, 0) < 0)
    {
        perror("Send()");
        exit(5);
    }
    
}
