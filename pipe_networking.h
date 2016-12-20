#define MESSAGE_BUFFER_SIZE 256
#define HANDSHAKE_BUFFER_SIZE 16

int server_handshake( int * address );

int client_handshake( int * address );

int server_handshake1( char * address );

int server_handshake2( char * address, int from );


