#include "scan.hpp"
#include "net_help.h"

#include <iostream>

//#####################################################################################################################
NetworkScanner::NetworkScanner(std::string localAddress)
    : localAddress_(std::move(localAddress))
{

}
//---------------------------------------------------------------------------------------------------------------------
std::vector <std::future <std::string>> NetworkScanner::icmpEchoScan() const
{
    std::vector <std::future <std::string>> result;

    std::string base = getAddressBase();
    for (std::size_t i = 1; i != 255; ++i)
    {
        std::string addr = base + std::to_string(i);
        result.emplace_back(
            std::async(std::launch::async, [this, addr, i]() -> std::string
            {
                auto echoResult = ICMPEcho(addr.c_str());
                if (!echoResult)
                    return {};

                auto actual = echoResult.get();

                if (actual.answerReceived && actual.status == 0)
                    return addr;
                else
                    return {};
            })
        );
    }

    return result;
}
//---------------------------------------------------------------------------------------------------------------------
std::string NetworkScanner::getAddressBase() const
{
    return localAddress_.substr(0, localAddress_.find_last_of('.') + 1);
}
//---------------------------------------------------------------------------------------------------------------------
std::vector <std::string> NetworkScanner::getLocalAddresses()
{
    return ::getLocalAddresses();
}
//---------------------------------------------------------------------------------------------------------------------
std::string NetworkScanner::getHostName(std::string const& ip)
{
    return ::getHostName(ip.c_str());
}
//#####################################################################################################################
