#include "neuron.h"
#include <cmath>
#include <iostream>

Neuron::Neuron()
{
	output = 0.0;
	gradient = 0.0;
	index = 0;
}

Neuron::Neuron(unsigned int numOutputs, unsigned int myIndex)
{
	for (unsigned int i = 0; i < numOutputs; ++i) {
		outputWeights.push_back(Synapse());
		outputWeights.back().weight = randomWeight();
	}
	index = myIndex;
}

void Neuron::setOutput(double val) 
{
	output = val;
}

double Neuron::getOutput(void) const 
{
	return output; 
}

std::vector<Synapse> Neuron::getOutputWeights() 
{ 
	return outputWeights; 
}

double Neuron::randomWeight() 
{
	return rand() / double(RAND_MAX);
}

void Neuron::updateInputWeights(Layer& prevLayer) const
{
	for (size_t i = 0; i < prevLayer.size(); ++i)
	{
		Neuron& neuron = prevLayer.at(i);
		double oldDeltaWeight = neuron.outputWeights.at(index).deltaWeight;
		double newDeltaWeight = trainingRate * neuron.getOutput() * gradient + alpha * oldDeltaWeight;
		neuron.outputWeights.at(index).deltaWeight = newDeltaWeight;
		neuron.outputWeights.at(index).weight += newDeltaWeight;
	}
}
double Neuron::innerProductWeightsAndGradient(const Layer& nextLayer) const
{
	double innerProduct = 0.0;

	for (size_t i = 0; i < nextLayer.size() - 1; ++i)
	{
		innerProduct += outputWeights.at(i).weight * nextLayer.at(i).gradient;
	}

	return innerProduct;
}

void Neuron::calculateHiddenGradients(const Layer& nextLayer)
{
	double ipwag = innerProductWeightsAndGradient(nextLayer);
	gradient = ipwag * Neuron::sigmoidDerivative(output);
}

void Neuron::calculateOutputGradients(double targetValue)
{
	double delta = targetValue - output;
	gradient = delta * Neuron::sigmoidDerivative(output);
}

double Neuron::sigmoid(double input)
{
	return (1 / (1 + std::exp(-input)));
}

double Neuron::sigmoidDerivative(double sigmoid)
{
	return (sigmoid * (1 - sigmoid));
}

void Neuron::feedForward(const Layer& previousLayer)
{
	double innerProduct = 0.0;

	for (size_t i = 0; i < previousLayer.size(); ++i)
	{
		innerProduct += previousLayer.at(i).getOutput() * previousLayer.at(i).outputWeights.at(index).weight;
	}

	output = Neuron::sigmoid(innerProduct);
}

Neuron& Neuron::operator=(const Neuron& other) 
{
	output = other.output;
	outputWeights = other.outputWeights;
	return *this;
}