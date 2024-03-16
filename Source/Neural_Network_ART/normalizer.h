#pragma once
#include <string>
#include <vector>

class StringNormalizer
{
public:
	static std::vector<double> normalize(std::string& str);
	static std::vector<double> findTarget(std::vector<double>& normalized, char symbol, int outputLayerSize);
	static std::string convertToString(std::vector<double>& doubles);
};

