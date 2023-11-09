#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include "trainer.h"
#include "net.h"

void printVector(std::string label, std::vector<double>& vector)
{
	std::cout << label << " ";
	for (size_t i = 0; i < vector.size(); i++)
	{
		std::cout << vector.at(i) << " ";
	}
	std::cout << std::endl;
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
		printVector(" Inputs :", inputVals);
		myNet.forwardPropagation(inputVals);

		myNet.getResults(resultVals);
		printVector("Outputs:", resultVals);

		trainData.getTargetOutputs(targetVals);
		printVector("Targets:", targetVals);
		assert(targetVals.size() == topology.back());

		myNet.backPropagation(targetVals);

		std::cout << "Net average error: " << myNet.getRecentAverageError() << std::endl;
	}

	std::cout << std::endl << "Finish" << std::endl;
}