compile: server.o client.o
	gcc -o client client.o
	gcc -o server server.o

server.o: server.c pipe_networking.c
	gcc -o server.o server.c pipe_networking.c

fall: fserver.o client.o 
	gcc -o client client.o
	gcc -o fserver fserver.o

fserver.o: fserver.c pipe_networking.c
	gcc -o fserver.o fserver.c pipe_networking.c

client.o: client.c pipe_networking.c
	gcc -o client.o client.c pipe_networking.c

clean:
	rm *~
	rm *.o
