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

int main() {
	//AlphanumericGenerator gen;
	Database db;

	std::string tableForTests = "strings";
	//std::string query = "(ID INT PRIMARY KEY NOT NULL, STRING TEXT NOT NULL);";
	//db.createTable(tableForTests, query);
	////tableForTests += " (ID,STRING) ";
	//for (int i = 0; i < TESTS_NUMBER; i++) {
	//	std::string randomString = gen.generateRandomString(100);
	//	std::string values = "VALUES (" + std::to_string(i) + ", '" + randomString + "');";
	//	db.insert(tableForTests, values);
	//}
	//query = "";
	std::string selection = "STRING";
	int test_id = 1;
	//std::string str = db.select(tableForTests, selection, test_id);

	std::string str = "Hello, world!beunivrvniwrenvindeivjnijewdvjnidjevijnwdejvjnwedivnjnjgenijwreigvndijnvejjgnreiwgiemm";
	char symbol = 'w';

	std::vector<unsigned int> topology = { static_cast<unsigned int>(str.length()), 2, 2 };
	//auto start = std::chrono::high_resolution_clock::now();
	Net firstNet{ topology, Net::networksNames.back() };
	Net::networksNames.pop_back();
	//auto finish = std::chrono::high_resolution_clock::now();
	//auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
	//std::cout << "Microseconds: " << duration.count() << std::endl;
	//start = std::chrono::high_resolution_clock::now();
	Net secondNet{ topology, Net::networksNames.back() };
	Net::networksNames.pop_back();
	//finish = std::chrono::high_resolution_clock::now();
	//duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
	//std::cout << "Microseconds: " << duration.count() << std::endl;

	std::cout << "First net: " << firstNet.getName() << std::endl;
	std::cout << "Second net: " << secondNet.getName() << std::endl;

	std::vector<double> input = StringNormalizer::normalize(str);
	std::cout << "Input: " << input << std::endl;
	//std::vector<double> target = StringNormalizer::findOneChar(input, symbol, (int)firstNet.getLayers().back().size() - 1);
	//std::vector<double> target = StringNormalizer::findSubstring(str, substr, 14);
	//std::string convertedTarget = StringNormalizer::convertToString(target);
	std::vector<double> target = { 1.0, 1.0 / 7.0 };
	std::cout << "Target: " << target << std::endl;

	int i = 1;
	//std::string result = "";
	//while (result.find(substr) == -1 || result == substr) {
	while (i < 1000) {
		std::cout << "Epoch: " << i << std::endl;

		for (size_t i = 0; i < 10; i++) {
			firstNet.forwardPropagation(input);
			firstNet.backPropagation(target);
			secondNet.forwardPropagation(input);
			secondNet.backPropagation(target);
		}

		//firstNet.setFitness(Genetic::calculateFitnessByCoincidence(StringNormalizer::convertToString(firstNet.getResults()), convertedTarget));
		//secondNet.setFitness(Genetic::calculateFitnessByCoincidence(StringNormalizer::convertToString(secondNet.getResults()), convertedTarget));
		//Genetic::population.at(i).setFitness(Genetic::calculateFitnessByCoincidence(convertedOutput, convertedTarget));
		//Genetic::population.at(i).setDistance(Genetic::calculateFitnessByEuclidianDistance(outputNeurons, target));
		firstNet.setDistance(Genetic::calculateFitnessByManhattanDistance(firstNet.getResults(), target));
		secondNet.setDistance(Genetic::calculateFitnessByManhattanDistance(secondNet.getResults(), target));

		std::cout << "First net: " << firstNet.getName() << " Distance: " << firstNet.getDistance() << std::endl;
		std::cout << "Second net: " << secondNet.getName() << " Distance: " << secondNet.getDistance() << std::endl;

		std::cout << "First net: " << firstNet.getName() << " Output: " << firstNet.getResults().at(0) << " "
			<< pow(firstNet.getResults().at(1), -1) << std::endl;
		std::cout << "Second net: " << secondNet.getName() << " Output: " << secondNet.getResults().at(0) << " "
			<< pow(secondNet.getResults().at(1), -1) << std::endl;

		//std::cout << "First net: " << firstNet.getName() << " Fitness: " << firstNet.getFitness() << std::endl;
		//std::cout << "Second net: " << secondNet.getName() << " Fitness: " << secondNet.getFitness() << std::endl;

		//std::cout << "Converted string first net: " << StringNormalizer::convertToString(firstNet.getResults()) << std::endl;
		//std::cout << "Converted string second net: " << StringNormalizer::convertToString(secondNet.getResults()) << std::endl;

		//if (firstNet.getFitness() > secondNet.getFitness()) {
		//	result = StringNormalizer::convertToString(firstNet.getResults());
		//}
		//else result = StringNormalizer::convertToString(secondNet.getResults());

		system("pause");

		i++;
	}


	/*
	size_t epoch = 0;
	std::string result = "";
	//while (result.find(substr) == -1)
	while (epoch < 1000)
	{
		for (size_t i = 0; i < 10000; i++) {
			firstNet.forwardPropagation(input);
			firstNet.backPropagation(target);
			secondNet.forwardPropagation(input);
			secondNet.backPropagation(target);
		}

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
			for (size_t j = 0; j < 1000; j++) {
				Genetic::population.at(i).forwardPropagation(input);
				Genetic::population.at(i).backPropagation(target);
			}
			std::vector<double> outputNeurons = Genetic::population.at(i).getResults();
			//std::string convertedOutput = StringNormalizer::convertToString(outputNeurons);
			//Genetic::population.at(i).setFitness(Genetic::calculateFitnessByCoincidence(convertedOutput, convertedTarget));
			//Genetic::population.at(i).setDistance(Genetic::calculateFitnessByEuclidianDistance(outputNeurons, target));
			Genetic::population.at(i).setDistance(Genetic::calculateFitnessByManhattanDistance(outputNeurons, target));
		}
		Genetic::selection();
		std::cout << "Selection is finished!" << std::endl;
		firstNet = Genetic::population.at(0);
		secondNet = Genetic::population.at(1);
		//while (firstNet.getFitness() == 0 || secondNet.getFitness() == 0)
		//{
		//	for (size_t i = 0; i < 10; i++) {
		//		firstNet.forwardPropagation(input);
		//		firstNet.backPropagation(target);
		//		secondNet.forwardPropagation(input);
		//		secondNet.backPropagation(target);
		//	}
		//	std::string firstNetOutput = StringNormalizer::convertToString(firstNet.getResults());
		//	firstNet.setFitness(Genetic::calculateFitnessByCoincidence(firstNetOutput, convertedTarget));
		//	std::string secondNetOutput = StringNormalizer::convertToString(secondNet.getResults());
		//	secondNet.setFitness(Genetic::calculateFitnessByCoincidence(secondNetOutput, convertedTarget));
		//}
		//std::cout << "First net: " << firstNet.getName() << " Fitness: " << firstNet.getFitness() << std::endl;
		//std::cout << "Second net: " << secondNet.getName() << " Fitness: " << secondNet.getFitness() << std::endl;
		std::cout << "First net: " << firstNet.getName() << " Distance: " << firstNet.getDistance() << std::endl;
		std::cout << "Second net: " << secondNet.getName() << " Distance: " << secondNet.getDistance() << std::endl;
		std::vector<double> outputNeurons;
		if (firstNet.getFitness() > secondNet.getFitness())
		{
			outputNeurons = firstNet.getResults();
		}
		else
		{
			outputNeurons = secondNet.getResults();
		}
		std::cout << "Converted string: " << StringNormalizer::convertToString(outputNeurons) << std::endl;
		std::cout << std::endl;
		epoch++;
		finish = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
		std::cout << "Microseconds: " << duration.count() << std::endl;
	}
	*/
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