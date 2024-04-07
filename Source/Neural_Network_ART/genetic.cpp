#include "genetic.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>

std::vector<Net> Genetic::population;

Layer Genetic::Mutation(Layer& layer)
{
	for (size_t i = 0; i < layer.size(); i++) {
		for (size_t j = 0; j < layer.at(i).getOutputWeights().size(); j++) {
			int probability = rand() % 100;
			if (probability < MUTATION_PROBABILITY) {
				layer.at(i).getOutputWeights().at(j).weight = (rand() % 100) / 100.0;
			}
		}
	}
	return layer;
}

//TODO One child
const Net Genetic::crossover(const Net& mother, const Net& father)
{
	Net child = mother;
	Layer input = child.getLayers().at(0);
	int counter = 0;
	for (size_t j = 0; j < input.size(); j++) {
		for (size_t k = 0; k < input.at(j).getOutputWeights().size(); k++) {
			int probability = rand() % 100;
			if (probability < 50) {
				counter++;
				input.at(j).getOutputWeights().at(k).weight = father.getLayers().at(0).at(j).getOutputWeights().at(k).weight;
			}
		}
	}
	std::cout << "Number of weights from father: " << counter << std::endl;

	child.getLayers().at(0) = Mutation(input);

	networksNames.pop_back();
	child.setName(networksNames.back());

	std::cout << "Child name in crossover function: " << child.getName() << std::endl;
	population.push_back(child);
	return child;
}

Net Genetic::parthenogenesis(const Net& mother)
{
	Net child(mother);
	return child;
}

void Genetic::geneticModification(const std::vector<double>& target)
{
}

void Genetic::selection()
{
	std::sort(population.begin(), population.end(), [](Net a, Net b) {
		return a.getFitness() < b.getFitness();
		});
	reduction();
}

void Genetic::reduction()
{
	for (size_t i = population.size(); i > 2; --i) {
		networksNames.push_back(population.at(i).getName());
		population.pop_back();
	}
}

//TODO Homogeneous functions => by objects (const Net&)
void Genetic::mutation(const Net& net)
{

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