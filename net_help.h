#pragma once

#include <boost/optional.hpp>
#include <string>
#include <vector>

struct EchoResult
{
    bool answerReceived;
    unsigned long status;
    unsigned long rtt;
};

boost::optional <EchoResult> ICMPEcho(const char* addr, int timeout = 5000);
std::string getHostName(const char* addr);
std::vector<std::string> getLocalAddresses();
