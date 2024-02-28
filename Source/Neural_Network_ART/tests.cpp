#include "tests.h"

std::string generateString()
{
	std::string generated;
	for (size_t i = 0; i < 101; i++)
	{
		char symbol = rand() % alphabeticalSymbols.length();
		generated[i] = symbol;
	}
	return generated;
}