#pragma once

#include <vector>
#include <string>
#include "neuron.h"

static std::vector<std::string> networksNames = {
		"Emma", "Olivia", "Ava", "Isabella", "Sophia",
		"Mia", "Charlotte", "Amelia", "Harper", "Evelyn",
		"Abigail", "Emily", "Elizabeth", "Sofia", "Avery",
		"Ella", "Scarlett", "Grace", "Chloe", "Victoria"
};

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
	double getRecentAverageError() const;
	double getError() const;
	std::vector<Layer> getLayers();
	std::string getName();
	Net& operator=(const Net& other);
};