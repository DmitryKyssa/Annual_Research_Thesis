#include "genetic.h"
#include <algorithm>

void Genetic::crossover(Net* mother, Net* father)
{
	Net* childBoy = new Net(*mother);
	Net* childGirl = new Net(*father);

	for (size_t i = 0; i < (*(childBoy)).getLayers().size(); i++) {
		for (size_t j = 0; j < (*(childBoy)).getLayers().at(i).size() / 2; j++) {
			(*(childBoy)).getLayers().at(i).at(j).getOutputWeights() = father->getLayers().at(i).at(j).getOutputWeights();
			(*(childGirl)).getLayers().at(i).at(j).getOutputWeights() = mother->getLayers().at(i).at(j).getOutputWeights();
		}
	}
}

void Genetic::selection()
{
	std
}