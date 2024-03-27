#include "genetic.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>

std::vector<Net> Genetic::population;

void Genetic::crossover(Net* mother, Net* father)
{
	Net* childBoy = new Net(*mother);
	Net* childGirl = new Net(*father);

	for (size_t i = 0; i < (*(childBoy)).getLayers().size(); i++) {
		for (size_t j = 0; j < (*(childBoy)).getLayers().at(i).size() / 2; j++) {
			(*(childBoy)).getLayers().at(i).at(j).getOutputWeights() =
				father->getLayers().at(i).at(j).getOutputWeights();
			(*(childGirl)).getLayers().at(i).at(j).getOutputWeights() =
				mother->getLayers().at(i).at(j).getOutputWeights();
		}
	}
	population.push_back(*childBoy);
	population.push_back(*childGirl);
}

void Genetic::selection()
{
	std::sort(population.begin(), population.end(), [](Net a, Net b) {return a.getError() < b.getError(); });
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