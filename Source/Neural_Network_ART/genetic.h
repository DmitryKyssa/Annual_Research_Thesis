#pragma once

#include <vector>
#include "net.h"

class Genetic
{
public:
	std::vector<Net> population;
	void crossover(Net* mother, Net* father);
	void selection();
};