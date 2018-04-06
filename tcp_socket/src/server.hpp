#ifndef BRIGHT_LIB__TCP_SOCKET__SERVER_HPP
#define BRIGHT_LIB__TCP_SOCKET__SERVER_HPP

#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <thread>
#include <vector>
#include <cstring>

#include "tcp_socket.hpp"

namespace bright_lib{
namespace tcp_socket{

class ServerHandler: public TcpSocket{
public:
	std::thread this_thread;

	virtual int execute() = 0;
	int handle(int sock, sockaddr_in client_addr);
};

template<class T>
class Server{
public:
	int sockfd;
	std::thread listen_thread;
	std::vector<T*> handlers;

	int __listen(uint16_t port, int n_concurrent){
		while (1){
			sockaddr_in client_addr;
			socklen_t client_addr_len = sizeof(client_addr);
			int client_sock = accept(sockfd, (sockaddr *) &client_addr, &client_addr_len);
			handlers.push_back(new T);
			handlers.back()->handle(client_sock, client_addr);
		}
		return 0;
	}
	int listen(uint16_t port, int n_concurrent, bool daemon){
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (sockfd < 0)
			return -1;
		sockaddr_in server_addr;
		memset(&server_addr, 0, sizeof(sockaddr_in));
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = INADDR_ANY;
		server_addr.sin_port = htons(port);
		if (bind(sockfd, (sockaddr *) &server_addr, sizeof(server_addr)) < 0)
			return -2;
		::listen(sockfd, n_concurrent);

		if (daemon){
			listen_thread = std::thread(&Server::__listen, this, port, n_concurrent);
		}else {
			__listen(port, n_concurrent);
		}
		return 0;
	}
};

}
}

#endif /* BRIGHT_LIB__TCP_SOCKET__SERVER_HPP */
