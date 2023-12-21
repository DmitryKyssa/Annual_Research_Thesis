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

	int exec = sqlite3_open("neural_network.sqlite", &database);

	std::cout << "Opening: " << exec << std::endl;

	std::stringstream ss;
	ss << "CREATE TABLE IF NOT EXISTS nn_info ("
		"Name TEXT PRIMARY KEY, "
		"Error REAL";

	for (size_t l = 0; l < myNet.getLayers().size(); l++) {
		for (size_t n = 0; n < myNet.getLayers().at(l).size(); n++) {
			ss << ", Output_of_neuron_" << (n + 1) << "_of_layer_" << (l + 1) << " REAL";
			ss << ", Weights_of_neuron_" << (n + 1) << "_of_layer_" << (l + 1) << " TEXT";
		}
	}

	ss << ");";

	std::string addTable = ss.str();

	//std::cout << addTable << std::endl;

	exec = sqlite3_prepare_v3(database, addTable.c_str(), (int)addTable.length(), 0, &stmt, 0);
	std::cout << "Add header: " << exec << std::endl;
	exec = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	std::vector<std::string> columnsNames;
	std::string getNumberOfColumns = "PRAGMA table_info(nn_info);";
	exec = sqlite3_prepare_v3(database, getNumberOfColumns.c_str(), (int)getNumberOfColumns.length(), 0, &stmt, 0);

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		columnsNames.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
	}
	sqlite3_finalize(stmt);

	//for (size_t i = 0; i < columnsNames.size(); i++) {
	//	std::cout << columnsNames.at(i) << std::endl;
	//}

	std::string checkIfRowExists = "SELECT EXISTS(SELECT 1 FROM nn-info WHERE Name=" + myNet.getName() +" LIMIT 1);";
	exec = sqlite3_prepare_v3(database, checkIfRowExists.c_str(), (int)checkIfRowExists.length(), 0, &stmt, 0);
	std::cout << "Check if row exists: " << exec << std::endl;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	ss.str("");
	if (exec == 0) {
		ss << "INSERT INTO nn_info (";
		for (size_t i = 0; i < columnsNames.size(); i++) {
			if (i == columnsNames.size() - 1) {
				ss << columnsNames.at(i) << ")";
				continue;
			}
			ss << columnsNames.at(i) << ", ";
		}
		ss << " VALUES ('" << myNet.getName() << "', " << std::to_string(myNet.getError()) << ",";
		for (size_t l = 0; l < myNet.getLayers().size(); l++) {
			for (size_t n = 0; n < myNet.getLayers().at(l).size(); n++) {
				ss << std::to_string(myNet.getLayers().at(l).at(n).getOutput()) << ",";
				ss << "'";
				if (myNet.getLayers().at(l).at(n).getOutputWeights().size() == 0) {
					ss << " ";
				}
				for (size_t w = 0; w < myNet.getLayers().at(l).at(n).getOutputWeights().size(); w++) {
					ss << " " << myNet.getLayers().at(l).at(n).getOutputWeights().at(w).weight;
				}
				if ((l == myNet.getLayers().size() - 1) && (n == myNet.getLayers().at(l).size() - 1)) {
					ss << "'";
				}
				else
					ss << "',";
			}
		}
		ss << ");";
		std::cout << ss.str() << std::endl;

		std::string insert = ss.str();

		exec = sqlite3_prepare_v3(database, insert.c_str(), (int)insert.length(), 0, &stmt, 0);
		std::cout << "Add data: " << exec << std::endl;
		exec = sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		ss << "UPDATE nn_info SET Error = " << myNet.getError() << ",";
		int columnIndex = 2;
		for (size_t l = 0; l < myNet.getLayers().size(); l++) {
			for (size_t n = 0; n < myNet.getLayers().at(l).size(); n++) {
				ss << columnsNames.at(columnIndex) << " = " << std::to_string(myNet.getLayers().at(l).at(n).getOutput()) << ",";
				columnIndex++;
				if (myNet.getLayers().at(l).at(n).getOutputWeights().size() == 0) {
					ss << " ";
				}
				ss << columnsNames.at(columnIndex) << " = ";
				ss << "'";
				for (size_t w = 0; w < myNet.getLayers().at(l).at(n).getOutputWeights().size(); w++) {
					ss << " " << myNet.getLayers().at(l).at(n).getOutputWeights().at(w).weight;
				}
				columnIndex++;
				if ((l == myNet.getLayers().size() - 1) && (n == myNet.getLayers().at(l).size() - 1)) {
					ss << "'";
				}
				else
					ss << "',";
			}
		}
		ss << "WHERE Name = '" << myNet.getName() << "';";

		std::cout << ss.str() << std::endl;

		std::string update = ss.str();

		exec = sqlite3_prepare_v3(database, update.c_str(), (int)update.length(), 0, &stmt, 0);
		std::cout << "Update data: " << exec << std::endl;
		//std::cout << sqlite3_errmsg(database) << std::endl;
		exec = sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	
	//exec = sqlite3_bind_text(stmt, 1, buffer.str().c_str(), (int)buffer.str().length(), SQLITE_STATIC);

	exec = sqlite3_close(database);
	std::cout << "Close database: " << exec << std::endl;


	/*Genetic genAlgo;

	genAlgo.population.push_back(myNet);*/
}