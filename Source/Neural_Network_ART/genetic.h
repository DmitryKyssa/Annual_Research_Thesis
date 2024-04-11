#pragma once

#include "net.h"

const size_t MAX_POPULATION = 50;
const int MUTATION_PROBABILITY = 20;

class Genetic
{
private:
	void static reduction();
public:
	static std::vector<Net> population;
	Layer static mutation(Layer& layer);
	static const Net crossover(const Net& mother, const Net& father);
	Net static parthenogenesis(const Net& mother);
	void static geneticModification(const std::vector<double>& target);
	void static selection();
	void static mutation(const Net& net);
	int static calculateFitness(std::string convertedOutput, std::string convertedTarget);
};