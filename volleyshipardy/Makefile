all: client server

client: client.cc
	g++ -pthread -O3 -g -o client client.cc -lgtest -std=c++2a

server: server.cc
	g++ -pthread -O3 -g -o server server.cc -lgtest -std=c++2a

clean:
	rm -f *.o a.out core
