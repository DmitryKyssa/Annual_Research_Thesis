#include <iostream>
#include <vector>
#include <cstdlib>
#include "genetic.h"
#include "net.h"
#include "database.h"
#include "generator.h"
#include "normalizer.h"

const int TESTS_NUMBER = 100000;

static std::ostream& operator<<(std::ostream& out, std::vector<double>& vector) {
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
	std::string valueString = "STRING";

	//std::string query = "(ID INT PRIMARY KEY NOT NULL, STRING TEXT NOT NULL);";
	//db.createTable(tableForTests, query);
	//tableForTests += " (ID,STRING) ";
	//query = "";
	//for (int i = 0; i < TESTS_NUMBER; i++) {
	//	int stringLength = rand() % 1000 + 9000;
	//	query = "VALUES (" + std::to_string(i + 1) + ", '" + gen.generateRandomString(stringLength) + "'); ";
	//	db.insert(tableForTests, query);
	//	std::cout << "String added! " << i << std::endl;
	//}

	std::string test = db.getTestByID(tableForTests, valueString, 1);
	std::string str = "Hello world";
	char search = str[0];
	//std::string substr = test.substr(5, 500);

	std::vector<unsigned int> topology = { (unsigned int)str.length(), 5, (unsigned int)str.length() };
	Net* firstNet = new Net(topology);
	Net* secondNet = new Net(topology);

	std::vector<double> input = StringNormalizer::normalize(str);
	std::vector<double> target = StringNormalizer::findOneChar(input, search, firstNet->getLayers().back().size());
	//std::vector<double> target = StringNormalizer::findSubstring(test, substr, net->getLayers().back().size());
	//std::cout << "Targets: " << target << std::endl;

	firstNet->forwardPropagation(input);
	firstNet->backPropagation(target);
	secondNet->forwardPropagation(input);
	secondNet->backPropagation(target);

	Genetic::population.push_back(*firstNet);
	Genetic::population.push_back(*secondNet);

	size_t epoch = 0;
	std::string result = "";
	//while (result.find(substr) == -1)
	//while (result.find(search) == -1)
	while (epoch < 1000)
	{
		std::cout << "Epoch #" << epoch + 1 << std::endl;
		while (Genetic::population.size() < MAX_POPULATION)
		{
			Genetic::crossover(firstNet, secondNet);
		}
		std::cout << "Population size after crossover: " << Genetic::population.size() << std::endl;
		for (size_t i = 0; i < Genetic::population.size(); i++)
		{
			Genetic::mutation(i);
		}
		std::cout << "Mutation" << std::endl;
		Genetic::selection();
		std::cout << "Selection" << std::endl;
		Genetic::reduction();
		std::cout << "Population size after reduction: " << Genetic::population.size() << std::endl;
		Net bestNet = Genetic::population.back();
		for (size_t j = 2; j < bestNet.getLayers().size(); j++)
		{
			std::cout << "Layer #" << j + 1 << std::endl;
			for (size_t k = 0; k < bestNet.getLayers().at(j).size(); k++)
			{
				std::cout << bestNet.getLayers().at(j).at(k).getOutput() << " ";
			}
			std::cout << std::endl;
		}
		std::vector<double> outputNeurons = bestNet.getResults();
		result = StringNormalizer::convertToString(outputNeurons);
		std::cout << "Converted string: " << result << std::endl;
		std::cout << "Error: " << bestNet.getError() << std::endl;
		std::cout << std::endl;

		//firstNet->forwardPropagation(input);
		//firstNet->backPropagation(target);

		//for (size_t j = 2; j < firstNet->getLayers().size(); j++)
		//{
		//	std::cout << "Layer #" << j + 1 << std::endl;
		//	for (size_t k = 0; k < firstNet->getLayers().at(j).size(); k++)
		//	{
		//		std::cout << firstNet->getLayers().at(j).at(k).getOutput() << " ";
		//	}
		//	std::cout << std::endl;
		//}
		//std::vector<double> outputNeurons = firstNet->getResults();
		//result = StringNormalizer::convertToString(outputNeurons);
		//std::cout << "Converted string: " << result << std::endl;
		//std::cout << "Error " << i + 1 << ": " << firstNet->getError() << std::endl;
		//std::cout << std::endl;
		epoch++;
	}

	return 0;
}