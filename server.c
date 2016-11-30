#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
 
int main()
{
  int socket_desc , new_socket , c, ret, read_size, csock, ssock;
  struct sockaddr_in server, client;
  char message[128];
  char *filename;
  FILE *fp;
	 
  //Open File
  filename = "log.txt";
  fclose(fopen(filename, "w+"));
	
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 80 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("bind failed");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    //infinite runtime for the server (or util user runs CTRL_C
    while(1)
    {
      new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
      if (new_socket < 0)
      {
        puts("Unable to make connection\n");
        exit(0);
      }

      //TODO: Might need to mess with memset to clear space for message


      puts("Connection accepted");
      /*if( recv(socket_desc, message , 128 , 0) < 0)*/
      if (read(new_socket, message, sizeof(message)) <= 0)
      {
        puts("recv failed");
      } 
      else 
      {
        //open up file for append
        fp = fopen(filename, "a+");
        puts("something");
        //print to and close logfile when done to ensure it can be read
	fprintf(fp, "%s\n", message);
        fclose(fp);
      }
    }
    puts("done with socket");
     
    close(new_socket);
    close(socket_desc);
    fclose(fp);
    printf("End connection\n");
    return 0;
 
    //TODO: Add signal to safe exit program
}

