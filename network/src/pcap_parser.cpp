#include "pcap_parser.hpp"
#include "pcap.h"
using namespace std;

namespace bright_lib{
static int parse_pcap_base(const char *pcap_name, vector<PcapRecord> &res, int has_l2){
    res.clear();
    pcap_t *pcap;
    pcap_pkthdr header;
    const unsigned char *packet;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap = pcap_open_offline(pcap_name, errbuf);
    if (pcap == NULL){
        fprintf(stderr, "Invalid pcap file %s\n", pcap_name);
        return 1;
    }

    while ((packet = pcap_next(pcap, &header)) != NULL){
        PcapRecord p;
        int err = 0;
		if (has_l2)
			err = p.parse(packet, header);
		else
			err = p.parse_no_l2(packet, header);
        res.push_back(p);
    }
    return 0;
}

int parse_pcap(const char *pcap_name, vector<PcapRecord> &res){
	return parse_pcap_base(pcap_name, res, 1);
}

int parse_pcap_no_l2(const char* pcap_name, std::vector<PcapRecord> &res){
	return parse_pcap_base(pcap_name, res, 0);
}
} /* namespace bright_lib */
