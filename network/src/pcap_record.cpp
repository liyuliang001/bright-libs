#include "pcap_record.hpp"
using namespace std;

namespace bright_lib{

double PcapRecord::get_ts_double() const{
    return ts.tv_sec + ts.tv_usec / 1e6;
}

int PcapRecord::parse(const unsigned char *buf, pcap_pkthdr &hdr)
{
    ts = hdr.ts;
	packet.parse(buf, hdr);
    return 0;
}

string PcapRecord::to_str() const{
	return packet.to_str() + "," + to_string(ts.tv_sec) + "." + to_string(ts.tv_usec);
}

string PcapRecord::to_readable() const {
	return to_string(ts.tv_sec) + "." + to_string(ts.tv_usec) + "," + packet.to_readable();
}

} /* namespace bright_lib */
