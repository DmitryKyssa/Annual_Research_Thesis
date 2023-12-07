#pragma once

#include <vector>
#include <fstream>
#include <sstream>

class Trainer
{
private:
	std::ifstream file;
public:
	Trainer(const std::string filename);
	void getTopology(std::vector<unsigned int>& topology);
	size_t getNextInputs(std::vector<double>& inputVals);
	size_t getTargetOutputs(std::vector<double>& targetOutputVals);
	bool getEOF();
};