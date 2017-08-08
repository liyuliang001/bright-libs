#include "tcp_socket.hpp"
#include <netinet/tcp.h>
using namespace std;

namespace bright_lib{
namespace tcp_socket{

TcpSocket::TcpSocket(){
	this->sockfd = 0;
}

TcpSocket::~TcpSocket(){
	close();
}

void TcpSocket::close(){
	if (sockfd != 0){
		::close(sockfd);
		sockfd = 0;
	}
}

uint16_t TcpSocket::get_local_port(){
	struct sockaddr_in sin;
	socklen_t addrlen = sizeof(sin);
	if(getsockname(sockfd, (struct sockaddr *)&sin, &addrlen) == 0 && sin.sin_family == AF_INET && addrlen == sizeof(sin))
		return ntohs(sin.sin_port);
	return 0;
}

uint16_t TcpSocket::get_peer_port(){
	struct sockaddr_in sin;
	socklen_t addrlen = sizeof(sin);
	if(getpeername(sockfd, (struct sockaddr *)&sin, &addrlen) == 0 && sin.sin_family == AF_INET && addrlen == sizeof(sin))
		return ntohs(sin.sin_port);
	return 0;
}

string TcpSocket::get_local_ip_str(){
	struct sockaddr_in sin;
	socklen_t addrlen = sizeof(sin);
	if(getsockname(sockfd, (struct sockaddr *)&sin, &addrlen) == 0 && sin.sin_family == AF_INET && addrlen == sizeof(sin))
		return inet_ntoa(sin.sin_addr);
	return "0.0.0.0";
}

string TcpSocket::get_peer_ip_str(){
	struct sockaddr_in sin;
	socklen_t addrlen = sizeof(sin);
	if(getpeername(sockfd, (struct sockaddr *)&sin, &addrlen) == 0 && sin.sin_family == AF_INET && addrlen == sizeof(sin))
		return inet_ntoa(sin.sin_addr);
	return "0.0.0.0";
}

ssize_t TcpSocket::recv_raw(char* buf, int len){
	return ::recv(sockfd, buf, len, 0);
}
int TcpSocket::recv_len(char* buf, int len){
	int ret = 0, cur = 0;
	while (len > cur && (ret = ::recv(sockfd, buf+cur, len-cur, 0)) != -1)
		cur += ret;
	if (ret == -1)
		return -1;
	return 0;
}

ssize_t TcpSocket::send_raw(const char* buf, int len){
	return ::send(sockfd, buf, len, 0);
}
int TcpSocket::send_len(const char* buf, int len){
	int ret = 0, cur = 0;
	while (len > cur && (ret = ::send(sockfd, buf+cur, len-cur, 0)) != -1)
		cur += ret;
	if (ret == -1)
		return -1;
	return 0;
}

int TcpSocket::set_quickack(int v){
	setsockopt(sockfd, IPPROTO_TCP, TCP_QUICKACK, &v, sizeof(v));
}

int TcpSocket::set_nodelay(int v){
	setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, &v, sizeof(v));
}

}
}
