#include "database.h"
#include <iostream>

Database::Database() {
	sqlite3_open(DATABASE, &db);
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

void Database::update(std::string& table, std::string& values, int rowid)
{
	ss << "UPDATE " << table << " SET " << values << " WHERE rowid = " << rowid << ";";
	sqlite3_exec(db, ss.str().c_str(), NULL, 0, &errMsg);
	if (errMsg != NULL) {
		std::cout << errMsg << std::endl;
	}
	ss.str("");
}

void Database::deleteRow(std::string& table, int rowid)
{
	ss << "DELETE FROM " << table << " WHERE rowid = " << rowid << ";";
	sqlite3_exec(db, ss.str().c_str(), NULL, 0, &errMsg);
	if (errMsg != NULL) {
		std::cout << errMsg << std::endl;
	}
	ss.str("");
}

std::string Database::select(std::string& table, std::string& selection, int rowid)
{
	ss << "SELECT " << selection << " FROM " << table << " WHERE rowid = " << rowid << ";";
	sqlite3_prepare_v2(db, ss.str().c_str(), -1, &stmt, 0);
	if (errMsg != NULL) {
		std::cout << errMsg << std::endl;
	}
	sqlite3_bind_int(stmt, rowid, rowid);

	sqlite3_step(stmt);

	std::string result = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

	ss.str("");
	return result;
}
