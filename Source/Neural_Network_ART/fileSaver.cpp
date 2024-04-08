#include "fileSaver.h"
#include <iostream>
#include <fstream>

void FileSaver::saveToFile(const Net& net, const std::string& filename)
{
	std::ofstream file;
	file.open(filename);
	file << "Name: " << net.getName() << std::endl;
	file << "Number of layers: " << net.getLayers().size() << std::endl;
	for (size_t i = 0; i < net.getLayers().size(); i++)
	{
		file << "Number of neurons in layer " << i << ": " << net.getLayers().at(i).size() << std::endl;
	}
	for (size_t i = 0; i < net.getLayers().size(); i++)
	{
		for (size_t j = 0; j < net.getLayers().at(i).size(); j++)
		{
			file << "Neuron " << j << " in layer " << i << std::endl;
			//file << "Weights: " << *&(net.getLayers().at(i).at(j).getOutputWeights()) << std::endl;
		}
	}
	file << "Error: " << net.getError() << std::endl;
	file.close();
}


Net FileSaver::loadFromFile(const std::string& filename)
{
	std::ifstream file;
	file.open(filename);
	std::string name;
	std::vector<unsigned int> topology;
	std::vector<Layer> layers;
	double error;
	std::string line;
	while (std::getline(file, line))
	{
		if (line.find("Name: ") != std::string::npos)
		{
			name = line.substr(6);
			std::cout << "Name: " << name << std::endl;
		}
		else if (line.find("Number of layers: ") != std::string::npos)
		{
			unsigned int numberOfLayers = std::stoi(line.substr(18));
			for (size_t i = 0; i < numberOfLayers; i++)
			{
				std::getline(file, line);
				std::size_t pos = line.find(": ");
				if (pos != std::string::npos)
				{
					line = line.substr(pos + 1);
				}
				else
				{
					std::cout << "Error while reading number of neurons in layer " << i << std::endl;
				}
				unsigned int numberOfNeurons = std::stoi(line);
				topology.push_back(numberOfNeurons);
				std::cout << "Number of neurons in layer " << i << ": " << numberOfNeurons << std::endl;
			}
		}
		else if (line.find("Neuron ") != std::string::npos)
		{
			unsigned int layerIndex = std::stoi(line.substr(14, 1));
			unsigned int neuronIndex = std::stoi(line.substr(7, 1));
			std::vector<Synapse> outputWeights;
			for (size_t i = 0; i < topology.at(layerIndex + 1); i++)
			{
				std::getline(file, line);
				double weight = std::stod(line.substr(8));
				outputWeights.push_back(Synapse());
				outputWeights.back().weight = weight;
				std::cout << "Weight " << i << ": " << weight << std::endl;
			}
			layers.at(layerIndex).push_back(Neuron());
			//layers.at(layerIndex).back().getOutputWeights() = outputWeights;
		}
		else if (line.find("Error: ") != std::string::npos)
		{
			error = std::stod(line.substr(7));
			std::cout << "Error: " << error << std::endl;
		}
	}
	file.close();
	Net net(topology, name);
	return net;
}