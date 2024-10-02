#include <iostream>
#include "Fraction.h"


int main()
{
	Fraction first(10, 5), second(2,7), result;
	first.reduce();
	first.print();
	result = first+second;
	first.print();
	result.print();
	result = first-second;
	result.print();
	result = first*second;
	first.printProperForm();
	std::cout<<(first.getIntegerPart());
}
