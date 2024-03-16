#include <iostream>
#include <vector>
#include <cstdlib>
#include "net.h"
#include "database.h"
#include "Constants.h"
#include "generator.h"
#include "normalizer.h"

static std::ostream& operator<<(std::ostream& out, std::vector<double>& vector) {
	for (size_t i = 0; i < vector.size(); i++)
	{
		out << vector.at(i) << " ";
	}
	out << std::endl;

	return out;
}

int main() {
	//for (int i = 0; i < 100; i++) {
	//	double x = rand() / double(RAND_MAX);
	//	std::cout << x << std::endl;
	//}

	AlphanumericGenerator gen;
	Database db(DATABASE);
	std::string tableForTests = "strings";
	std::string valueString = "STRING";

	//std::string query = "(ID INT PRIMARY KEY NOT NULL, STRING TEXT NOT NULL);";
	//db.createTable(tableForTests, query);
	//tableForTests += " (ID,STRING) ";
	//query = "";
	//for (int i = 0; i < TESTS_NUMBER; i++) {
	//	query = "VALUES (" + std::to_string(i + 1) + ", '" + gen() + "'); ";
	//	db.insert(tableForTests, query);
	//	std::cout << "String added!" << std::endl;
	//}

	std::vector<unsigned int> topology = { 62, 100, 62 };
	Net* net = new Net(topology);

	std::string test = db.getTestByID(tableForTests, valueString, 1);
	//std::string str = "afZ";
	std::vector<double> input = StringNormalizer::normalize(test);
	std::vector<double> target = StringNormalizer::findTarget(input, 'o', net->getLayers().back().size());
	std::cout << target << std::endl;

	size_t i = 0;
	std::string result = "";
	//while (result.find('o') == -1)
	while(i < 10)
	{
		net->forwardPropagation(input);
		net->backPropagation(target);
		for (size_t j = 0; j < input.size(); j++)
		{
			input.at(j) = net->getLayers().back().at(j).getOutput();
		}
		for (size_t j = 0; j < net->getLayers().size(); j++)
		{
			std::cout << "Layer #" << j + 1 << std::endl;
			for (size_t k = 0; k < net->getLayers().at(j).size(); k++)
			{
				std::cout << net->getLayers().at(j).at(k).getOutput() << " ";
			}
			std::cout << std::endl;
		}
		result = StringNormalizer::convertToString(input);
		std::cout << "Converted string: " << result << std::endl;
		std::cout << "Error " << i + 1 << ": " << net->getError() << std::endl;
		std::cout << std::endl;
		i++;
	}

	return 0;
}