#pragma once

#include <algorithm>
#include <functional>
#include <stdint.h>
#include <charconv>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
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

struct IpAddress {
    IpAddress(const std::vector<std::string>& str_ip)
    {
        if (str_ip.size() != 4)
            return;
        auto [ptr1, ec1] = std::from_chars(str_ip[0].data(), str_ip[0].data() + str_ip[0].size(), o1);
        if (ec1 != std::errc())
            return;
        auto [ptr2, ec2] = std::from_chars(str_ip[1].data(), str_ip[1].data() + str_ip[1].size(), o2);
        if (ec2 != std::errc())
            return;
        auto [ptr3, ec3] = std::from_chars(str_ip[2].data(), str_ip[2].data() + str_ip[2].size(), o3);
        if (ec3 != std::errc())
            return;
        auto [ptr4, ec4] = std::from_chars(str_ip[3].data(), str_ip[3].data() + str_ip[3].size(), o4);
        if (ec4 != std::errc())
            return;
    }

    IpAddress(uint8_t i1, uint8_t i2, uint8_t i3, uint8_t i4)
        : o1(i1)
        , o2(i2)
        , o3(i3)
        , o4(i4)
    {}

    IpAddress() = delete;

    uint8_t o1 = 0;
    uint8_t o2 = 0;
    uint8_t o3 = 0;
    uint8_t o4 = 0;
};


bool operator<(const IpAddress& ip1, const IpAddress& ip2)
{
    if (ip1.o1 < ip2.o1)
        return true;
    if (ip1.o1 == ip2.o1) {
        if (ip1.o2 < ip2.o2)
            return true;
        if (ip1.o2 == ip2.o2) {
            if (ip1.o3 < ip2.o3)
                return true;
            if (ip1.o3 == ip2.o3) {
                if (ip1.o4 < ip2.o4)
                    return true;
            }
        }
    }
    return false;
}
std::ostream& operator<<(std::ostream& os, const  IpAddress& ip) {
    os << ip.o1 << "." << ip.o2 << "." << ip.o3 << "." << ip.o4;
    return os;
}

using IpPool = std::set<IpAddress>;
using FilterFunc = std::function<bool(const IpAddress&)>;

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

void PrintWithFilter(const IpPool& p, FilterFunc func)
{
    auto it = p.rbegin();
    auto end = p.rend();
    for (; it != end; ++it) {
        if (func(*it))
            std::cout << *it << std::endl;
    }
}

