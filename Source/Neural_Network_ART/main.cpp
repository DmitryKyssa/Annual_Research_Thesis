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
	std::vector<unsigned> topology;

	trainData.getTopology(topology);
	Net myNet(topology);

	std::vector<double> inputValues, targetValues, resultValues;

	std::stringstream buffer;
	std::streambuf* last = std::cout.rdbuf(buffer.rdbuf());

	int trainingPass = 0;
	while (!trainData.getEOF())
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

	int exec = sqlite3_open("neural_network.db", &database);

	if (exec) {
		std::cout << "Cannot open!" << std::endl;
	}
	else {
		std::cout << "Opened!" << std::endl;
	}

	std::string addTable = "CREATE TABLE IF NOT EXISTS trainingOutput (" 
		"id INTEGER PRIMARY KEY AUTOINCREMENT, " 
		"data VARCHAR(10000));";

	char* errorMessage;

	exec = sqlite3_exec(database, addTable.c_str(), NULL, NULL, &errorMessage);

	std::cout  << errorMessage << std::endl;

	std::string insert = "INSERT INTO trainingOutput (data) VALUES (?);";

	exec = sqlite3_prepare_v3(database, insert.c_str(), (int)insert.length(), 0, &stmt, 0);

	exec = sqlite3_bind_text(stmt, 1, buffer.str().c_str(), (int)buffer.str().length(), SQLITE_STATIC);

	exec = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	sqlite3_close(database);

	/*Genetic genAlgo;

	genAlgo.population.push_back(myNet);*/
}