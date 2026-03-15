#include <charconv>
#include <algorithm>
#include <functional>
#include <iostream>

#include "ip_filter.h"

std::vector<std::string> split(const std::string& str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

IpAddress::IpAddress(const std::vector<std::string>& str_ip)
{
    if (str_ip.size() != 4) {
        valid = false;
        return;
    }
    ParseOctet(str_ip[0], o1);
    ParseOctet(str_ip[1], o2);
    ParseOctet(str_ip[2], o3);
    ParseOctet(str_ip[3], o4);
}

IpAddress::IpAddress(uint8_t i1, uint8_t i2, uint8_t i3, uint8_t i4)
    : o1(i1)
    , o2(i2)
    , o3(i3)
    , o4(i4)
    , valid(true)
{}

void IpAddress::ParseOctet(const std::string& str, uint8_t& octet)
{
    if (!valid)
        return;
    auto [ptr4, ec4] = std::from_chars(str.data(), str.data() + str.size(), octet);
    if (ec4 != std::errc())
    {
        valid = false;
        return;
    }
}


bool operator<(const IpAddress& ip1, const IpAddress& ip2)
{
    uint32_t i1 = (static_cast<uint32_t>(ip1.o1) << 24) + (static_cast<uint32_t>(ip1.o2) << 16) + (static_cast<uint32_t>(ip1.o3) << 8) + static_cast<uint32_t>(ip1.o4);
    uint32_t i2 = (static_cast<uint32_t>(ip2.o1) << 24) + (static_cast<uint32_t>(ip2.o2) << 16) + (static_cast<uint32_t>(ip2.o3) << 8) + static_cast<uint32_t>(ip2.o4);

    return i1 < i2;
}

std::ostream& operator<<(std::ostream& os, const  IpAddress& ip) {
    os << +ip.o1 << "." << +ip.o2 << "." << +ip.o3 << "." << +ip.o4;
    return os;
}


BoolFunc AndFunc = [](bool b1, bool b2) { return b1 && b2; };
BoolFunc OrFunc = [](bool b1, bool b2) { return b1 || b2; };

void PrintIpPool(const IpPool& p, bool reverse)
{
    if (reverse) {
        auto bIt = p.rbegin();
        auto eIt = p.rend();
        for (; bIt != eIt; ++bIt)
            std::cout << *bIt << std::endl;
    }
    else {
        auto bIt = p.begin();
        auto eIt = p.end();
        for (; bIt != eIt; ++bIt)
            std::cout << *bIt << std::endl;
    }
}
