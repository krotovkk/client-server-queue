all: client server

client: client.c
		gcc -o client client.c

server: queue.o TList.o server.c
		gcc queue.o TList.o -o server server.c

queue.o: queue.c
		gcc -c queue.c

TList.o: TList.c
		gcc -c TList.c 


clean:
		rm -rf *.o client server