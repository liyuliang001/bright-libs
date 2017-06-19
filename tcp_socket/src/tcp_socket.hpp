#ifndef BRIGHT_LIB_TCP_SOCKET_TCP_SOCKET_HPP
#define BRIGHT_LIB_TCP_SOCKET_TCP_SOCKET_HPP

#include <stdint.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

namespace bright_lib{
namespace tcp_socket{

class TcpSocket{
public:
	int sockfd;

	TcpSocket();
	~TcpSocket();
	void close();
	uint16_t get_local_port();
	uint16_t get_peer_port();
	std::string get_local_ip_str();
	std::string get_peer_ip_str();

	ssize_t recv_raw(char* buf, int len);
	int recv_len(char* buf, int len);

	template<class T> 
	int recv(T &res){
		if (recv_len((char*)&res, (int)sizeof(res)) == -1)
			return -1;
		return 0;
	}

	int recv(std::string &res){
		int len;
		if (recv(len) == -1)
			return -1;
		res.resize(len);
		if (recv_len(&res[0], len) == -1)
			return -1;
		return 0;
	}

	ssize_t send_raw(const char* buf, int len);
	int send_len(const char* buf, int len);

	template<class T> 
	int send(const T &buf){
		if (send_len((char*)&buf, (int)sizeof(buf)) == -1)
			return -1;
		return 0;
	}
	int send(const std::string &buf){
		int len = buf.size();
		if (send(len) == -1)
			return -1;
		if (send_len(&buf[0], (int)buf.size()) == -1)
			return -1;
		return 0;
	}

	int set_quickack(int v);

};

}
}

#endif /* BRIGHT_LIB_TCP_SOCKET_TCP_SOCKET_HPP */
