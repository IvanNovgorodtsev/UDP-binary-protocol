#include <iostream>
#include <algorithm>
#include <cctype>
#include <conio.h>
#include <vector>
#include <chrono>
#include <thread>
#include "UDPSocket.h"
#include "Client.h"
#include "Packet.h"

bool digitCheck(std::string a)//funkcja zwraca TRUE gdy podany string sk³ada siê tylko z liczb 0-9
{
	bool check = 1;
	for (char x : a)
	{
		if (!std::isdigit(x))
		{
			check = 0;
		}
	}
	return check;
}

void IDrequest(UDPSocket &Socket, Packet &packet)
{
	packet.setState(0);
	packet.packing();
	Socket.SendTo("127.0.0.1", 1111, packet);
}

void IDrecive(UDPSocket &Socket, Packet &packet)
{
	Socket.RecvFrom(packet);
	packet.unpacking();
	if (packet.getState() == 1)
	{
		packet.setState(2);
	}
}

void sending(UDPSocket &Socket, Packet &packet)
{
	packet.setIsEnd(0);
	string typed;
	long long number;
	int amount;
	std::vector<long long> numbers;
	//WYBOR TYPU
	std::cout << "Podawaj numer pozadanej operacji:\n1 DODAWANIE\n2 MNOZENIE\n3 NAJWIEKSZA\n4 NAJMNIEJSZA" << std::endl;
	getline(cin, typed);
	while (!digitCheck(typed))
	{
		std::cout << "Podana wartosc nie jest liczba, sprobuj ponownie\n";
		getline(cin, typed);
	}
	number = std::stoi(typed);
	while (number < 1 || number>4)
	{
		std::cout << "Podana wartosc wykracza poza zakres, sprobuj ponownie\n";
		getline(cin, typed);
		number = std::stoi(typed);
	}
	packet.setType(number);
	system("cls");

	//WYBOR ILOŒCI LICZB
	std::cout << "Podawaj ilosc liczb ktore chcesz wyslac" << std::endl;
	getline(cin, typed);
	while (!digitCheck(typed))
	{
		std::cout << "Podana wartosc nie jest liczba, sprobuj ponownie\n";
		getline(cin, typed);
	}
	amount = std::stoi(typed);

	//WYBOR LICZBY
	for (int i = 0; i < amount; i++)
	{
		std::cout << "Podaj wartosci kolejnych liczb: " << std::endl;
		getline(cin, typed);
		while (!digitCheck(typed))
		{
			std::cout << "Podana wartosc nie jest liczba, sprobuj ponownie\n";
			getline(cin, typed);
		}
		number = std::stoll(typed);
		while (number < 0 || number > 9223372036)
		{
			std::cout << "Podana wartosc wykracza poza zakres, sprobuj ponownie\n";
			getline(cin, typed);
			number = std::stoll(typed);
		}

		numbers.push_back(number);
	}
	for (int i = 0; i < numbers.size(); i++)
	{
		if (i + 1 == numbers.size())
		{
			packet.setIsEnd(1);
		}
		packet.setNumber(numbers[i]);
		packet.setState(2);
		packet.packing();
		Socket.SendTo("127.0.0.1", 1111, packet);

	}

	system("cls");
}

void recivingReply(UDPSocket &Socket, Packet &reply)
{
	string replyBuff;
	Socket.RecvFrom(reply);
	reply.unpacking();

	if (reply.getState() == 3)
	{
		std::cout << "Wynik operacji to " << reply.getNumber() << std::endl;
	}
	else if (reply.getState() == 4)
	{
		std::cout << "Blad, wyniku operacji arytmetycznej poza dopuszczalnym zakresem" << std::endl;
	}
	std::cout << "Wcisnij dowolny przycisk" << std::endl;
	_getch();
	system("cls");
}

Client::Client()
{

	try
	{
		WSAData data;//contains information about the Windows Sockets implementation
		int ReturnCheck = WSAStartup(MAKEWORD(2, 2), &data);//initiates use of the Winsock DLL by a process
		if (ReturnCheck == SOCKET_ERROR)//Tell the user that we could not find a usable Winsock DLL.
			throw std::system_error(WSAGetLastError(), std::system_category(), "WSAStartup Failed");

		UDPSocket Socket;
		
		while (1)//g³ówna pêtla klienta
		{
			Packet packet(0,0,0,0,0);

			IDrequest(Socket,packet);
			IDrecive(Socket,packet);

			sending(Socket,packet);
			recivingReply(Socket,packet);
		}
	}
	catch (std::exception &ex)
	{
		std::cout << ex.what();
	}
}
	