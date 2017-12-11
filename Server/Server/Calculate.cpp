#include <vector>
#include <algorithm>
#include <map>
#include "Packet.h"


long long calculate(Packet &packet, std::vector<long long> cont)
{
	long long temp;
	switch (packet.getType())
	{
	case 0:
		temp = 0;
		for (long long x : cont)
		{
			temp +=x;
		}
		return temp;
	case 1:
		temp = 1;
		for (long long x : cont)
		{
			temp *= x;
		}
		return temp;
	case 2:
		return  *std::max_element(std::begin(cont), std::end(cont));
	case 3:
		return  *std::min_element(std::begin(cont), std::end(cont));
	default:
		break;
	}

}