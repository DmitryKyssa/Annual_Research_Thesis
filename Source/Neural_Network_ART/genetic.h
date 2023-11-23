#pragma once

#include <vector>
#include "net.h"

const size_t MAX_POPULATION = 10;

class Genetic
{
public:
	std::vector<Net> population;
	void crossover(Net* mother, Net* father);
	void selection();
	void reduction();
	void mutation();
};