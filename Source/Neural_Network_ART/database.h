#pragma once

#include <winsqlite/winsqlite3.h>
#include <string>

class Database {
public:
	Database(const char* filename) {
		sqlite3_open(filename, &db);
	}

	~Database() {
		sqlite3_close(db);
	}

	void createTable(const char* table, std::string& values) {
		char* errMsg;
		std::stringstream sql;
		sql = "CREATE TABLE IF NOT EXISTS " << table << " " << values;
		sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
	}

	void insert(int id, const std::string& data) {
		std::string sql = "INSERT INTO tests (ID,DATA) "  \
			"VALUES (" + std::to_string(id) + ", '" + data + "'); ";
		char* errMsg;
		sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
	}

private:
	sqlite3* db;
};