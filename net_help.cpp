#include "net_help.h"

#include <winsock2.h>
#include <iphlpapi.h>
#include <icmpapi.h>

boost::optional <EchoResult> ICMPEcho(const char* addr, int timeout)
{
	HANDLE hIcmpFile;
    unsigned long ipaddr = INADDR_NONE;
    DWORD dwRetVal = 0;
    char SendData[16] = "PINGPING";
    LPVOID ReplyBuffer = NULL;
    DWORD ReplySize = 0;

    // Validate the parameters
    ipaddr = inet_addr(addr);

    hIcmpFile = IcmpCreateFile();
    if (hIcmpFile == INVALID_HANDLE_VALUE)
        return boost::none;

    ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(SendData);
    ReplyBuffer = (VOID*) malloc(ReplySize);
    if (ReplyBuffer == NULL)
        return boost::none;

    dwRetVal = IcmpSendEcho(hIcmpFile, ipaddr, SendData, sizeof(SendData),
                            NULL, ReplyBuffer, ReplySize, timeout);

    EchoResult res = {
        dwRetVal != 0,
        ((icmp_echo_reply*)ReplyBuffer)[0].Status,
        ((icmp_echo_reply*)ReplyBuffer)[0].RoundTripTime
    };
    free(ReplyBuffer);
    return boost::optional <EchoResult> {res};
}

std::string getHostName(const char* addr)
{
	struct hostent *remoteHost;
	struct in_addr v4addr = { 0 };
	v4addr.s_addr = inet_addr(addr);
	remoteHost = gethostbyaddr((char *) &v4addr, 4, AF_INET);
	if (remoteHost == nullptr)
		return "";
	if (remoteHost->h_name == nullptr)
		return "";
	return std::string(remoteHost->h_name);
}

std::vector<std::string> getLocalAddresses()
{
	std::vector <std::string> addresses;

    char ac[80];
    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
		return {};
    }

    struct hostent *phe = gethostbyname(ac);
    if (phe == 0) {
		return {};
    }

    for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
        struct in_addr addr;
        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
        addresses.emplace_back(inet_ntoa(addr));
    }

    return addresses;
}
