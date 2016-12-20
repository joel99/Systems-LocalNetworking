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
  
  write(toServer,"go", 3);
 
  
  return toServer;
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
  printf("Apparently their private pipe name is %s\n", buf);
  int toClient = open(buf, O_WRONLY);
  write( toClient, "confirm", 8);


  read(fromClient, buf, sizeof(buf));
  printf("Connection confirmed by client: %s\n", buf);
  
  return toClient;
}

int server_handshake1( char * address ){
  return 0;
}

int server_handshake2( char * address, int from ){
  return 0;
}

