#pragma once
#pragma comment (lib, "Ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include "Packet.h"

//#include <system_error>
class UDPSocket
{
public:
	UDPSocket();
	~UDPSocket();
	void SendTo(const std::string & address, unsigned short port, Packet &pak, int flags=0);
	void SendTo(sockaddr_in & address, Packet &pak, int flags = 0);
	sockaddr_in RecvFrom(Packet &pak, int flags = 0);
	void Bind(unsigned short port);

private:
	SOCKET sock;
	std::string _packet;
};