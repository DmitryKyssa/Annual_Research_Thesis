#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <sstream>
#include <winsqlite/winsqlite3.h>
#include "trainer.h"
#include "net.h"
#include "genetic.h"
#include "main.h"

std::ostream& operator<<(std::ostream& out, std::vector<double>& vector) {
	for (size_t i = 0; i < vector.size(); i++)
	{
		out << vector.at(i) << " ";
	}
	out << std::endl;

	return out;
}

void trainNeuralNetwork(Trainer& trainData, std::vector<double>& inputValues, std::vector<unsigned int>& topology, Net& firstNet, std::vector<double>& resultValues, std::vector<double>& targetValues)
{
	int trainingPass = 0;
	while (!trainData.getEOF())
	{
		trainingPass++;
		std::cout << std::endl << "Pass:" << trainingPass;

		if (trainData.getNextInputs(inputValues) != topology.at(0))
			break;
		std::cout << " Inputs:" << inputValues;
		firstNet.forwardPropagation(inputValues);

		firstNet.getResults(resultValues);
		std::cout << "Outputs:" << resultValues;

		trainData.getTargetOutputs(targetValues);
		std::cout << "Targets:" << targetValues;
		assert(targetValues.size() == topology.back());

		firstNet.backPropagation(targetValues);

		std::cout << "Net average error: " << firstNet.getError() << std::endl;
	}
	std::cout << std::endl << "Finish" << std::endl;
}

bool checkIfRowExistsInTable(Net& net, int& exec, sqlite3* database, sqlite3_stmt*& stmt)
{
	std::string checkIfRowExists = "SELECT EXISTS(SELECT 1 FROM nn-info WHERE Name=" + net.getName() + " LIMIT 1);";
	exec = sqlite3_prepare_v3(database, checkIfRowExists.c_str(), (int)checkIfRowExists.length(), 0, &stmt, 0);
	std::cout << "Check if row exists: " << exec << std::endl;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	if (exec == 0) {
		return false;
	}
	else return true;
}

void insertIntoTheTable(std::stringstream& ss, std::vector<std::string>& columnsNames, Net& net)
{
	ss << "INSERT INTO nn_info (";
	for (size_t i = 0; i < columnsNames.size(); i++) {
		if (i == columnsNames.size() - 1) {
			ss << columnsNames.at(i) << ")";
			continue;
		}
		ss << columnsNames.at(i) << ", ";
	}
	ss << " VALUES ('" << net.getName() << "', " << std::to_string(net.getError()) << ",";
	for (size_t l = 0; l < net.getLayers().size(); l++) {
		for (size_t n = 0; n < net.getLayers().at(l).size(); n++) {
			ss << std::to_string(net.getLayers().at(l).at(n).getOutput()) << ",";
			ss << "'";
			if (net.getLayers().at(l).at(n).getOutputWeights().size() == 0) {
				ss << " ";
			}
			for (size_t w = 0; w < net.getLayers().at(l).at(n).getOutputWeights().size(); w++) {
				ss << " " << net.getLayers().at(l).at(n).getOutputWeights().at(w).weight;
			}
			if ((l == net.getLayers().size() - 1) && (n == net.getLayers().at(l).size() - 1)) {
				ss << "'";
			}
			else
				ss << "',";
		}
	}
	ss << ");";
}

void updateNetworkInfo(std::stringstream& ss, Net& net, std::vector<std::string>& columnsNames)
{
	ss << "UPDATE nn_info SET Error = " << net.getError() << ",";
	int columnIndex = 2;
	for (size_t l = 0; l < net.getLayers().size(); l++) {
		for (size_t n = 0; n < net.getLayers().at(l).size(); n++) {
			ss << columnsNames.at(columnIndex) << " = " << std::to_string(net.getLayers().at(l).at(n).getOutput()) << ",";
			columnIndex++;
			if (net.getLayers().at(l).at(n).getOutputWeights().size() == 0) {
				ss << " ";
			}
			ss << columnsNames.at(columnIndex) << " = ";
			ss << "'";
			for (size_t w = 0; w < net.getLayers().at(l).at(n).getOutputWeights().size(); w++) {
				ss << " " << net.getLayers().at(l).at(n).getOutputWeights().at(w).weight;
			}
			columnIndex++;
			if ((l == net.getLayers().size() - 1) && (n == net.getLayers().at(l).size() - 1)) {
				ss << "'";
			}
			else
				ss << "',";
		}
	}
	ss << "WHERE Name = '" << net.getName() << "';";
}

int main()
{
	Trainer trainerFirstNetwork("DataForTraining.txt");
	Trainer trainerSecondNetwork("DataForTraining.txt");
	std::vector<unsigned int> topologyFirst, topologySecond;

	trainerFirstNetwork.getTopology(topologyFirst);
	Net firstNet(topologyFirst);
	trainerSecondNetwork.getTopology(topologySecond);
	Net secondNet(topologySecond);

	std::vector<double> inputValues, targetValues, resultValues;

	trainNeuralNetwork(trainerFirstNetwork, inputValues, topologyFirst, firstNet, resultValues, targetValues);
	trainNeuralNetwork(trainerSecondNetwork, inputValues, topologySecond, secondNet, resultValues, targetValues);

	sqlite3* database;
	sqlite3_stmt* stmt;

	int exec = sqlite3_open("neural_network.sqlite", &database);

	std::cout << "Opening: " << exec << std::endl;

	std::stringstream ss;
	ss << "CREATE TABLE IF NOT EXISTS nn_info ("
		"Name TEXT PRIMARY KEY, "
		"Error REAL";
	for (size_t l = 0; l < firstNet.getLayers().size(); l++) {
		for (size_t n = 0; n < firstNet.getLayers().at(l).size(); n++) {
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

	ss.str("");
	if (checkIfRowExistsInTable(firstNet, exec, database, stmt) == false) {
		insertIntoTheTable(ss, columnsNames, firstNet);

		std::string insert = ss.str();
		exec = sqlite3_prepare_v3(database, insert.c_str(), (int)insert.length(), 0, &stmt, 0);
		exec = sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		updateNetworkInfo(ss, firstNet, columnsNames);

		//std::cout << ss.str() << std::endl;

		std::string update = ss.str();

		exec = sqlite3_prepare_v3(database, update.c_str(), (int)update.length(), 0, &stmt, 0);
		std::cout << "Update data: " << exec << std::endl;
		//std::cout << sqlite3_errmsg(database) << std::endl;
		exec = sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}

	ss.str("");
	if (checkIfRowExistsInTable(secondNet, exec, database, stmt) == false) {
		insertIntoTheTable(ss, columnsNames, secondNet);

		std::string insert = ss.str();
		exec = sqlite3_prepare_v3(database, insert.c_str(), (int)insert.length(), 0, &stmt, 0);
		exec = sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}
	else {
		updateNetworkInfo(ss, secondNet, columnsNames);

		//std::cout << ss.str() << std::endl;

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