#include "pipe_networking.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

//see 12-14 notes
int client_handshake( int * address ){
  printf("Initializing client\n");
  
  char ppname[100];
  sprintf(ppname, "%d", getpid());
  
  mkfifo(ppname, 0644);
  printf("Created private FIFO\n");

  int toServer = open("waluigi", O_WRONLY);
  printf("Connected to server's wkp\n");

  printf("Client pipe created, waiting for server connection\n");
  
 
  //send pipename to server
  write(toServer, ppname, strlen(ppname) + 1);
  printf("Private pipe name sent to server\n");
  int fromServer = open(ppname, O_RDONLY);
  //wait for confirmation from server
  char confirm[8];
  read(fromServer, confirm, 8);
  if (!strcmp(confirm, "confirm")){
    //connected
    printf("Private pipe removed\n");
    remove(ppname);
  }
  
  write(*address,"go\n", 4);
 
  
  return fromServer;
}


//gets a client pipe - server connects as reader, client connects
int server_handshake( int * address ){

  //well known pipe
  mkfifo("waluigi", 0644);
  printf("Server booted\n");
  int fromClient = open("waluigi", O_RDONLY);
  printf("Client connected\n");
  remove("waluigi");
  
  char buf[64];
  read(fromClient, buf, sizeof(buf));
  printf("private pipe name is %s\n", buf);
  int toClient = open(buf, O_WRONLY);
  write( toClient, "confirm", 8);


  read(fromClient, buf, sizeof(buf));
  printf("Connection confirmed by client: %s\n", buf);
  
  return toClient;
}

int server_handshake1( char * address ){
  mkfifo("waluigi", 0644);
  printf("Starting handshake\n");
  int fromClient = open("waluigi", O_RDONLY);
  printf("Client connected\n");
  read(fromClient, address, HANDSHAKE_BUFFER_SIZE);
  remove("waluigi");
  return fromClient;
}

int server_handshake2( char * address, int from ){
  int toClient = open(address, O_WRONLY);
  printf("Server connected to private pipe %s\n", address);
  char buf[MESSAGE_BUFFER_SIZE];
  write(toClient, "confirm", 8);

  read(from, buf, MESSAGE_BUFFER_SIZE);
  printf("Client handshake confirmed: %s\n", buf);
  
  return toClient;
}

