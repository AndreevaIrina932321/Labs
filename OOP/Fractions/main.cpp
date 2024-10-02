#include <iostream>
#include "Fraction.h"


int main()
{
	Fraction first(35, 21), second(2,7), result;
	result = first+second;
	result.print();
	result = first-second;
	result.print();
	result = first*second;
	first.printProperForm();
	std::cout<<(first.getIntegerPart());
}
