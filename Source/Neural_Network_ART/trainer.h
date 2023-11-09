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
	unsigned int getNextInputs(std::vector<double>& inputVals);
	unsigned int getTargetOutputs(std::vector<double>& targetOutputVals);
	bool getEOF();
};