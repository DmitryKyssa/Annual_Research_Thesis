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
				layer.at(i).getOutputWeights().at(j) = (rand() % 100) / 100.0;
			}
		}
	}
	return layer;
}

//TODO One child
const Net Genetic::crossover(const Net& mother, const Net& father)
{
	// Create a child from mother using overloaded operator=
	Net child(mother);
	// Set the name of the child using last name from Net::networksNames. After that, pop the last name from the vector.
	child.setName(Net::networksNames.back());
	Net::networksNames.pop_back();
	Layer input = child.getLayers().at(0);
	int counter = 0;
	for (size_t j = 0; j < input.size(); j++) {
		for (size_t k = 0; k < input.at(j).getOutputWeights().size(); k++) {
			int probability = rand() % 100;
			if (probability < 50) {
				counter++;
				input.at(j).getOutputWeights().at(k) = father.getLayers().at(0).at(j).getOutputWeights().at(k);
			}
		}
	}
	//std::cout << "Number of weights from father: " << counter << std::endl;

	child.getLayers().at(0) = Mutation(input);

	//std::cout << "Child name in crossover function: " << child.getName() << std::endl;
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
	// print names of the networks
	//for (size_t i = 0; i < population.size(); i++) {
	//	std::cout << "Net name before sorting: " << population.at(i).getName() << std::endl;
	//}
	// sort the population by fitness descending
	//std::sort(population.begin(), population.end(), [](const Net& a, const Net& b) {
	//	return a.getFitness() > b.getFitness();
	//});
	// sort the population by error ascending and fitness descending. First, sort by fitness, then by error.
	std::sort(population.begin(), population.end(), [](const Net& a, const Net& b) {
		if (a.getFitness() == b.getFitness()) {
			return a.getError() < b.getError();
		}
		return a.getFitness() > b.getFitness();
	});
	// print names of the networks
	//for (size_t i = 0; i < population.size(); i++) {
	//	std::cout << "Net name after sorting: " << population.at(i).getName() << std::endl;
	//}
	reduction();
}

void Genetic::reduction()
{
	for (size_t i = 2; i < population.size(); i++) {
		auto str = population.at(i).getName();
		str = "-" + str;
		Net::networksNames.push_back(str);
	}
	population.erase(population.begin() + 2, population.end());
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