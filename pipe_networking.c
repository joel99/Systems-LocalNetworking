#include "pipe_networking.h"
#include <sys/types.h>
#include <sys/stat.h>

//see 12-14 notes
int client_handshake( int * address ){
  
  int fd = open("waluigi", O_WRONLY);

  mkfifo("test", 0644);
  
  int fromClient = open("test", O_RDONLY);

  write(fd, "test", 4);
  
  
  return 0;
}


//gets a client pipe - server connects as reader, client connects
int server_handshake( int * address ){
  mkfifo("waluigi", 0644);

  int fd = open("waluigi", O_RDONLY);

  //write(fd, "Welcome!\n", 9);
  char buf[64];
  read("waluigi", buf, sizeof(buf));

  int toClient = open(buf, O_WRONLY);
  write( toClient, "SCP\n", 4);
  remove("waluigi");
  
  return 0;
}
