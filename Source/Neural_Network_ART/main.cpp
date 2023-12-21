#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <sstream>
#include <winsqlite/winsqlite3.h>
#include "trainer.h"
#include "net.h"
#include "genetic.h"

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
	std::vector<unsigned int> topology;

	trainData.getTopology(topology);
	Net myNet(topology);

	std::vector<double> inputValues, targetValues, resultValues;

	//std::stringstream buffer;
	//std::streambuf* last = std::cout.rdbuf(buffer.rdbuf());

	int trainingPass = 0;
	while (!trainData.getEOF() || myNet.getError() < 0.05)
	{
		trainingPass++;
		std::cout << std::endl << "Pass:" << trainingPass;

		if (trainData.getNextInputs(inputValues) != topology.at(0))
			break;
		std::cout << " Inputs:" << inputValues;
		myNet.forwardPropagation(inputValues);

		myNet.getResults(resultValues);
		std::cout << "Outputs:" << resultValues;

		trainData.getTargetOutputs(targetValues);
		std::cout << "Targets:" << targetValues;
		assert(targetValues.size() == topology.back());

		myNet.backPropagation(targetValues);

		std::cout << "Net average error: " << myNet.getError() << std::endl;
	}

	std::cout << std::endl << "Finish" << std::endl;

	sqlite3* database;
	sqlite3_stmt* stmt;

	int exec = sqlite3_open("neural_network.sqlite", &database);

	std::cout << "Opening: " << exec << std::endl;

	std::stringstream addTable_ss;
	addTable_ss << "CREATE TABLE IF NOT EXISTS nn_info ("
		"Name TEXT, "
		"Error REAL";

	for (size_t l = 0; l < myNet.getLayers().size(); l++) {
		for (size_t n = 0; n < myNet.getLayers().at(l).size(); n++) {
			addTable_ss << ", Output_of_neuron_" << (n + 1) << "_of_layer_" << (l + 1) << " REAL";
			addTable_ss << ", Weights_of_neuron_" << (n + 1) << "_of_layer_" << (l + 1) << " TEXT";
		}
	}

	addTable_ss << ");";

	std::string addTable = addTable_ss.str();

	//std::cout << addTable << std::endl;

	exec = sqlite3_prepare_v3(database, addTable.c_str(), (int)addTable.length(), 0, &stmt, 0);
	std::cout << "Add header: " << exec << std::endl;

	//std::string insert = "INSERT INTO trainingOutput (data) VALUES (?);";

	//exec = sqlite3_prepare_v3(database, insert.c_str(), (int)insert.length(), 0, &stmt, 0);

	//exec = sqlite3_bind_text(stmt, 1, buffer.str().c_str(), (int)buffer.str().length(), SQLITE_STATIC);

	exec = sqlite3_step(stmt);
	std::cout << "Evaluate statement: " << exec << std::endl;
	sqlite3_finalize(stmt);

	exec = sqlite3_close(database);
	std::cout << "Close database: " << exec << std::endl;


	/*Genetic genAlgo;

	genAlgo.population.push_back(myNet);*/
}