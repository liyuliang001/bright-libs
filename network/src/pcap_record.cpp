#include "pcap_record.hpp"
using namespace std;

namespace bright_lib{

double PcapRecord::get_ts_double() const{
    return ts.tv_sec + ts.tv_usec / 1e6;
}

int PcapRecord::parse(const unsigned char *buf, pcap_pkthdr &hdr)
{
    ts = hdr.ts;
	int err = packet.parse(buf, hdr);
	return err;
}

int PcapRecord::parse_no_l2(const unsigned char *buf, pcap_pkthdr &hdr){
    ts = hdr.ts;
	int err = packet.parse_no_l2(buf, hdr);
	return err;
}

string PcapRecord::to_str() const{
	char buf[128];
	sprintf(buf, "%s,%lu.%06lu", packet.to_str().c_str(), ts.tv_sec, ts.tv_usec);
	return buf;
}

string PcapRecord::to_readable() const {
	char buf[128];
	sprintf(buf, "%lu.%06lu %s", ts.tv_sec, ts.tv_usec, packet.to_str().c_str());
	return buf;
}

} /* namespace bright_lib */
