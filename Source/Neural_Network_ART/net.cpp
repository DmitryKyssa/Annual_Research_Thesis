#include "net.h"
#include <cassert>
#include <iostream>

Net::Net(const std::vector<unsigned int>& topology, std::string& name)
{
	size_t numLayers = topology.size();
	for (size_t i = 0; i < numLayers; i++) {
		layers.push_back(Layer());
		size_t numOutputs = i == topology.size() - 1 ? 1 : topology.at(i + 1);
		//std::cout << "Number of outputs:" << numOutputs << std::endl;

		for (size_t neuronNum = 0; neuronNum <= topology.at(i); neuronNum++) {
			layers.back().push_back(Neuron((unsigned int)numOutputs, (unsigned int)neuronNum));
		}

		layers.back().back().setOutput(1.0);
	}

	error = 0.0;
	previousAverageError = 0.0;
	fitness = 0;
	this->name = name;
}

Net::Net(const Net& original)
{
	layers = original.layers;
	error = original.error;
	fitness = original.fitness;
	previousAverageError = original.previousAverageError;
	name = original.name;
	std::cout << "Copy constructor for net!" << std::endl;
}

Net& Net::operator=(const Net& other)
{
	layers = other.layers;
	error = other.error;
	previousAverageError = other.previousAverageError;
	try
	{
		name = networksNames.back();
		networksNames.pop_back();
		std::cout << "Overload for operator=" << std::endl;
	}
	catch (const std::exception&)
	{
		std::cout << "Vector of names is empty!" << std::endl;
	}
	return *this;
}

std::vector<double> Net::getResults() const
{
	std::vector<double> result;

	for (size_t i = 0; i < layers.back().size() - 1; ++i)
	{
		result.push_back(layers.back().at(i).getOutput());
	}

	return result;
}

double Net::getRecentAverageError() const
{
	return previousAverageError;
}

double Net::getError() const
{
	return error;
}

std::vector<Layer> Net::getLayers() const
{
	return layers;
}

std::string Net::getName() const
{
	return name;
}

int Net::getFitness() const
{
	return fitness;
}

void Net::setFitness(int fitness)
{
	this->fitness = fitness;
}

void Net::setName(std::string& newName)
{
	name = newName;
}

void Net::backPropagation(const std::vector<double>& targetValues)
{
	Layer& outputLayer = layers.back();
	error = 0.0;

	for (size_t i = 0; i < outputLayer.size() - 1; i++)
	{
		double delta = targetValues.at(i) - outputLayer.at(i).getOutput();
		error += delta * delta;
	}
	error /= outputLayer.size() - 1;
	error = sqrt(error);

	previousAverageError = (previousAverageError * smooth + error) / (smooth + 1.0);

	for (size_t i = 0; i < outputLayer.size() - 1; i++)
	{
		outputLayer.at(i).calculateOutputGradients(targetValues.at(i));
	}

	for (size_t i = layers.size() - 2; i > 0; --i)
	{
		Layer& hiddenLayer = layers.at(i);
		Layer& nextLayer = layers.at(i + 1);

		for (size_t j = 0; j < hiddenLayer.size(); j++)
		{
			hiddenLayer.at(j).calculateHiddenGradients(nextLayer);
		}
	}

	for (size_t i = layers.size() - 1; i > 0; --i)
	{
		Layer& layer = layers.at(i);
		Layer& prevLayer = layers.at(i - 1);

		for (size_t j = 0; j < layer.size() - 1; j++)
		{
			layer.at(j).updateInputWeights(prevLayer);
		}
	}
}

void Net::forwardPropagation(const std::vector<double>& inputs)
{
	assert(inputs.size() == layers[0].size() - 1);

	for (size_t i = 0; i < inputs.size(); i++) {
		layers.at(0).at(i).setOutput(inputs.at(i));
	}

	for (size_t i = 1; i < layers.size(); i++) {
		Layer& prevLayer = layers.at(i - 1);
		for (size_t j = 0; j < layers.at(i).size() - 1; j++) {
			layers.at(i).at(j).feedForward(prevLayer);
		}
	}
}