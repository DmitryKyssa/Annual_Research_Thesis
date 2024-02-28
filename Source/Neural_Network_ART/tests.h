#pragma once

#include <iostream>
#include <string>
#include <vector>

void generateTests() 
{
	std::string alphabetical = "qwertyuiopasdfghjklzxcvbnm";
	std::string test;
	std::vector<std::string> tests;
	int symbol;
	while (tests.size() < 100) {
		for (size_t i = 0; i < 100; i++)
		{
			symbol = rand() % alphabetical.length();
			test += alphabetical[symbol];
		}

		tests.push_back(test);
		test = "";
	}

	for (size_t i = 0; i < tests.size(); i++)
	{
		std::cout << i + 1 << ": " << tests.at(i) << std::endl;
	}
}