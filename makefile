compile: client.c server.c pipe_networking.h pipe_networking.c 
	gcc client.c -o client
	gcc server.c -o server
	gcc pipe_networking.c -o pipe_networking

clean:
	rm *~
	rm *.o
