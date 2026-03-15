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
        PrintWithFilter(pool, AndFunc, 1);

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        PrintWithFilter(pool, AndFunc, 46, 70);
        
        // TODO filter by any byte and output
        // ip = filter_any(46)

        PrintWithFilter(pool, OrFunc, 46, 46, 46, 46);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
