#pragma once

#include <winsqlite/winsqlite3.h>
#include <string>
#include <sstream>
#include <iostream>

class Database {
public:
	Database(const char* filename);

	~Database();

	void createTable(std::string& table, std::string& values);

	void insert(std::string& table, std::string& values);

private:
	sqlite3* db;
	char* errMsg;
	std::stringstream ss;
};