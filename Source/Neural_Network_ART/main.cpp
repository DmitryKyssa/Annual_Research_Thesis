#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include "trainer.h"
#include "net.h"

std::ostream& operator<<(std::ostream& out, std::vector<double>& vector) {
	for (size_t i = 0; i < vector.size(); i++)
	{
		out << vector.at(i) << " ";
	}
	out << std::endl;

	return out;
}

int main()
{
	Trainer trainData("DataForTraining.txt");
	std::vector<unsigned> topology;

	trainData.getTopology(topology);
	Net myNet(topology);

	std::vector<double> inputVals, targetVals, resultVals;
	int trainingPass = 0;
	while (!trainData.getEOF())
	{
		trainingPass++;
		std::cout << std::endl << "Pass:" << trainingPass;

		if (trainData.getNextInputs(inputVals) != topology.at(0))
			break;
		std::cout << " Inputs :" << inputVals;
		myNet.forwardPropagation(inputVals);

		myNet.getResults(resultVals);
		std::cout << "Outputs:" << resultVals;

		trainData.getTargetOutputs(targetVals);
		std::cout << "Targets:" << targetVals;
		assert(targetVals.size() == topology.back());

		myNet.backPropagation(targetVals);

		std::cout << "Net average error: " << myNet.getRecentAverageError() << std::endl;
	}

	std::cout << std::endl << "Finish" << std::endl;
}