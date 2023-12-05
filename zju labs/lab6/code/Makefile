all: server client

server: server.c
	gcc -o server -pthread server.c

client: client.c
	gcc -o client -pthread client.c

reb: server.c
	rm server
	gcc -o server -pthread server.c
	./server

clean:
	rm server client
