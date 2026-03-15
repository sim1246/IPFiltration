#pragma once

#include <set>
#include <functional>
#include <vector>
#include <utility>
#include <string>

std::vector<std::string> split(const std::string& str, char d);

struct IpAddress {
    IpAddress(const std::vector<std::string>& str_ip);
    IpAddress(uint8_t i1, uint8_t i2, uint8_t i3, uint8_t i4);

    operator bool() const { return valid; }

    IpAddress() = delete;

    uint8_t o1 = 0;
    uint8_t o2 = 0;
    uint8_t o3 = 0;
    uint8_t o4 = 0;
private:

    void ParseOctet(const std::string& str, uint8_t& octet);
    bool valid = true;
};


bool operator<(const IpAddress& ip1, const IpAddress& ip2);

std::ostream& operator<<(std::ostream& os, const  IpAddress& ip);

using IpPool = std::multiset<IpAddress>;

using BoolFunc = std::function<bool(bool, bool)>;

extern BoolFunc AndFunc;
extern BoolFunc OrFunc;

template<typename... Args>
bool FilterFunc(const IpAddress& ip, BoolFunc funcB, Args ... octets)
{
    static_assert(sizeof...(octets) <= 4);
    std::vector<uint8_t> ipv = { ip.o1, ip.o2, ip.o3, ip.o4 };

    size_t count = sizeof...(octets);

    uint32_t octs[] = { static_cast<uint32_t>(octets)... };
    bool res = (octs[0] > 255) ? true : (ipv[0] == static_cast<uint8_t>(octs[0]));
    for (size_t idx = 1; idx < count; ++idx)
    {
        res = (octs[idx] > 255) ? funcB(res, true) : funcB(res, (ipv[idx] == static_cast<uint8_t>(octs[idx])));
    }
    return res;
}

template<typename... Args>
void PrintWithFilter(const IpPool& p, BoolFunc boolF, Args ... octets)
{
    auto it = p.rbegin();
    auto end = p.rend();
    for (; it != end; ++it) {
        if (FilterFunc(*it, boolF, std::forward<Args>(octets)...))
            std::cout << *it << std::endl;
    }
}

void PrintIpPool(const IpPool& p, bool reverse);