/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(char *msg)
{
    perror(msg);
    exit(1);
}

char * socket_client(int portno, char *hostname, char *message, int message_len) 
{
    int sockfd, n;

    struct sockaddr_in serv_addr; //Structures Defined in netlib.h
    struct hostent *server;       //

    char * buffer;
    buffer = (char*) malloc(256);
    bzero(buffer,256);

    //Open Socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0); //AF_INET creates IP socket, SOCK_STREAM creates TCP socket
    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    printf("%s\n", server->h_name);
    fflush(stdout);

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    //Attempt to connect 
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    n = write(sockfd, message, message_len); //Write Message from buffer to socket
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd, buffer, 255); //Read Socket into Buffer
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer); //Print Response
    return buffer;
}

int socket_server(int portno)  //Args Port
{
     printf("test\n");
     fflush(stdout);
     int sockfd, newsockfd, clilen;
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     char * buffer;
     buffer = (char *) malloc(256);
     bzero(buffer,256);

     //Open Socket
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     
     //Binds socket to address and port (port contained in serv_addr
     if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd, 15); //Listen on bound socket
     printf("listening\n");
     fflush(stdout);

     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen); //blocks process until client connects
     printf("accepted\n");
     fflush(stdout);
     if (newsockfd < 0) 
          error("ERROR on accept");

     n = read(newsockfd,buffer,255); //Reads from socket into buffer
     if (n < 0) error("ERROR reading from socket");

     buffer = socket_client(6379, "127.0.0.1", buffer, 255);

     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,buffer, 255); //Replies to client by writing back into socket
     if (n < 0) error("ERROR writing to socket");
     return 0; 
}

int main(int argc, char *argv[])  //Args Port
{
    socket_server(10001);
}
