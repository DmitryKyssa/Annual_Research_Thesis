#include "genetic.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>

std::vector<Net> Genetic::population;

void Genetic::crossover(Net* mother, Net* father)
{
	Net firstChild = *mother;
	Net secondChild = *father;
	Layer firstChildInput = firstChild.getLayers().at(0);
	Layer secondChildInputt = secondChild.getLayers().at(0);
	for (size_t i = 0; i < firstChildInput.size(); i++) {
		auto firstChildInputWeights = firstChildInput.at(i).getOutputWeights();
		auto secondChildInputWeights = secondChildInputt.at(i).getOutputWeights();
		for (size_t j = 0; j < firstChildInputWeights.size(); j++) {
			int probability = rand() % 100;
			if (probability < 50) {
				firstChildInputWeights.at(j).weight = mother->getLayers().at(0).at(j).getOutputWeights().at(j).weight;
				secondChildInputWeights.at(j).weight = father->getLayers().at(0).at(j).getOutputWeights().at(j).weight;
			}
			else {
				firstChildInputWeights.at(j).weight = father->getLayers().at(0).at(j).getOutputWeights().at(j).weight;
				secondChildInputWeights.at(j).weight = mother->getLayers().at(0).at(j).getOutputWeights().at(j).weight;
			}
		}
	}

	population.push_back(firstChild);
	population.push_back(secondChild);
}

void Genetic::selection()
{
	for (size_t i = 0; i < population.size(); i++) {
		mutation(i);
	}
	std::sort(population.begin(), population.end(), [](Net a, Net b) {
		return a.getFitness() < b.getFitness();
		});
	reduction();
}

void Genetic::reduction()
{
	for (size_t i = population.size(); i > 2; --i) {
		population.pop_back();
	}
}

void Genetic::mutation(size_t index)
{
	int probability = rand() % 100;
	//std::cout << probability << std::endl;
	if (probability < MUTATION_PROBABILITY) {
		//std::cout << "Mutation!" << std::endl;
		auto layers = population.at(index).getLayers();
		for (Neuron& neuron : layers.at(0)) {
			auto outputWeights = neuron.getOutputWeights();
			for (Synapse& synapse : outputWeights) {
				synapse.weight = rand() / double(RAND_MAX);
			}
		}
	}
}

int Genetic::calculateFitness(std::string convertedOutput, std::string convertedTarget)
{
	int fitness = 0;
	for (size_t i = 0; i < convertedOutput.size(); i++) {
		if (convertedOutput.at(i) == convertedTarget.at(i)) {
			fitness++;
		}
	}
	return fitness;
}