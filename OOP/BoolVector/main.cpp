#include <iostream>
#include "BoolVector.h"

int main()
{
	BoolVector bv(14, true);
	for (int i = 0; i < 14; ++i)
	{
		std::cout << bv.bitValue(i);
	}
	std::cout << std::endl;
	bv.setBitValue(1, false);
	bv.setBitValue(6, false);
	for (int i = 0; i < 14; ++i)
	{
		std::cout << bv.bitValue(i);
	}
	return 0;
}
