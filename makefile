compile: server fserver client

server: server.o pipe_networking.o
	gcc -o server server.o pipe_networking.o

server.o: server.c pipe_networking.h
	gcc -c server.c

fserver: fserver.o pipe_networking.o
	gcc -o fserver fserver.o pipe_networking.o

fserver.o: fserver.c pipe_networking.h
	gcc -c fserver.c
	
client: client.o pipe_networking.o
	gcc -o client client.o pipe_networking.o

client.o: client.c pipe_networking.h
	gcc -o client.o client.c

pipe_networking.o: pipe_networking.c
	gcc -c pipe_networking.c

clean:
	rm -f *~ *.o server fserver client



