#include <cstdio>
#include <string>
#include <bright_lib/tcp_socket/client.hpp>
using namespace std;
using namespace bright_lib::tcp_socket;

int main(int argc, char **argv){
	if (argc != 3){
		printf("Usage: ./client <server_ip> <server_port>\n");
		return 0;
	}

	string ip = argv[1];
	uint16_t port = stoi(argv[2]);

	int ret;
	Client c;
	while (ret = c.connect(ip, port) < 0){
		port ++;
	}
	printf("connect ot %hu\n", port);
	printf("local: %s:%hu\n", c.get_local_ip_str().c_str(), c.get_local_port());
	printf("peer: %s:%hu\n", c.get_peer_ip_str().c_str(), c.get_peer_port());
	int x = 0x1108;
	c.send(x);
	c.recv(x);
	printf("%x\n", x);
	string s = "hello";
	c.send(s);
	c.recv(s);
	printf("%s\n", s.c_str());
	return 0;
}
