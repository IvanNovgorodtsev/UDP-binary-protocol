#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <conio.h>
#include <map>
#include "Server.h"
#include "Packet.h"
#include "Calculate.h"

int ClientID = 1;

void anserwing(UDPSocket &Socket, std::vector<long long> &cont)
{
	Packet packet;
	sockaddr_in add = Socket.RecvFrom(packet);

	packet.unpacking();
	std::cout << "Packet recive: "<< std::endl;
	packet.print();


	switch (packet.getState())
	{
	case 0:

	{
		if (ClientID > 31)
		{
			ClientID = 1;
		}
		else
		{
			packet.setID(ClientID);
			packet.setState(1);
			packet.packing();
			Socket.SendTo(add, packet);
			ClientID++;
			cont.clear();
			std::cout << "Przyznano identyfikator sesji" << std::endl;
			break;
		}
	}

	case 2:
		std::cout << "Session[" << packet.getID() << "]: ";

		cont.push_back(packet.getNumber());

		long long result = calculate(packet, cont);
		std::cout << "wartosc sesji: " << result << std::endl;


		if (packet.getIsEnd())
		{
			if (result < 0 || result > 9223372036)
			{
				packet.setState(4);//jeœli wynik jest poza zakresem ustawia status poza zakrese
			}
			else
			{
				packet.setState(3);//jeœli siê zgadza to ustawia status odpowiedŸ na ¿¹danie arytmetycne
				packet.setNumber(result);//i jego wynik na miejscu pierwszej liczby

			}
			packet.packing();
			Socket.SendTo(add, packet);

		}

		break;
	}
	std::cout << std::endl;
}

#include <iostream>
#include "UDPSocket.h"
#include "Server.h"
#include <conio.h>
Server::Server()
{
	try
	{
		WSAData data;//contains information about the Windows Sockets implementation
		int ReturnCheck = WSAStartup(MAKEWORD(2, 2), &data);//initiates use of the Winsock DLL by a process
		if (ReturnCheck == SOCKET_ERROR)//Tell the user that we could not find a usable Winsock DLL.
			throw std::system_error(WSAGetLastError(), std::system_category(), "WSAStartup Failed");

		UDPSocket Socket;
		Socket.Bind(1111);
		std::vector<long long> cont;

		while (1)//g³ówna pêtla servera
		{
			anserwing(Socket, cont);
		}
	}
	catch (std::system_error& e)
	{
		std::cout << e.what();
	}
}
