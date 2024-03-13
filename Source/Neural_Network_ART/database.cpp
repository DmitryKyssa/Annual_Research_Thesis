#include "database.h"

Database::Database(const char* filename) {
	sqlite3_open(filename, &db);
	errMsg = NULL;
	std::cout << "Database is opened!" << std::endl;
}

Database::~Database() {
	sqlite3_close(db);
	std::cout << "Database is closed!" << std::endl;
}

void Database::createTable(std::string& table, std::string& values) {
	ss << "CREATE TABLE IF NOT EXISTS " << table << " " << values;
	sqlite3_exec(db, ss.str().c_str(), NULL, 0, &errMsg);
	if (errMsg != NULL) {
		std::cout << errMsg << std::endl;
	}
	ss.str("");
}

void Database::insert(std::string& table, std::string& values) {
	ss << "INSERT INTO " << table << " " << values;
	sqlite3_exec(db, ss.str().c_str(), NULL, 0, &errMsg);
	if (errMsg != NULL) {
		std::cout << errMsg << std::endl;
	}
	ss.str("");
}
