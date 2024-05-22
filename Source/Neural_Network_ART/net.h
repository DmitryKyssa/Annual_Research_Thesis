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
	const double smooth = 1000.0;
	std::string name;
	int fitness;
	double distance;
public:
	Net(const std::vector<unsigned int>& topology, std::string& name);
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
	double getDistance() const;
	void setDistance(double distance);
	Net operator=(const Net& other);
};