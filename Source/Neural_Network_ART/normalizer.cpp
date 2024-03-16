#include "normalizer.h"
#include <iostream>
#include <algorithm>

std::vector<double> StringNormalizer::normalize(std::string& str)
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

std::vector<double> StringNormalizer::findTarget(std::vector<double>& normalized, char symbol, int outputLayerSize)
{
	std::vector<double> output(outputLayerSize, 0.0);
	std::vector<double>::iterator it = std::find(normalized.begin(), normalized.end(), 1.0 / symbol);
	std::_Iter_diff_t<std::vector<double>::iterator> position = std::distance(normalized.begin(), it);

	if (it != normalized.end()) {
		std::cout << "Value '" << symbol << "' was found in vector at position: " << position << std::endl;
	}
	else {
		std::cout << "Value '" << symbol << "' was not found in vector." << std::endl;
	}

	output.at(position) = 1.0 / symbol;

	return output;
}

std::string StringNormalizer::convertToString(std::vector<double>& doubles)
{
	std::string converted = "";
	for (size_t i = 0; i < doubles.size(); i++)
	{
		int intValue = (1 / doubles.at(i));
		char charValue = intValue;
		converted += charValue;
	}
	return converted;
}
