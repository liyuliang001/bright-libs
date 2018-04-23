#ifndef BRIGHT_LIB_PACKET_HPP
#define BRIGHT_LIB_PACKET_HPP

#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <pcap.h>
#include <string>

#include <bright_lib/serde/serde.hpp>

namespace bright_lib{
/*
 * Packet parser that get timestamp, srcip, dstip, srcport, dstport, protocol, and ipid
 */
class Packet{
public:
	uint8_t dmac[6], smac[6];
	in_addr srcip, dstip;
	uint32_t sip, dip;
	uint16_t sport, dport;
	uint8_t prot; 
	uint16_t ipid;
	uint32_t seq;
	uint32_t ack;
	uint32_t size;
	uint8_t flags;
	uint16_t dsize, ip_size;

	int parse_base(const unsigned char *packet, pcap_pkthdr &hdr, int has_l2);
	int parse(const unsigned char *packet, pcap_pkthdr &hdr);
	int parse_no_l2(const unsigned char *packet, pcap_pkthdr &hdr);
	void serialize(Serializer &ser) const;
	void deserialize(Deserializer &des);
	std::string to_str() const;
	std::string to_readable() const;
	std::string get_flow_id() const;
	std::string str_srcip() const;
};

} /* namespace bright_lib */

#endif /* BRIGHT_LIB_PACKET_HPP */
