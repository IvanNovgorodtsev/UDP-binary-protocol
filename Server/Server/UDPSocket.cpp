#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "UDPSocket.h"
#include <system_error>
#include <WS2tcpip.h>
#include <conio.h>
#include "Packet.h"
UDPSocket::UDPSocket()
{
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == INVALID_SOCKET)
		throw std::system_error(WSAGetLastError(), std::system_category(), "Error opening socket");
}

UDPSocket::~UDPSocket()
{
	closesocket(sock);
}

void UDPSocket::SendTo(const std::string & address, unsigned short port, Packet &pak, int flags)
{
	int len = pak.packet_size;
	char buffer[10];
	for (int i = 0; i < len; i++)
	{
		buffer[i] = pak.packet[i];
	}
	sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_addr.s_addr = inet_addr(address.c_str());
	//InetPton(AF_INET, address.c_str(), &add.sin_addr.s_addr);
	add.sin_port = htons(port);
	int ret = sendto(sock, buffer, len, flags, reinterpret_cast<SOCKADDR *>(&add), sizeof(add));
	if (ret < 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
}

void UDPSocket::SendTo(sockaddr_in & address, Packet &pak , int flags)
{
	int len = pak.packet_size;
	char buffer[10];
	for (int i = 0; i < len; i++)
	{
		buffer[i] = pak.packet[i];
	}
	int ret = sendto(sock, buffer, len, flags, reinterpret_cast<SOCKADDR *>(&address), sizeof(address));
	if (ret < 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "sendto failed");
}

sockaddr_in UDPSocket::RecvFrom(Packet &pak, int flags)
{
	char buffer[10];
	int len = pak.packet_size;
	sockaddr_in from;
	int size = sizeof(from);
	int ret = recvfrom(sock, buffer, len, flags, reinterpret_cast<SOCKADDR *>(&from), &size);
	if (ret < 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "recvfrom failed");

	for (int i = 0; i < len; i++)
	{
		pak.packet[i] = buffer[i];
	}
	// make the buffer zero terminated
	return from;
}

void UDPSocket::Bind(unsigned short port)
{
	sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_addr.s_addr = htonl(INADDR_ANY);
	add.sin_port = htons(port);

	int ret = bind(sock, reinterpret_cast<SOCKADDR *>(&add), sizeof(add));
	if (ret < 0)
		throw std::system_error(WSAGetLastError(), std::system_category(), "Bind failed");
}
