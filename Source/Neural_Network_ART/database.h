#pragma once

#include <winsqlite/winsqlite3.h>
#include <string>
#include <sstream>
#include <iostream>

class Database {
public:
	Database(const char* filename) {
		sqlite3_open(filename, &db);
	}

	~Database() {
		sqlite3_close(db);
	}

	void createTable(std::string table, std::string& values) {
		ss << "CREATE TABLE IF NOT EXISTS " << table << " " << values;
		sqlite3_exec(db, ss.str().c_str(), NULL, 0, &errMsg);
		std::cout << errMsg << std::endl;
	}

	void insert(std::string table, std::string& values) {
		ss << "INSERT INTO " << table << " " << values;
		sqlite3_exec(db, ss.str().c_str(), NULL, 0, &errMsg);
		std::cout << errMsg << std::endl;
	}

private:
	sqlite3* db;
	char* errMsg;
	std::stringstream ss;
};