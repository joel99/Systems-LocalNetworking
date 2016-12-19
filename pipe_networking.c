#include "pipe_networking.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

//see 12-14 notes
int client_handshake( int * address ){

  char * ppname;
  sprintf(ppname, "%d", getpid());
  
  mkfifo(ppname, 0644);
    
  int toServer = open("waluigi", O_WRONLY);

  
  int fromServer = open(ppname, O_RDONLY);

  //send pipename to server
  write(toServer, ppname, strlen(ppname));
  
  //wait for confirmation from server
  char confirm[8];
  read(fromServer, confirm, 8);
  if (!strcmp(confirm, "confirm\n")){
    //connected
    remove(ppname);
  }
  
  return toServer;
}


//gets a client pipe - server connects as reader, client connects
int server_handshake( int * address ){

  //well known pipe
  mkfifo("waluigi", 0644);

  int fromClient = open("waluigi", O_RDONLY);

  char buf[64];
  read(fromClient, buf, sizeof(buf));

  int toClient = open(buf, O_WRONLY);
  write( toClient, "confirm\n", 8);
  remove("waluigi");
  
  return toClient;
}
