#include <iostream>
#include <sstream>
#include <array>
#include <boost/format.hpp>
#include "TcpPdu.h"
#include "Pdu.h"

TcpPdu::TcpPdu(size_t hlen)
{
    Pdu::parse(sizeof(TcpHeader));
    m_options.reserve(hlen * 4 - sizeof(TcpHeader));
    TcpPdu::hlen(hlen);
}

TcpPdu::TcpPdu(const uint8_t* header)
{
    Pdu::parse(header, sizeof(TcpHeader));
    const auto hlen = TcpPdu::hlen();
    m_options.reserve(hlen * 4);
    std::copy_n(header + sizeof(TcpHeader), hlen * 4, m_options.begin());
}

TcpPdu::TcpPdu(const TcpHeader& header):
TcpPdu::TcpPdu{reinterpret_cast<const uint8_t*>(&header)}
{}

TcpPdu::TcpPdu(const TcpHeader* header):
TcpPdu::TcpPdu{reinterpret_cast<const uint8_t*>(header)}
{}

constexpr uint8_t TcpPdu::defaultSize() const
{
    return 20;
}

uint16_t TcpPdu::sport() const
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    return ntohs(header->sport);
}

uint16_t TcpPdu::dport() const
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    return ntohs(header->dport);
}

uint32_t TcpPdu::seqnum() const
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    return ntohl(header->seqnum);
}

uint32_t TcpPdu::acknum() const
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    return ntohl(header->acknum);
}

uint8_t TcpPdu::hlen() const
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    return TCP_PDU_HLEN(header);
}

uint16_t TcpPdu::flags() const
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    return TCP_PDU_FLAGS(header);
}

uint16_t TcpPdu::winsize() const
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    return ntohs(header->winsize);
}

uint16_t TcpPdu::chksum() const
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    return ntohs(header->chksum);
}

uint16_t TcpPdu::urgptr() const
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    return ntohs(header->urgptr);
}

std::array<uint8_t, 8> TcpPdu::options() const
{
    //auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    std::array<uint8_t, 8> options;
    std::copy_n(m_options.begin(), 8, options.begin());
    return options;
}

/*
void TcpPdu::print(std::stringstream& sstr) const
{
    sstr << TcpPdu::toString() << std::endl;
}
*/

void TcpPdu::sport(uint16_t sport)
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    header->sport = htons(sport);
}

void TcpPdu::dport(uint16_t dport)
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    header->dport = htons(dport);
}

void TcpPdu::seqnum(uint32_t seqnum)
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    header->seqnum = seqnum;
}

void TcpPdu::acknum(uint32_t acknum)
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    header->acknum = acknum;
}

void TcpPdu::hlen(uint8_t hlen)
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    header->hlen = hlen;
}

void TcpPdu::flags(uint16_t flags)
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    header->flags = flags;
}

void TcpPdu::winsize(uint16_t winsize)
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    header->winsize = winsize;
}

void TcpPdu::chksum(uint16_t chksum)
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    header->chksum = chksum;
}

void TcpPdu::urgptr(uint16_t urgptr)
{
    auto header = static_cast<TcpHeader* const>(TcpPdu::data());
    header->urgptr = urgptr;
}

std::string TcpPdu::toString() const
{
    std::stringstream sstr;
    sstr << boost::format("tcp sport %d\n") % TcpPdu::sport();
    sstr << boost::format("tcp dport %d\n") % TcpPdu::dport();
    sstr << boost::format("tcp seqnum %u\n") % TcpPdu::seqnum();
    sstr << boost::format("tcp acknum %u\n") % TcpPdu::acknum();
    sstr << boost::format("tcp hlen %u\n") % TcpPdu::hlen();
    sstr << boost::format("tcp flags %u\n") % TcpPdu::flags();
    sstr << boost::format("tcp winsize %u\n") % TcpPdu::winsize();
    sstr << boost::format("tcp chksum %X\n") % TcpPdu::chksum();
    sstr << boost::format("tcp urgptr %u\n") % TcpPdu::urgptr();
    //sstr << boost::format("tcp options %s\n") % TcpPdu::options();
    return sstr.str();
}
