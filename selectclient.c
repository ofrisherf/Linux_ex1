// Ex. 1
// Client for Beej's server
// Ofri Sherf
// 312481112

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFERSIZE 1024

int receiveInput(char* buf, int size)
{
  int c,counter = 0;
  
  while((c = getchar()) != '\n')
  {
    if(counter < size)
    {
      buf[counter++] = c;
    }
  }
  
  buf[counter]=c;

  // Terminate the string
  buf[++counter] = '\0';

  // Length of the string
  return counter;
}

int main()
{
  fd_set readfds;

  int clientSocket;
  char buffer[BUFFERSIZE];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  char message[BUFFERSIZE];

  // Create the socket. The three arguments are:
  // Internet domain, Stream socket, Default protocol (TCP)
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  
  // Configure settings of the server address struct
  // Address family = Internet
  serverAddr.sin_family = AF_INET;

  // Set port number, using htons function to use proper byte order
  serverAddr.sin_port = htons(9034);

  // Set IP address to localhost
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  // Set all bits of the padding field to 0
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  // Connect the socket to the server using the address struct
  addr_size = sizeof serverAddr;
  connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

  memset(message, '\0',BUFFERSIZE);
  FD_ZERO(&readfds);
  FD_SET(clientSocket, &readfds);
  FD_SET(0, &readfds);

  while(1)
  {
    select(clientSocket+1, &readfds, NULL, NULL, NULL);
    
    // Got something from STDIN
    if(FD_ISSET(0, &readfds))
    {
      // Read from stdin
      receiveInput(message, BUFFERSIZE);
      if(strcmp(message,"exit") == 0)
      {
        goto gracefulExit;
      }
      // Send to server
      send(clientSocket, message, BUFFERSIZE, 0);

      // Set all bits of the padding field to 0
      memset(message, '\0',BUFFERSIZE);
      FD_ZERO(&readfds);
      FD_SET(clientSocket, &readfds);
      FD_SET(0, &readfds);
    }
    // Got something from the server
    else if(FD_ISSET(clientSocket, &readfds))
    {
      // Read the message from the server into the buffer
      recv(clientSocket, buffer, BUFFERSIZE, 0);

      // Print the received message
      printf("Data received: %s",buffer);
      FD_ZERO(&readfds);
      FD_SET(clientSocket, &readfds);
      FD_SET(0, &readfds);
    }
  }   

gracefulExit:
  close(clientSocket);

  return 0;
}
