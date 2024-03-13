//#pragma once
//
//#include <iostream>
//#include <string>
//#include <vector>
//
//bool ifRowExistsInTable(std::stringstream& stream, int index, sqlite3* database, sqlite3_stmt*& stmt)
//{
//	stream.clear();
//	stream << "SELECT EXISTS(SELECT 1 FROM tests WHERE Id = " << index << " LIMIT 1);";
//	int exec = sqlite3_prepare_v3(database, stream.str().c_str(), (int)stream.str().length(), 0, &stmt, 0);
//	std::cout << "Check if row exists: " << exec << " " << index << std::endl;
//	sqlite3_step(stmt);
//	sqlite3_finalize(stmt);
//	if (exec == 0) {
//		return false;
//	}
//	else return true;
//}
//
//void generateTests()
//{
//	sqlite3* database;
//	sqlite3_stmt* stmt;
//
//	int exec = sqlite3_open("neural_network.sqlite", &database);
//
//	std::cout << "Opening: " << exec << std::endl;
//
//	std::stringstream query;
//	query << "CREATE TABLE IF NOT EXISTS tests ("
//		"Id TEXT PRIMARY KEY, "
//		"String TEXT);";
//
//	exec = sqlite3_prepare_v3(database, query.str().c_str(), (int)query.str().length(), 0, &stmt, 0);
//	exec = sqlite3_step(stmt);
//	std::cout << exec << " " << std::endl;
//	sqlite3_finalize(stmt);
//
//	std::string alphabetical = "qwertyuiopasdfghjklzxcvbnm";
//	std::string test;
//	query.clear();
//	int index;
//	int i;
//	for (i = 0; i < 10; i++) {
//		for (int j = 0; j < 100; j++) {
//			index = rand() % alphabetical.length();
//			test += alphabetical[index];
//		}
//
//		if (!ifRowExistsInTable(query, i, database, stmt)) {
//			query.clear();
//			query << "INSERT INTO tests (Id, String) VALUES ('" << (i + 1) << "','" << test << "');";
//
//			/*exec = sqlite3_prepare_v3(database, query.str().c_str(), (int)query.str().length(), -1, &stmt, NULL);
//			if (exec != SQLITE_OK) {
//				std::cout << "Failed to execute query: " << sqlite3_errmsg(database) << std::endl;
//			}
//			sqlite3_bind_text(stmt, 1, std::to_string(i).c_str(), -1, SQLITE_STATIC);
//			sqlite3_bind_text(stmt, 2, test.c_str(), -1, SQLITE_STATIC);
//			exec = sqlite3_step(stmt);
//			if (exec != SQLITE_DONE) {
//				std::cout << "Failed to execute query: " << sqlite3_errmsg(database) << std::endl;
//			}
//			sqlite3_finalize(stmt);*/
//			exec = sqlite3_prepare_v3(database, query.str().c_str(), (int)query.str().length(), 0, &stmt, 0);
//			exec = sqlite3_step(stmt);
//			std::cout << "exec: " << exec << std::endl;
//			std::cout << sqlite3_errmsg(database) << std::endl;
//			sqlite3_finalize(stmt);
//			test = "";
//			std::cout << "inserted" << std::endl;
//		}
//		else {
//			query.clear();
//			query << "UPDATE strings Id = '" << i << "' = '" << i << "'," << "String = '" << test << "' WHERE Id = '" << i << "';";
//			exec = sqlite3_prepare_v3(database, query.str().c_str(), (int)query.str().length(), -1, &stmt, NULL);
//			if (exec != SQLITE_OK) {
//				std::cout << "Failed to execute query: " << sqlite3_errmsg(database) << std::endl;
//			}
//			sqlite3_bind_text(stmt, 1, std::to_string(i).c_str(), -1, SQLITE_STATIC);
//			sqlite3_bind_text(stmt, 2, test.c_str(), -1, SQLITE_STATIC);
//			exec = sqlite3_step(stmt);
//			if (exec != SQLITE_DONE) {
//				std::cout << "Failed to execute query: " << sqlite3_errmsg(database) << std::endl;
//			}
//			sqlite3_finalize(stmt);
//			std::cout << "updated" << std::endl;
//		}
//	}
//	exec = sqlite3_close(database);
//	std::cout << "Close database: " << exec << std::endl;
//}