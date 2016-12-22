#ifndef PCAP_RECORD_HPP
#define PCAP_RECORD_HPP
#include "packet.hpp"
namespace bright_lib{

class PcapRecord{
	public:
		timeval ts;
		Packet packet;

		double get_ts_double() const;
		int parse(const unsigned char *packet, pcap_pkthdr &hdr);
		std::string to_str() const;
		std::string to_readable() const;
}; /* class PcapRecord */

} /* namespace bright_lib */
#endif /* PCAP_RECORD_HPP */
