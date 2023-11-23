#pragma once

#include <vector>
#include <string>
#include "neuron.h"

class Net
{
private:
	std::vector<Layer> layers;
	double error;
	double previousAverageError;
	const double smooth = 100.0;
	std::string name;
public:
	Net(const std::vector<unsigned int>& topology);
	Net(const Net& original);
	void forwardPropagation(const std::vector<double>& inputVals);
	void backPropagation(const std::vector<double>& targetVals);
	void getResults(std::vector<double>& resultVals) const;
	double getRecentAverageError(){ return previousAverageError; }
	double getError(){ return error; }
	std::vector<Layer> getLayers() { return layers; }
	void setName(std::string value) { name = value; }
	Net& operator=(const Net& other);
};