#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>

#include <cstdio>
#include <cstring>
#include <pcap.h>

#include <string>
#include <vector>

#include "pcap_record.hpp"

namespace bright_lib{
int parse_pcap(const char* pcap_name, std::vector<PcapRecord> &res);
int parse_pcap_no_l2(const char* pcap_name, std::vector<PcapRecord> &res);
} /* namespace bright_lib */
