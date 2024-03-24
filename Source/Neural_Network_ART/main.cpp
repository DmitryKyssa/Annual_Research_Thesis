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
	std::string alphanumeric = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

	std::string query = "(ID INT PRIMARY KEY NOT NULL, STRING TEXT NOT NULL);";
	db.createTable(tableForTests, query);
	tableForTests += " (ID,STRING) ";
	query = "";
	for (int i = 0; i < TESTS_NUMBER; i++) {
		int stringLength = rand() % 1000 + 9000;
		query = "VALUES (" + std::to_string(i + 1) + ", '" + gen.generateRandomString(stringLength, alphanumeric) + "'); ";
		db.insert(tableForTests, query);
		std::cout << "String added! " << i << std::endl;
	}

	//std::string test = db.getTestByID(tableForTests, valueString, 1);
	//std::string str = "Hello world";
	//char search = str[0];
	//std::string substr = str.substr(1, 11);

	//std::vector<unsigned int> topology = { (unsigned int)str.length(), 20, (unsigned int)str.length() };
	//Net* net = new Net(topology);

	//std::vector<double> input = StringNormalizer::normalize(str);
	////std::vector<double> target = StringNormalizer::findOneChar(input, search, net->getLayers().back().size());
	//std::vector<double> target = StringNormalizer::findSubstring(str, substr, net->getLayers().back().size());
	//std::cout << "Targets: " << target << std::endl;

	//size_t i = 0;
	//std::string result = "";
	//while (result.find(substr) == -1)
	//	//while (result.find(search) == -1)
	//	//while(i < 20)
	//{
	//	net->forwardPropagation(input);
	//	net->backPropagation(target);
	//	for (size_t j = 2; j < net->getLayers().size(); j++)
	//	{
	//		std::cout << "Layer #" << j + 1 << std::endl;
	//		for (size_t k = 0; k < net->getLayers().at(j).size(); k++)
	//		{
	//			std::cout << net->getLayers().at(j).at(k).getOutput() << " ";
	//		}
	//		std::cout << std::endl;
	//	}
	//	std::vector<double> outputNeurons = net->getResults();
	//	result = StringNormalizer::convertToString(outputNeurons);
	//	std::cout << "Converted string: " << result << std::endl;
	//	std::cout << "Error " << i + 1 << ": " << net->getError() << std::endl;
	//	std::cout << std::endl;
	//	i++;
	//}

	return 0;
}