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
	int fitness;
public:
	Net(const std::vector<unsigned int>& topology, std::string& name);
	//Net(const Net& original);
	static std::vector<std::string> networksNames;
	void forwardPropagation(const std::vector<double>& inputVals);
	void backPropagation(const std::vector<double>& targetVals);
	std::vector<double> getResults() const;
	double getRecentAverageError() const;
	double getError() const;
	std::vector<Layer> getLayers() const;
	std::string getName() const;
	int getFitness() const;
	void setName(std::string& newName);
	void setFitness(int fitness);
	Net operator=(const Net& other);
};