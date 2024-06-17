#pragma once
#include <string>
#include <vector>

class Normalizer
{
public:
	static std::vector<double> normalize(std::string& str); 
	static std::vector<double> findOneChar(std::vector<double>& normalized, char symbol, int outputLayerSize);
};