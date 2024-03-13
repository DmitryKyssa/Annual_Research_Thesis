#include "normalizer.h"
#include <iostream>

std::vector<double> StringNormalizer::normalize(std::string str)
{
	std::vector<double> normalized;
	for (size_t i = 0; i < str.length(); i++)
	{
		double value = 1.0 / str[i];
		normalized.push_back(value);
		//std::cout << str[i] << ": " << value << std::endl;
	}
	return normalized;
}