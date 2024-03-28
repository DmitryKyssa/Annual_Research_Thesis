#pragma once

#include "net.h"

const size_t MAX_POPULATION = 10;
const int MUTATION_PROBABILITY = 75;

class Genetic
{
private:
	void static reduction();
public:
	static std::vector<Net> population;
	void static crossover(Net* mother, Net* father);
	void static selection();
	void static mutation(size_t index);
	int static calculateFitness(std::string convertedOutput, std::string convertedTarget);
};