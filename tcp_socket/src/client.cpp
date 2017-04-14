#include <cstdio>
#include "client.hpp"

namespace bright_lib{
namespace tcp_socket{

Client::Client(){
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

Client::~Client(){
	close();
}

}
}
