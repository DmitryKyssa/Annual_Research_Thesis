#include "normalizer.h"
#include <iostream>
#include <algorithm>

std::vector<double> StringNormalizer::normalize(std::string str)
{
	std::vector<double> normalized;
	for (size_t i = 0; i < str.length(); i++)
	{
		double value = 1.0 / str[i];
		normalized.push_back(value);
		std::cout << str[i] << ": " << value << std::endl;
	}
	return normalized;
}

std::vector<double> StringNormalizer::findTarget(std::vector<double> normalized, char symbol)
{
	std::vector<double> output(62, 0.0);
	auto it = std::find(normalized.begin(), normalized.end(), 1.0 / symbol);
	auto position = std::distance(normalized.begin(), it);

	if (it != normalized.end()) {
		std::cout << "Value " << symbol << " found in vector at position: " << position << std::endl;
	}
	else {
		std::cout << "Value " << symbol << " not found in vector." << std::endl;
	}

	output.at(position) = 1.0 / symbol;

	return output;
}
