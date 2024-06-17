#include "neuron.h"
#include <cmath>
#include <iostream>
#include <random>

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

std::vector<double> Neuron::getOutputWeights() 
{ 
	std::vector<double> weights; 
	for (Synapse s : outputWeights) 
	{
		weights.push_back(s.weight);
	}
	return weights; 
}

double Neuron::randomWeight() 
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0.01, 0.99);

	double randomDouble = dis(gen);
	return randomDouble;
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
	//std::cout << "Inner: " << innerProduct << std::endl;
	output = Neuron::sigmoid(innerProduct);
	//std::cout << "Output: " << output << std::endl;
}

Neuron& Neuron::operator=(const Neuron& other) 
{
	output = other.output;
	outputWeights = other.outputWeights;
	return *this;
}