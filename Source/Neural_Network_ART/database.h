#pragma once

#include <winsqlite/winsqlite3.h>
#include <string>
#include <sstream>

class Database {
public:
	Database();
	~Database();
	void createTable(std::string& table, std::string& values); //TODO private
	void insert(std::string& table, std::string& values); //TODO Add update, select and delete
	void update(std::string& table, std::string& values, int rowid);
	void deleteRow(std::string& table, int rowid);
	std::string select(std::string& table, std::string& selection, int rowid);
	const char* DATABASE = "neuralNetwork.sqlite";
private:
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* errMsg;
	std::stringstream ss;
};