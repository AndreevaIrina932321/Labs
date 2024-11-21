#include <iostream>
#include "BoolVector.h"

int main()
{
    bool a = true;
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
	bv = bv >> 7;
	bv.print();
	bv[2] = bv[6] ^ a;
	bv.print();
	return 0;
}
