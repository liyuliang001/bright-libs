#ifndef BRIGHT_LIB_TCP_SOCKET_CLIENT_HPP
#define BRIGHT_LIB_TCP_SOCKET_CLIENT_HPP

#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

#include "tcp_socket.hpp"

namespace bright_lib{
namespace tcp_socket{

class Client: public TcpSocket{
public:
	Client();
	int connect(std::string ip, uint16_t port);
	//uint16_t get_local_port();
	~Client();
};

}
}

#endif /* BRIGHT_LIB_TCP_SOCKET_CLIENT_HPP */
