#include "normalizer.h"
#include <iostream>
#include <algorithm>
#include <cstring>

std::vector<double> Normalizer::normalize(std::string& str)
{
	std::vector<double> normalized;
	for (size_t i = 0; i < str.length(); i++)
	{
		normalized.push_back(1.0 / str[i]);
	}
	return normalized;
}

std::vector<double> Normalizer::findOneChar(std::vector<double>& normalized, char symbol, int outputLayerSize)
{
	std::vector<double> output(outputLayerSize, 0.0);
	std::vector<double>::iterator it = std::find(normalized.begin(), normalized.end(), 1.0 / symbol);
	std::_Iter_diff_t<std::vector<double>::iterator> position = std::distance(normalized.begin(), it);

	if (it != normalized.end()) {
		std::cout << "Value '" << symbol << "' was found in vector at position: " << position << std::endl;
		output.at(0) = 1.0;
		output.at(1) = position;
	}
	else {
		std::cout << "Value '" << symbol << "' was not found in vector." << std::endl;
	}

	return output;
}