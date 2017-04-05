#include "client.hpp"

namespace bright_lib{
namespace tcp_socket{

Client::Client(){
	sockfd = 0;
}

int Client::connect(std::string ip, uint16_t port){
	sockaddr_in master_addr;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		return -1;
	master_addr.sin_family = AF_INET;
	inet_aton(ip.c_str(), &master_addr.sin_addr);
	master_addr.sin_port = htons(port);
	if (::connect(sockfd,(struct sockaddr *)&master_addr,sizeof(master_addr)) < 0) 
		return -2;
	return 0;
}

int Client::close(){
	if (sockfd != 0){
		::close(sockfd);
		sockfd = 0;
	}
}

uint16_t Client::get_local_port(){
	struct sockaddr_in sin;
	socklen_t addrlen = sizeof(sin);
	if(getsockname(sockfd, (struct sockaddr *)&sin, &addrlen) == 0 &&
			sin.sin_family == AF_INET &&
			addrlen == sizeof(sin))
	{
		return ntohs(sin.sin_port);
	}
	return 0;
}

int Client::recv_len(char* buf, int len){
	int ret = 0, cur = 0;
	while (len > cur && (ret = ::recv(sockfd, buf+cur, len-cur, 0)) != -1)
		cur += ret;
	if (ret == -1)
		return -1;
	return 0;
}

int Client::send_len(char* buf, int len){
	int ret = 0, cur = 0;
	while (len > cur && (ret = ::send(sockfd, buf+cur, len-cur, 0)) != -1)
		cur += ret;
	if (ret == -1)
		return -1;
	return 0;
}

Client::~Client(){
	if (sockfd != 0){
		::close(sockfd);
		sockfd = 0;
	}
}

}
}
