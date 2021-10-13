#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
 * Servidor UDP
 */
int main()
{
   int sockint,s, namelen, client_address_size;
   struct sockaddr_in client, server;
   char buf[32];

   /*
    * Cria um socket UDP (dgram). 
    */
   if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
       perror("socket()");
       exit(1);
   }

   /*
    * Define a qual endereco IP e porta o servidor estara ligado.
    * Porta = 0 -> faz com que seja utilizada uma porta qualquer livre.
    * IP = INADDDR_ANY -> faz com que o servidor se ligue em todos
    * os enderecos IP
    */
   server.sin_family      = AF_INET;   /* Tipo do endereço             */
   server.sin_port        = 0;         /* Escolhe uma porta disponível */
   server.sin_addr.s_addr = INADDR_ANY;/* Endereço IP do servidor      */

   /*
    * Liga o servidor à porta definida anteriormente.
    */
   if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0)
   {
       perror("bind()");
       exit(1);
   }

   /* Consulta qual porta foi utilizada. */
   namelen = sizeof(server);
   if (getsockname(s, (struct sockaddr *) &server, (socklen_t *) &namelen) < 0)
   {
       perror("getsockname()");
       exit(1);
   }

   /* Imprime qual porta foi utilizada. */
    printf("Porta utilizada: %d\n", ntohs(server.sin_port));

   /*
    * Recebe uma mensagem do cliente.
    * O endereco do cliente sera armazenado em "client".
    */
   client_address_size = sizeof(client);
   if(recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &client, (socklen_t *) &client_address_size) <0)
   {
       perror("recvfrom()");
       exit(1);
   }

   /*
    * Imprime a mensagem recebida, o endereco IP do cliente
    * e a porta do cliente 
    */
   printf("Recebida a mensagem %s do endereco IP %s da porta %d\n",buf,inet_ntoa(client.sin_addr),ntohs(client.sin_port));

   /*
    * Fecha o socket.
    */
   close(s);
}
