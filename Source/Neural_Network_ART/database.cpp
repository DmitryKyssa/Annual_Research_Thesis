#include "database.h"
#include <iostream>

Database::Database() 
{
	sqlite3_open(DATABASE, &db);
	stmt = NULL;
	errMsg = NULL;
	std::cout << "Database is opened!" << std::endl;
}

Database::~Database() 
{
	sqlite3_close(db);
	std::cout << "Database is closed!" << std::endl;
}

void Database::createTable(std::string& table, std::string& values) 
{
	ss << "CREATE TABLE IF NOT EXISTS " << table << " " << values;
	sqlite3_exec(db, ss.str().c_str(), NULL, 0, &errMsg);
	if (errMsg != NULL) 
	{
		std::cout << errMsg << std::endl;
	}
	ss.str("");
}

void Database::insert(std::string& table, std::string& values) 
{
	ss << "INSERT INTO " << table << " " << values;
	sqlite3_exec(db, ss.str().c_str(), NULL, 0, &errMsg);
	if (errMsg != NULL) 
	{
		std::cout << errMsg << std::endl;
	}
	ss.str("");
}

void Database::update(std::string& table, std::string& values, int rowid)
{
	ss << "UPDATE " << table << " SET " << values << " WHERE rowid = " << rowid << ";";
	sqlite3_exec(db, ss.str().c_str(), NULL, 0, &errMsg);
	if (errMsg != NULL) 
	{
		std::cout << errMsg << std::endl;
	}
	ss.str("");
}

bool Database::tableExists(const std::string& tableName)
{
	bool exists = false;
	std::string sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='" + tableName + "';";
	char* errMsg = nullptr;
	auto callback = [](void* data, int argc, char** argv, char** azColName) -> int 
		{
		*(bool*)data = true;
		return 0;
		};
	if (sqlite3_exec(db, sql.c_str(), callback, &exists, &errMsg) != SQLITE_OK) 
	{
		sqlite3_free(errMsg);
	}
	return exists;
}

bool Database::isTableFull(const std::string& tableName, int maxRecords) {
	bool isEmpty = true;
	std::string sql = "SELECT COUNT(*) FROM " + tableName + ";";
	char* errMsg = nullptr;
	auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
		if (argc == 1 && argv[0] && std::stoi(argv[0]) >= 100) 
		{
			*(bool*)data = false;
		}
		return 0;
		};
	if (sqlite3_exec(db, sql.c_str(), callback, &isEmpty, &errMsg) != SQLITE_OK) 
	{
		sqlite3_free(errMsg);
	}
	return isEmpty;
}

std::string Database::select(std::string& table, std::string& selection, int rowid)
{
	ss << "SELECT " << selection << " FROM " << table << " WHERE rowid = " << rowid << ";";
	sqlite3_prepare_v2(db, ss.str().c_str(), -1, &stmt, 0);
	if (errMsg != NULL) 
	{
		std::cout << errMsg << std::endl;
	}
	sqlite3_bind_int(stmt, rowid, rowid);

	sqlite3_step(stmt);

	std::string result = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

	ss.str("");
	return result;
}

std::vector<std::string> Database::selectVector(std::string& table, std::string& selection)
{
	std::vector<std::string> vector;
	ss << "SELECT " << selection << " FROM " << table << ";";

	if (sqlite3_prepare_v2(db, ss.str().c_str(), -1, &stmt, nullptr) == SQLITE_OK) 
	{
		while (sqlite3_step(stmt) == SQLITE_ROW) 
		{
			vector.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
		}
		sqlite3_finalize(stmt);
	}
	return vector;
}