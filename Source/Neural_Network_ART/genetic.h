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
	void static selection();
	int static calculateFitnessByCoincidence(std::string convertedOutput, std::string convertedTarget);
	double static calculateFitnessByEuclidianDistance(std::vector<double> output, std::vector<double> target);
	double static calculateFitnessByManhattanDistance(std::vector<double> output, std::vector<double> target);
};