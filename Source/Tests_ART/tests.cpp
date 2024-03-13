#include <string>
#include <random>
#include <iostream>
#include "../Neural_Network_ART/database.h"

const int TESTS_NUMBER = 100;
const int TEST_LENGHT = 100;

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

int main() {
    AlphanumericGenerator gen;
    Database db("test.sqlite");

    db.createTable("string", "(ID INT PRIMARY KEY NOT NULL, DATA TEXT NOT NULL);");

    for (int i = 0; i < 100; i++) {
        db.insert(i, gen());
    }

    return 0;
}

