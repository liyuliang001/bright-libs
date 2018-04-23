#ifndef BRIGHT_LIB_PCAP_RECORD_HPP
#define BRIGHT_LIB_PCAP_RECORD_HPP
#include "packet.hpp"
namespace bright_lib{

class PcapRecord{
	public:
		timeval ts;
		Packet packet;

		double get_ts_double() const;
		int parse(const unsigned char *packet, pcap_pkthdr &hdr);
		int parse_no_l2(const unsigned char *packet, pcap_pkthdr &hdr);
		std::string to_str() const;
		std::string to_readable() const;
}; /* class PcapRecord */

} /* namespace bright_lib */
#endif /* BRIGHT_LIB_PCAP_RECORD_HPP */
