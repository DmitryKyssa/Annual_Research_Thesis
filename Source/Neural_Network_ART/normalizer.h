#pragma once
#include <string>
#include <vector>

class StringNormalizer
{
public:
	static std::vector<double> normalize(std::string& str); 
	static std::vector<double> findOneChar(std::vector<double>& normalized, char symbol, int outputLayerSize);
	static std::vector<double> findSubstring(std::string& str, std::string& substr, int outputLayerSize);
	static std::string convertToString(const std::vector<double>& doubles);
};

