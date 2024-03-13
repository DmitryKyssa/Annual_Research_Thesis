#include "database.h"
#include "Constants.h"
#include <string>
#include <random>
#include <iostream>

class AlphanumericGenerator {
public:
	std::string operator()() {
		std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

		std::random_device rd;
		std::mt19937 generator(rd());

		std::shuffle(str.begin(), str.end(), generator);

		return str.substr(0, TEST_LENGHT);
	}
};

int main() {
	AlphanumericGenerator gen;
	Database db(DATABASE);
	std::string tableForTests = "strings";
	std::string query = "(ID INT PRIMARY KEY NOT NULL, STRING TEXT NOT NULL);";

	db.createTable(tableForTests, query);

	tableForTests += " (ID,DATA) ";
	query = "";
	for (int i = 0; i < TESTS_NUMBER; i++) {
		query = "VALUES (" + std::to_string(i + 1) + ", '" + gen() + "'); ";
		db.insert(tableForTests, query);
		std::cout << "String added!" << std::endl;
	}

	return 0;
}