#include "server.hpp"
#include <cstring>
#include <thread>

using namespace std;

namespace bright_lib{
namespace tcp_socket{

int ServerHandler::handle(int sock, sockaddr_in client_addr){
	this->sockfd = sock;
	this_thread = thread(&ServerHandler::execute, this);
	return 0;
}

}
}
