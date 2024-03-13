#pragma once

#include <winsqlite/winsqlite3.h>
#include <string>
#include <sstream>

class Database {
public:
	Database(const char* filename);

	~Database();

	void createTable(std::string& table, std::string& values);

	void insert(std::string& table, std::string& values);

	std::string getTestByID(std::string& table, std::string& selection, int rowid);

private:
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* errMsg;
	std::stringstream ss;
};