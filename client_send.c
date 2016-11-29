#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
 
void client_send(char message[128])
{
    int socket_desc;
    struct sockaddr_in server;
     
    //Create socket
    if ((socket_desc = socket(AF_INET , SOCK_STREAM , 0)) == -1)
    {
	return 1;
    }
         
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 80 );
 
    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        return 1;
    }
     
    //Send some data
    if( send(socket_desc , message , 128 , 0) < 0)
    {
        return 1;
    }     
    return 0;
}
