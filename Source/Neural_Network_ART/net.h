#pragma once

#include <vector>
#include <string>
#include "neuron.h"

const double trainingRate = 0.15;
const double alpha = 0.5;

class Net
{
private:
	std::vector<Layer> layers;
	double error;
	std::string name;
	double distance;
public:
	Net(const std::vector<unsigned int>& topology, std::string& name);
	static std::vector<std::string> networksNames;
	void forwardPropagation(const std::vector<double>& inputVals);
	void backPropagation(const std::vector<double>& targetVals);
	std::vector<double> getResults() const;
	double getError() const;
	std::vector<Layer> getLayers() const;
	std::string getName() const;
	void setName(std::string& newName);
	double getDistance() const;
	void setDistance(double distance);
	Net operator=(const Net& other);
};