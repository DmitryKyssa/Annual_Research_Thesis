#include "generator.h"
#include <random>

std::string AlphanumericGenerator::generateRandomString(int length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, alphanumeric.size() - 1);

    std::string result;
    for (int i = 0; i < length; i++) {
        result += alphanumeric[dis(gen)];
    }
    return result;
}
