#include "genetic.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>

std::vector<Net> Genetic::population;

Layer Genetic::mutation(Layer& layer)
{
	for (size_t i = 0; i < layer.size(); i++)
	{
		for (size_t j = 0; j < layer.at(i).getOutputWeights().size(); j++)
		{
			int probability = rand() % 100;
			if (probability < MUTATION_PROBABILITY)
			{
				layer.at(i).getOutputWeights().at(j) = (rand() % 100) / 100.0;
			}
		}
	}
	return layer;
}

const Net Genetic::crossover(const Net& mother, const Net& father)
{
	Net child(mother);
	child.setName(Net::networksNames.back());
	Net::networksNames.pop_back();
	Layer input = child.getLayers().at(0);

	for (size_t j = 0; j < input.size(); j++) 
	{
		for (size_t k = 0; k < input.at(j).getOutputWeights().size(); k++) 
		{
			int probability = rand() % 100;
			if (probability < 50) 
			{
				input.at(j).getOutputWeights().at(k) = father.getLayers().at(0).at(j).getOutputWeights().at(k);
			}
		}
	}

	Layer hidden = child.getLayers().at(1);
	child.getLayers().at(1) = mutation(hidden);

	return child;
}

void Genetic::selection()
{
	std::sort(population.begin(), population.end(), [](const Net& a, const Net& b)
		{
			return a.getDistance() < b.getDistance();
		});
	reduction();
}

void Genetic::reduction()
{
	for (size_t i = 2; i < population.size(); i++)
	{
		Net::networksNames.push_back(population.at(i).getName());
	}
	population.erase(population.begin() + 2, population.end());
}

double Genetic::calculateFitnessByEuclidianDistance(std::vector<double> output, std::vector<double> target)
{
	if (output.size() != target.size())
	{
		std::cout << "Sizes of output and target vectors aren't equal!" << std::endl;
		return 0.0;
	}
	double sum = 0.0;
	for (size_t i = 0; i < output.size(); ++i)
	{
		double diff = output[i] - target[i];
		sum += diff * diff;
	}
	return std::sqrt(sum);
}

double Genetic::calculateFitnessByManhattanDistance(std::vector<double> output, std::vector<double> target)
{
	if (output.size() != target.size())
	{
		std::cout << "Sizes of output and target vectors aren't equal!" << std::endl;
		return 0.0;
	}
	double sum = 0.0;
	for (size_t i = 0; i < output.size(); ++i)
	{
		sum += std::abs(output[i] - target[i]);
	}
	return sum;
}