#pragma once

#include <vector>

struct Synapse
{
	double weight;
	double deltaWeight;
};

class Neuron;

typedef std::vector<Neuron> Layer;

class Neuron
{
private:
	const double trainingRate = 0.15; 
	const double alpha = 0.5; 
	static double sigmoid(double input);
	static double sigmoidDerivative(double sigmoid);
	static double randomWeight();
	double innerProductWeightsAndGradient(const Layer& nextLayer) const;
	double output;
	std::vector<Synapse> outputWeights;
	unsigned int index;
	double gradient;
public:
	Neuron(unsigned int numOutputs, unsigned int myIndex);
	void setOutput(double val) { output = val; }
	double getOutput(void) const { return output; }
	void feedForward(const Layer& prevLayer);
	void calculateOutputGradients(double targetVals);
	void calculateHiddenGradients(const Layer& nextLayer);
	void updateInputWeights(Layer& prevLayer);
};