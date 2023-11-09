#include "net.h"
#include <cassert>
#include <iostream>

Net::Net(const std::vector<unsigned int>& topology)
{
	size_t numLayers = topology.size();
	for (size_t i = 0; i < numLayers; i++) {
		layers.push_back(Layer());
		size_t numOutputs = i == topology.size() - 1 ? 0 : topology.at(i + 1);

		for (unsigned neuronNum = 0; neuronNum <= topology.at(i); neuronNum++) {
			layers.back().push_back(Neuron(numOutputs, neuronNum));
		}

		layers.back().back().setOutput(1.0);
	}

	error = 0.0;
	previousAverageError = 0.0;
}

void Net::getResults(std::vector<double>& result) const
{
	result.clear();

	for (size_t i = 0; i < layers.back().size() - 1; ++i)
	{
		result.push_back(layers.back().at(i).getOutput());
	}
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

	for (unsigned i = 1; i < layers.size(); ++i) {
		Layer& prevLayer = layers.at(i - 1);
		for (size_t j = 0; j < layers.at(j).size() - 1; ++j) {
			layers.at(0).at(j).feedForward(prevLayer);
		}
	}
}