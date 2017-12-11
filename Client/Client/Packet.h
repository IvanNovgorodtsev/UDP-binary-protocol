#pragma once
#include<bitset>
#include<string>
#include<iostream>
using namespace std;

class Packet
{
public:
	Packet();
	Packet(int type, long long num, int state, int id, bool isEnd);

	const int packet_size = 10;
	char packet[10];
private:
	int type; //typ dzia≥ania arytmetyczno-logicznego, 2 bity
	long long num; //przesy≥ana liczba
	int state; //pole statusu, 4 bity
	int id; //identyfikator sesji, 4 bity
	bool isEnd; //informacja czy to ostatni pakiet sesji 

				//MOØLIWE STATUSY PAKIETU:
				//0 - zapytanie o ID
				//1 - odpowiedü servera z wybranym ID
				//2 - wys≥anie øadania dzia≥ania arytmetycznego
				//3 - odpowiedü na øπdanie arytmetyczne
				//4 - b≥πd, odpowiedü arytmetyczna wysz≥a poza zakres
public:
	//std::string packetToString();
	//void stringToPacket(std::string packet);
	void print();
	void setType(int newType);
	int getType();
	void setNumber(long long num);
	long long getNumber();
	void setID(int ID);
	int getID();

	void packing();
	void unpacking();
	long long bit_to_int(const string &packet);
	int Packet::getState();
	void Packet::setState(int newState);
	bool Packet::getIsEnd();
	void Packet::setIsEnd(bool is);
};

