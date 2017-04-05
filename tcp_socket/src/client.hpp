#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>

namespace bright_lib{
namespace tcp_socket{

class Client{
public:
	int sockfd;

	Client();
	int connect(std::string ip, uint16_t port);
	uint16_t get_local_port();

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

	int send_len(char* buf, int len);

	template<class T> 
	int send(T &buf){
		if (send_len((char*)&buf, (int)sizeof(buf)) == -1)
			return -1;
		return 0;
	}
	int send(std::string &buf){
		int len = buf.size();
		if (send(len) == -1)
			return -1;
		if (send_len(&buf[0], (int)buf.size()) == -1)
			return -1;
		return 0;
	}
	~Client();
};

}
}

#endif /* CLIENT_HPP */
