#include "pcap_parser.hpp"
#include "pcap.h"
using namespace std;

namespace bright_lib{
int parse_pcap(const char *pcap_name, vector<PcapRecord> &res){
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
        err = p.parse(packet, header);
        res.push_back(p);
    }
    return 0;
}
} /* namespace bright_lib */
