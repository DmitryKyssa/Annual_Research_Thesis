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

	std::vector<unsigned int> topology = { 62, 300, 62 };
	Net* net = new Net(topology);

	std::string test = db.getTestByID(tableForTests, valueString, 1);
	std::vector<double> input = StringNormalizer::normalize(test);
	std::vector<double> target = StringNormalizer::findTarget(input, 'o');
	std::cout << target << std::endl;
	net->forwardPropagation(input);
	net->backPropagation(target);

	std::cout << net->getError() << std::endl;

	for (size_t i = 0; i < net->getLayers().size(); i++)
	{
		std::cout << "Layer #" << i + 1 << std::endl;
		for (size_t j = 0; j < net->getLayers().at(i).size(); j++)
		{
			std::cout << net->getLayers().at(i).at(j).getOutput() << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}