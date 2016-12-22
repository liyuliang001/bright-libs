#include <cstdio>
#include <bright_lib/network/pcap_parser.hpp>
using namespace bright_lib;
using namespace std;
int main(){
	vector<PcapRecord> res;
	parse_pcap("test.pcap", res);
	printf("%lu\n", res.size());
	for (int i = 0; i < (int)res.size(); i++){
		printf("%s\n", res[i].to_readable().c_str());
	}
	return 0;
}
