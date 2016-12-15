#include "pipe_networking.h"
#include <sys/types.h>
#include <sys/stat.h>

//gets a client pipe - server connects as reader, client connects
int server_handshake( int * address ){
  mkfifo("waluigi", 0644);

  int fd = open("waluigi", O_WRONLY);

  write(fd, "Welcome!\n", 9);
  
  return 0;
}
//see 12-14 notes
int client_handshake( int * address ){
  return 0;
}

