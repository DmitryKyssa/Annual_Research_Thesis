#include "genetic.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

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
}

void Genetic::selection()
{
	std::sort(population.begin(), population.end(), 
		[](Net a, Net b) {return a.getError() < b.getError();});
}

void Genetic::reduction()
{
	for (size_t i = population.size(); i >= MAX_POPULATION; --i) {
		population.pop_back();
	}
}

void Genetic::mutation(size_t index)
{
	srand((unsigned int)time(NULL));
	int probability = rand() % 100;
	if (probability < MUTATION_PROBABILITY) {
		for (Neuron neuron : population.at(index).getLayers().at(0)) {
			for (Synapse synapse : neuron.getOutputWeights()) {
				synapse.weight = rand() / double(RAND_MAX);
			}
		}
	}
}