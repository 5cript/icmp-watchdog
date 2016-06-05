#include "scan.hpp"
#include "user_io.hpp"
#include "net_help.h"

#include <winsock2.h>
#include <iostream>
#include <string>
#include <set>
#include <chrono>
#include <algorithm>
#include <iterator>
#include <thread>

#pragma comment(lib, "ws2_32")
#pragma comment(lib, "iphlpapi")

using namespace std::literals;

int main()
{
    //std::cout << ICMPEcho("192.168.178.32", 2500);

	WSAData wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return 255;
    }

    std::string selectedAddress;
	auto addresses = NetworkScanner::getLocalAddresses();
    auto selectedAddr = selectInterface(addresses);
    if (!selectedAddr)
        return 0;
    else
        selectedAddress = addresses[selectedAddr.get()];

    if (selectedAddress.find('.') == std::string::npos) // what the f...?
        return 1;

    //system("clear");
    std::cin.get();

    NetworkScanner scanner(selectedAddress);
    auto futures = scanner.icmpEchoScan();

    std::set <std::string> hosts;

    std::cout << "Currently online:\n";
    for (auto& fut : futures)
    {
        auto addr = fut.get();
        if (!addr.empty())
        {
            std::cout << addr << "\n";
            hosts.insert(addr);
        }
    }
    std::cout << "\nWaiting for differences...\n";

    std::atomic_bool running {true};
    std::thread perpetualScanner {
        [&]()
        {
            while(running.load())
            {
                std::set <std::string> newHosts;
                auto scanResults = scanner.icmpEchoScan();

                for (auto& scan : scanResults)
                {
                    auto addr = scan.get();
                    if (!addr.empty())
                    {
                        //std::cout << addr << "\n";
                        newHosts.insert(addr);
                    }
                }

                std::set <std::string> difference;
                std::set_difference(
                    std::begin(hosts), std::end(hosts),
                    std::begin(newHosts), std::end(newHosts),
                    std::inserter(difference, std::begin(difference))
                );
                std::set_difference(
                    std::begin(newHosts), std::end(newHosts),
                    std::begin(hosts), std::end(hosts),
                    std::inserter(difference, std::begin(difference))
                );

                std::set <std::string> fresh, old;
                for (auto const& diff : difference)
                {
                    if (hosts.find(diff) == std::end(hosts))
                        fresh.insert(diff);
                    else
                        old.insert(diff);
                }

                hosts = newHosts;

                for (auto const& i : fresh)
                    std::cout << "+++ " << i << " " << NetworkScanner::getHostName(i) << "\n";
                for (auto const& i : old)
                    std::cout << "--- " << i << " " << NetworkScanner::getHostName(i) << "\n";

                std::this_thread::sleep_for(5s);
            }
        }
    };

    std::cin.get();
    running.store(false);
    if (perpetualScanner.joinable())
        perpetualScanner.join();
	WSACleanup();
}
