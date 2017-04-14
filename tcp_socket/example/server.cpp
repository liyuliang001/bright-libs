#include <cstdio>
#include <bright_lib/tcp_socket/server.hpp>
using namespace std;
using namespace bright_lib::tcp_socket;

class TestHandler: public ServerHandler{
public:
	string local_ip, peer_ip;
	uint16_t local_port, peer_port;
	virtual int execute(){
		local_ip = get_local_ip_str();
		peer_ip = get_peer_ip_str();
		local_port = get_local_port();
		peer_port = get_peer_port();
		printf("local: %s:%hu\n", local_ip.c_str(), local_port);
		printf("peer: %s:%hu\n", peer_ip.c_str(), peer_port);
		char buf[10000];
		int x;
		recv(x);
		printf("%x\n", x);
		x = 0xdead;
		send(x);
		string s;
		recv(s);
		printf("%s\n", s.c_str());
		s = "world";
		send(s);
		close();
	}
};

int main(int argc, char **argv){
	if (argc != 2){
		printf("Usage: ./server <port>\n");
		return 0;
	}
	int ret;
	Server<TestHandler> s;
	uint16_t port = stoi(argv[1]);
	while (ret = s.listen(port, 1, true) < 0){
		port++;
	}
	printf("listen to %d\n", port);
	while (1){
		usleep(1000000);
		if (s.handlers.size() > 0){
			for (int i = 0; i < (int)s.handlers.size(); i++)
				printf("[%s:%hu] ", s.handlers[i]->peer_ip.c_str(), s.handlers[i]->peer_port);
			printf("connected\n");
		}
	}
	s.listen_thread.join();
	return 0;
}
