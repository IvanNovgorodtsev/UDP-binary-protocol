#include "Packet.h"

Packet::Packet() {}
Packet::Packet(int type, long long num, int state, int id, bool isEnd)
{
	this->type = type;
	this->num = num;
	this->state = state;
	this->id = id;
	this->isEnd = isEnd;
}
void Packet::packing()
{
	std::string temp;
	temp = bitset<2>(type).to_string();
	temp += bitset<64>(num).to_string();
	temp += bitset<4>(state).to_string();
	temp += bitset<4>(id).to_string();
	temp += bitset<1>(isEnd).to_string();
	temp += bitset<5>(0).to_string();

	std::string tempByte;
	for (int i = 0, y = 0; i < 10; i++, y += 8)
	{
		tempByte = temp.substr(y, 8);
		packet[i] = bit_to_int(tempByte);
	}

}

void Packet::unpacking()
{
	std::string pom = "";
	std::bitset<8> bits;
	for (int i = 0; i < 10; i++)
	{
		bits = packet[i];
		pom += bits.to_string();
	}
	type = bit_to_int(pom.substr(0, 2));
	num = bit_to_int(pom.substr(2, 64));
	state = bit_to_int(pom.substr(66, 4));
	id = bit_to_int(pom.substr(70, 4));
	isEnd = bit_to_int(pom.substr(74, 1));
}

long long Packet::bit_to_int(const std::string &s)
{
	long long liczba = 0;
	for (int i = s.size() - 1, p = 1; i >= 0; i--, p *= 2)
	{
		if (s[i] == '1')
			liczba += p;
	}
	return liczba;
}
void Packet::print()
{
	std::cout << "Typ: " << type << " Liczba : " << num << " Stan: " << state << " ID: " << id << " ostatni: " << isEnd << std::endl;
}
void Packet::setType(int newType)
{
	this->type = newType - 1;
}

int Packet::getType()
{
	return this->type;
}
void Packet::setNumber(long long num)
{
	this->num = num;
}

long long Packet::getNumber()
{
	return this->num;
}

int Packet::getState()
{
	return this->state;
}
void Packet::setState(int newState)
{
	this->state = newState;
}

void Packet::setID(int ID)
{
	this->id = ID;
}

int Packet::getID()
{
	return this->id;
}

bool Packet::getIsEnd()
{
	return this->isEnd;
}

void Packet::setIsEnd(bool is)
{
	this->isEnd = is;
}