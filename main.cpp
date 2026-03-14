#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>

#include "ip_filter.h"

int main()
{
    try
    {
        //std::vector<std::vector<std::string> > ip_pool;
        IpPool pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            IpAddress ip = split(v.at(0), '.');
            if (ip)
                pool.insert(ip);
        }

        // TODO reverse lexicographically sort
        PrintIpPool(pool, true);
        // TODO filter by first byte and output
        // ip = filter(1)
        auto filter1 = [](const IpAddress& ip) -> bool {
            if (ip.o1 == 1)
                return true;
            return false;
            };
        PrintWithFilter(pool, filter1);

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        auto filter2 = [](const IpAddress& ip) -> bool {
            if (ip.o1 == 46 && ip.o2 == 70)
                return true;
            return false;
            };
        PrintWithFilter(pool, filter2);
        
        // TODO filter by any byte and output
        // ip = filter_any(46)

        auto filter3 = [](const IpAddress& ip) -> bool {
            if (ip.o1 == 46 || ip.o2 == 46 || ip.o3 == 46 || ip.o4 == 46)
                return true;
            return false;
            };
        PrintWithFilter(pool, filter3);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
