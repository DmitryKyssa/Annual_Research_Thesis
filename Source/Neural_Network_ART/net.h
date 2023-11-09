#pragma once

#include <vector>
#include "neuron.h"

class Net
{
public:
	Net(const std::vector<unsigned int>& topology);
	void forwardPropagation(const std::vector<double>& inputVals);
	void backPropagation(const std::vector<double>& targetVals);
	void getResults(std::vector<double>& resultVals) const;
	double getRecentAverageError(void) const { return previousAverageError; }
private:
	std::vector<Layer> layers;
	double error;
	double previousAverageError;
	const double smooth = 100.0;
};