#pragma once

#include <string>
#include <thread>
#include <future>
#include <vector>
#include <algorithm>

class NetworkScanner
{
public:
    NetworkScanner(std::string localAddress);
    std::vector <std::future <std::string>> icmpEchoScan() const;

    static std::vector <std::string> getLocalAddresses();
    static std::string getHostName(std::string const& ip);

private:
    std::string getAddressBase() const;

private:
    std::string localAddress_;
};
