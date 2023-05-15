all: client server

client: client.cc common.h
	g++ -pthread -O3 -g -o client client.cc -lgtest

server: server.cc common.h
	g++ -pthread -O3 -g -o server server.cc -lgtest

clean:
	rm -f *.o a.out core
