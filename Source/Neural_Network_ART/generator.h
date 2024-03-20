#pragma once

#include <string>
#include <random>
#include <iostream>

class AlphanumericGenerator {
public:
	std::string operator()() {
		std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

		std::random_device rd;
		std::mt19937 generator(rd());

		std::shuffle(str.begin(), str.end(), generator);

		return str.substr(0, 100);
	}
};