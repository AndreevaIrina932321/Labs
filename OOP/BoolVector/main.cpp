#include <iostream>
#include "BoolVector.h"

int main()
{
	BoolVector bv(14, false), bv1(16, true);
	bv.print();
	bv = ~bv;
	bv.print();
	bv.invert(6);
	bv.invert(2);
	bv.print();
	bv &= bv1;
	std::cout << std::endl;
	bv.print();
	bv = bv >> 16;
	bv.print();
	return 0;
}
