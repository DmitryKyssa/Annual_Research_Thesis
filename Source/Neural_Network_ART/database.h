#pragma once

#include <winsqlite/winsqlite3.h>
#include <string>
#include <sstream>
#include <vector>

class Database 
{
public:
	Database();
	~Database();
	void createTable(std::string& table, std::string& values); 
	void insert(std::string& table, std::string& values); 
	void update(std::string& table, std::string& values, int rowid);
	std::string select(std::string& table, std::string& selection, int rowid);
	std::vector<std::string> selectVector(std::string& table, std::string& selection); 
	bool tableExists(const std::string& tableName);
	bool isTableFull(const std::string& tableName, int maxRecords);
	const char* DATABASE = "neuralNetwork.sqlite";
private:
	sqlite3* db;
	sqlite3_stmt* stmt;
	char* errMsg;
	std::stringstream ss;
};