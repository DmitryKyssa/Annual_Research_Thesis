#include "database.h"
#include <iostream>

Database::Database(const char* filename) {
	sqlite3_open(filename, &db);
	stmt = NULL;
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

std::string Database::getTestByID(std::string& table, std::string& selection, int rowid)
{
	ss << "SELECT " << selection << " FROM " << table << " WHERE rowid = " << rowid << ";";
	sqlite3_prepare_v2(db, ss.str().c_str(), -1, &stmt, 0);
	if (errMsg != NULL) {
		std::cout << errMsg << std::endl;
	}
	sqlite3_bind_int(stmt, rowid, rowid); 

	sqlite3_step(stmt);

	std::string result = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
	std::cout << result << std::endl;

	ss.str("");
	return result;
}
