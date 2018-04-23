/*
 * Packet parser that get timestamp, srcip, dstip, srcport, dstport, protocol, and ipid
 */

#include <arpa/inet.h>
#include <cstring>
#include "packet.hpp"
using namespace std;

namespace bright_lib{
int Packet::parse_base(const unsigned char *buf, pcap_pkthdr &hdr, int has_l2){
	int caplen = hdr.caplen;
	ether_header *eth_hdr;
	ip *ip_hdr;
	unsigned int IP_header_length;

	if (has_l2){
		/* For simplicity, we assume Ethernet encapsulation. */
		if (caplen < sizeof(ether_header))
			return 1;

		eth_hdr = (ether_header*) buf;
		memcpy(dmac, eth_hdr->ether_dhost, 6);
		memcpy(smac, eth_hdr->ether_shost, 6);

		/* Skip over the Ethernet header. */
		buf += sizeof(ether_header);
		caplen -= sizeof(ether_header);
	}

	/* Didn't capture a full IP header */
	if (caplen < sizeof(ip))
		return 2;
	

	ip_hdr = (ip*) buf;
	IP_header_length = ip_hdr->ip_hl * 4;   /* ip_hl is in 4-byte words */

	/* didn't capture the full IP header including options */
	if (caplen < IP_header_length)
		return 3;

	srcip = ip_hdr->ip_src;
	dstip = ip_hdr->ip_dst;
	sip = ntohl(srcip.s_addr);
	dip = ntohl(dstip.s_addr);
	ipid = ntohs(ip_hdr->ip_id);
	prot = ip_hdr->ip_p;
	size = hdr.len;
	ip_size = ntohs(ip_hdr->ip_len);

	/* L4 header */
	if (ip_hdr->ip_p == IPPROTO_TCP){
		buf += IP_header_length;
		caplen -= IP_header_length;

		if (caplen < sizeof(tcphdr))
			return 5;

		tcphdr *tcp_hdr = (tcphdr*) buf;

		sport = ntohs(tcp_hdr->source);
		dport = ntohs(tcp_hdr->dest);
		seq = ntohl(tcp_hdr->seq);
		ack = ntohl(tcp_hdr->ack_seq);
		flags = tcp_hdr->th_flags;
		dsize = ip_size - IP_header_length - tcp_hdr->doff * 4;

		return 0;
	}else if (ip_hdr->ip_p == IPPROTO_UDP){
		buf += IP_header_length;
		caplen -= IP_header_length;

		if (caplen < sizeof(udphdr))
			return 5;

		udphdr *udp_hdr = (udphdr*) buf;

		sport = ntohs(udp_hdr->source);
		dport = ntohs(udp_hdr->dest);
		dsize = ntohs(udp_hdr->len) - 8;

		return 0;
	}else 
		return 4;
}

int Packet::parse(const unsigned char *buf, pcap_pkthdr &hdr){
	return parse_base(buf, hdr, 1);
}

int Packet::parse_no_l2(const unsigned char *buf, pcap_pkthdr &hdr){
	return parse_base(buf, hdr, 0);
}

void Packet::serialize(Serializer &ser) const {
	ser.serialize(srcip.s_addr);
	ser.serialize(dstip.s_addr);
	ser.serialize(sport);
	ser.serialize(dport);
	ser.serialize(prot);
	ser.serialize(ipid);
	ser.serialize(seq);
	ser.serialize(ack);
	ser.serialize(size);
}

void Packet::deserialize(Deserializer &des){
	des.deserialize(srcip.s_addr);
	des.deserialize(dstip.s_addr);
	des.deserialize(sport);
	des.deserialize(dport);
	des.deserialize(prot);
	des.deserialize(ipid);
	des.deserialize(seq);
	des.deserialize(ack);
	des.deserialize(size);
}

string Packet::to_str() const{
	char buf[200];
	sprintf(buf, "%u,%u,%u,%u,%u,%u,%u,%u", srcip.s_addr, dstip.s_addr, sport, dport, prot, ipid, seq, ack);
	return buf;
}

string Packet::to_readable() const{
	char buf[200];
	int len = 0;
	len += sprintf(buf + len, "%s", inet_ntoa(srcip));
	len += sprintf(buf + len, " %s", inet_ntoa(dstip));
	sprintf(buf + len, " %d %d %d %d %d %u %u", sport, dport, prot, ipid, size, seq, ack);
	return buf;
}
string Packet::get_flow_id() const{
	char buf[60];
	int len = 0;
	len += sprintf(buf + len, "%s", inet_ntoa(srcip));
	len += sprintf(buf + len, " %s", inet_ntoa(dstip));
	sprintf(buf + len, " %d %d %d", sport, dport, prot);
	return buf;
}

string Packet::str_srcip() const{
	return inet_ntoa(srcip);
}

} /* namespace bright_lib */
