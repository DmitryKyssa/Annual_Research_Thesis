#pragma once

#include <vector>
#include "net.h"

const size_t MAX_POPULATION = 10;
const int MUTATION_PROBABILITY = 50;

class Genetic
{
public:
	static std::vector<Net> population;
	void static crossover(Net* mother, Net* father);
	void static selection();
	void static reduction();
	void static mutation(size_t index);
};