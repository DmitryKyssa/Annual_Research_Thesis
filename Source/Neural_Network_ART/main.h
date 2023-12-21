#pragma once

void trainNeuralNetwork(Trainer& trainData, std::vector<double>& inputValues, std::vector<unsigned int>& topology, Net& firstNet, std::vector<double>& resultValues, std::vector<double>& targetValues);

void insertIntoTheTable(std::stringstream& ss, std::vector<std::string>& columnsNames, Net& firstNet);

void updateNetworkInfo(std::stringstream& ss, Net& firstNet, std::vector<std::string>& columnsNames);

void CheckIfRowExists(Net& firstNet, int& exec, sqlite3* database, sqlite3_stmt*& stmt);
