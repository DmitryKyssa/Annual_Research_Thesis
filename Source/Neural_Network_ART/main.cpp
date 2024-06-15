#include <iostream>
#include <vector>
#include <cstdlib>
#include "genetic.h"
#include "database.h"
#include "generator.h"
#include "normalizer.h"
#include "fileSaver.h"
#include <chrono>

const int TESTS_NUMBER = 100;

std::ostream& operator<<(std::ostream& out, std::vector<double>& vector) {
	for (size_t i = 0; i < vector.size(); i++)
	{
		out << vector.at(i) << " ";
	}
	out << std::endl;

	return out;
}

enum DistanceCalculating
{
	Euclidian,
	Manhattan
};

int main() {
	AlphanumericGenerator gen;
	Database db;
	char symbol = 'c';
	int outputLayerSize = 2;
	bool updateTableIfExists = false;

	std::string tableForTests = "tests";
	std::string query = "(TEST TEXT NOT NULL, SYMBOL INT NOT NULL, POSITION INT NOT NULL);";
	db.createTable(tableForTests, query);
	query = "";

	if (!db.tableExists(tableForTests) || updateTableIfExists)
	{
		std::cout << "creating or updating" << std::endl;
		for (int i = 1; i <= TESTS_NUMBER; i++) {
			std::string randomString = gen.generateRandomString(100);
			std::vector<double> normalizedRandomString = StringNormalizer::normalize(randomString);
			std::vector<double> result = StringNormalizer::findOneChar(normalizedRandomString, symbol, outputLayerSize);
			std::string values = "VALUES ('" + randomString + "', " + std::to_string(result.at(0)) + ", " + std::to_string(result.at(1)) + ");";

			if (db.tableExists(tableForTests) && !db.isTableFull(tableForTests))
			{
				std::string update = "TEST = '" + randomString + "', SYMBOL = " + std::to_string(result.at(0)) + ", POSITION = " + std::to_string(result.at(1));
				db.update(tableForTests, update, i);
			}
			else
			{
				db.insert(tableForTests, values);
			}
		}
	}

	std::string selection = "TEST";
	int test_id = 1;
	std::string str = db.select(tableForTests, selection, test_id);

	std::vector<unsigned int> topology = { static_cast<unsigned int>(str.length()), 5, static_cast<unsigned int>(outputLayerSize) };
	auto start = std::chrono::high_resolution_clock::now();
	Net firstNet{ topology, Net::networksNames.back() };
	Net::networksNames.pop_back();
	auto finish = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
	std::cout << "Microseconds for creating first net: " << duration.count() << std::endl;
	start = std::chrono::high_resolution_clock::now();
	Net secondNet{ topology, Net::networksNames.back() };
	Net::networksNames.pop_back();
	finish = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
	std::cout << "Microseconds for creating second net: " << duration.count() << std::endl;

	std::vector<double> input = StringNormalizer::normalize(str);
	std::cout << "Input: " << input << std::endl;

	std::vector<double> target(outputLayerSize, 0.0);
	selection = "SYMBOL";
	target.at(0) = std::stoi(db.select(tableForTests, selection, test_id));
	selection = "POSITION";
	int index = std::stoi(db.select(tableForTests, selection, test_id));
	target.at(1) = 1.0 / index;
	std::cout << "Target: " << target << std::endl;
	std::cout << "Index: " << index << std::endl;

	DistanceCalculating method = DistanceCalculating::Manhattan;

	std::cout << "Enter number of epochs: ";
	size_t maxEpochs = 0;
	std::cin >> maxEpochs;

	size_t epoch = 0;
	while (epoch < maxEpochs)
	{
		firstNet.forwardPropagation(input);
		firstNet.backPropagation(target);
		secondNet.forwardPropagation(input);
		secondNet.backPropagation(target);

		Genetic::population.push_back(firstNet);
		Genetic::population.push_back(secondNet);

		std::cout << "Epoch #" << epoch + 1 << std::endl;
		start = std::chrono::high_resolution_clock::now();

		while (Genetic::population.size() < MAX_POPULATION)
		{
			Net child = Genetic::crossover(firstNet, secondNet);
			Genetic::population.push_back(child);
		}

		for (size_t i = 2; i < Genetic::population.size(); i++)
		{
			for (size_t j = 0; j < 5; j++)
			{
				Genetic::population.at(i).forwardPropagation(input);
				Genetic::population.at(i).backPropagation(target);
			}
		}

		if (method == DistanceCalculating::Manhattan)
		{
			for (size_t i = 0; i < Genetic::population.size(); i++)
			{
				Genetic::population.at(i).setDistance(Genetic::calculateFitnessByManhattanDistance(Genetic::population.at(i).getResults(), target));
			}
		}
		else
		{
			for (size_t i = 0; i < Genetic::population.size(); i++)
			{
				Genetic::population.at(i).setDistance(Genetic::calculateFitnessByEuclidianDistance(Genetic::population.at(i).getResults(), target));
			}
		}

		Genetic::selection();

		firstNet = Genetic::population.at(0);
		secondNet = Genetic::population.at(1);

		std::cout << "First net: " << firstNet.getName() << " with distance: " << firstNet.getDistance()
			<< ", output: " << firstNet.getResults().at(0) << " " << firstNet.getResults().at(1)
			<< " and index: " << round(pow(firstNet.getResults().at(1), -1)) << std::endl;
		std::cout << "Second net: " << secondNet.getName() << " with distance: " << secondNet.getDistance()
			<< ", output: " << secondNet.getResults().at(0) << " " << secondNet.getResults().at(1)
			<< " and index: " << round(pow(secondNet.getResults().at(1), -1)) << std::endl;

		//system("pause");

		epoch++;
		finish = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
		std::cout << "Microseconds for training: " << duration.count() << std::endl;
		std::cout << std::endl;
	}

	std::cout << "Enter string: ";
	std::string userInput;
	std::cin >> userInput;
	while (userInput.size() <= 100)
	{
		userInput += " ";
	}
	std::cout << "Enter symbol: ";
	char userSymbol;
	std::cin >> userSymbol;

	std::vector<double> userNormalizedInput = StringNormalizer::normalize(userInput);
	std::vector<double> result = StringNormalizer::findOneChar(userNormalizedInput, userSymbol, outputLayerSize);
	target.at(0) = result.at(0);
	target.at(1) = 1.0 / result.at(1);

	for (int i = 0; i < 200; i++)
	{
		firstNet.forwardPropagation(userNormalizedInput);
		firstNet.backPropagation(target);
	}

	std::cout << "First net: " << firstNet.getName() << " with distance: " << firstNet.getDistance()
		<< ", output: " << firstNet.getResults().at(0) << " " << firstNet.getResults().at(1)
		<< " and index: " << round(pow(firstNet.getResults().at(1), -1)) << std::endl;
	/*
	std::string tableForNetworks = "networks";
	std::string queryForNetworks = "(NET_NAME TEXT NOT NULL);";
	db.createTable(tableForNetworks, queryForNetworks);
	std::string valuesForNetworks = "VALUES ('" + firstNet.getName() + "');";
	db.insert(tableForNetworks, valuesForNetworks);

	std::string tableForLayers = "layers";
	std::string queryForLayers = "(NET_NAME TEXT NOT NULL, LAYER_ID INT NOT NULL);";
	db.createTable(tableForLayers, queryForLayers);
	for (size_t i = 0; i < firstNet.getLayers().size(); i++)
	{
		std::string valuesForLayers = "VALUES ('" + firstNet.getName() + "', " + std::to_string(i + 1) + ");";
		db.insert(tableForLayers, valuesForLayers);
	}

	std::string tableForNeurons = "neurons";
	std::string queryForNeurons = "(NET_NAME TEXT NOT NULL, LAYER_ID INT NOT NULL, NEURON INT NOT NULL, OUTPUT REAL NOT NULL);";
	db.createTable(tableForNeurons, queryForNeurons);
	for (size_t i = 0; i < firstNet.getLayers().size(); i++)
	{
		for (size_t j = 0; j < firstNet.getLayers().at(i).size(); j++)
		{
			std::string valuesForNeurons = "VALUES ('" + firstNet.getName() + "', " + std::to_string(i + 1) + ", " + std::to_string(j + 1) + ", " + std::to_string(firstNet.getLayers().at(i).at(j).getOutput()) + ");";
			db.insert(tableForNeurons, valuesForNeurons);
		}
	}

	std::string tableForResults = "results";
	std::string queryForResults = "(NET_NAME TEXT NOT NULL, TEST_ID INT NOT NULL, POPULATION_SIZE INT NOT NULL, TARGET TEXT NOT NULL, "
		"EPOCHES INT NOT NULL); ";
	db.createTable(tableForResults, queryForResults);
	std::string valuesForResults = "VALUES ('" + firstNet.getName() + "', " + std::to_string(test_id) + ", " + std::to_string(MAX_POPULATION) + ", " + "'" + substr + "', " + std::to_string(epoch) + ");";
	db.insert(tableForResults, valuesForResults);
	//*/
	return 0;
}