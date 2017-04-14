all: server client
server: server.cpp
	g++ server.cpp -o server -std=gnu++11 -lpthread -ltcp_socket
client: client.cpp
	g++ client.cpp -o client -std=gnu++11 -lpthread -ltcp_socket
