#include <iostream>
#include <vector>
#include <cstdlib>
#include "net.h"

std::ostream& operator<<(std::ostream& out, std::vector<double>& vector) {
	for (size_t i = 0; i < vector.size(); i++)
	{
		out << vector.at(i) << " ";
	}
	out << std::endl;

	return out;
}

int main() {
	std::vector<unsigned int> topology = {2, 5, 2};
	Net* net = new Net(topology);

	std::vector<double> input = {0.1, 0.8};
	net->forwardPropagation(input);
	std::vector<double> target = { 0, 1};
	net->backPropagation(target);

	std::cout << net->getError() << std::endl;

	for (size_t i = 0; i < net->getLayers().size(); i++)
	{
		std::cout << "Layer #" << i + 1 << std::endl;
		for (size_t j = 0; j < net->getLayers().at(i).size(); j++)
		{
			std::cout << net->getLayers().at(i).at(j).getOutput() << " ";
		}
		std::cout << std::endl;
	}
}