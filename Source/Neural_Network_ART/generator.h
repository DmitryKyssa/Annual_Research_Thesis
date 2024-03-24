#pragma once

#include <string>
#include <random>
#include <iostream>

class AlphanumericGenerator {
public:
    std::string generateRandomString(int length, const std::string& alphabet) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, alphabet.size() - 1);

        std::string result;
        for (int i = 0; i < length; i++) {
            result += alphabet[dis(gen)];
        }
        return result;
    }
};