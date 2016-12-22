/*
 * Packet parser that get timestamp, srcip, dstip, srcport, dstport, protocol, and ipid
 */

#include <arpa/inet.h>
#include "packet.hpp"
using namespace std;

namespace bright_lib{
int Packet::parse(const unsigned char *buf, pcap_pkthdr &hdr)
{
    int caplen = hdr.caplen;
    ip *ip_hdr;
    tcphdr *tcp_hdr;
    unsigned int IP_header_length;

    /* For simplicity, we assume Ethernet encapsulation. */
    if (caplen < sizeof(ether_header))
        return 1;

    /* Skip over the Ethernet header. */
    buf += sizeof(ether_header);
    caplen -= sizeof(ether_header);

    /* Didn't capture a full IP header */
    if (caplen < sizeof(ip))
        return 2;
    

    ip_hdr = (ip*) buf;
    IP_header_length = ip_hdr->ip_hl * 4;   /* ip_hl is in 4-byte words */

    /* didn't capture the full IP header including options */
    if (caplen < IP_header_length)
        return 3;

    if (ip_hdr->ip_p != IPPROTO_TCP)
        return 4;

    /* Skip over the IP header to get to the UDP header. */
    buf += IP_header_length;
    caplen -= IP_header_length;

    if (caplen < sizeof(tcphdr))
        return 5;

    tcp_hdr = (tcphdr*) buf;

	printf("parse srcip\n");
    srcip = ip_hdr->ip_src;
	printf("parse dstip\n");
    dstip = ip_hdr->ip_dst;
	printf("parse sport\n");
    sport = ntohs(tcp_hdr->source);
	printf("parse dport\n");
    dport = ntohs(tcp_hdr->dest);
	printf("parse prot\n");
    prot = ip_hdr->ip_p;
	printf("parse ipid\n");
    ipid = ntohs(ip_hdr->ip_id);
	printf("parse seq\n");
	seq = ntohl(tcp_hdr->seq);
	printf("parse ack\n");
	ack = ntohl(tcp_hdr->ack_seq);
	printf("parse size\n");
    size = hdr.len;

    return 0;
}

void Packet::serialize(Serializer &ser) const {
    ser.serialize(srcip.s_addr);
    ser.serialize(dstip.s_addr);
    ser.serialize(sport);
    ser.serialize(dport);
    ser.serialize(prot);
    ser.serialize(ipid);
    ser.serialize(size);
}

void Packet::deserialize(Deserializer &des){
    des.deserialize(srcip.s_addr);
    des.deserialize(dstip.s_addr);
    des.deserialize(sport);
    des.deserialize(dport);
    des.deserialize(prot);
    des.deserialize(ipid);
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
