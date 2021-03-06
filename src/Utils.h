#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cstring>
#include <pcap.h>
#include <boost/format.hpp>
#include <stdint.h>

#include "Ip4Addr.h"
#include "MacAddr.h"

namespace Utils
{
    /*
    inline std::string toMacString(uint8_t mac[6])
    {
        return boost::str(boost::format("%02x:%02x:%02x:%02x:%02x:%02x") % int(mac[0]) % int(mac[1]) % int(mac[2]) % int(mac[3]) % int(mac[4]) % int(mac[5]));
    }
    inline std::string toIpString(uint8_t ip[4])
    {
        return boost::str(boost::format("%d.%d.%d.%d") % int(ip[0]) % int(ip[1]) % int(ip[2]) % int(ip[3]));
    }
    inline std::string toIpString(uint32_t ipInt)
    {
        auto ip = reinterpret_cast<uint8_t*>(&ipInt);
        return boost::str(boost::format("%d.%d.%d.%d") % int(ip[0]) % int(ip[1]) % int(ip[2]) % int(ip[3]));
    }
    inline long toIpLong(uint8_t ip[4])
    {
        return *reinterpret_cast<long*>(ip);
    }
    inline uint8_t* fromIpLong(long& ip)
    {
        return reinterpret_cast<uint8_t*>(&ip);
    }
    inline uint8_t* fromIpSockAddr(struct sockaddr& ip)
    {
        return reinterpret_cast<uint8_t*>(reinterpret_cast<struct sockaddr_in*>(&ip)->sin_addr.s_addr);
    }
    inline void fromIpString(const char* ipString, uint8_t* ip)
    {
        struct sockaddr_in addr; 
        inet_pton(AF_INET, ipString, &addr.sin_addr);
        memcpy(ip, &addr.sin_addr, 4);
    }
    inline std::string toFilterString(uint8_t mac[6], uint8_t ip[4])
    {
        return boost::str(boost::format("(arp[6:2] = 2) and src host %s and ether dst %s") % Utils::toIpString(ip) % Utils::toMacString(mac));
    }
    */

    MacAddr getMyMac(const std::string&);
    Ip4Addr getMyIp(const std::string&);
    //MacAddr queryMac(pcap_t* handle, const MacAddr&, const Ip4Addr&, const Ip4Addr&);
}

#endif
