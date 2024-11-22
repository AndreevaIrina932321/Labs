#include <iostream>
#include "BoolVector.h"

int main()
{
    bool a = true;
	BoolVector bv(14, false), bv1(16, true), result(1);
	bv.print();
	bv = ~bv;
	bv.print();
	bv.invert(6);
	bv.invert(2);
	bv.print();
	bv1.invert(1);
	bv1.print();
	result = bv ^ bv1;
	std::cout << std::endl;
	result.print();
	bv = bv >> 7;
	bv.print();
	bv[13] = bv[7] & bv[9];
	bv.print();
	return 0;
}
