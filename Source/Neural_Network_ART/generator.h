#pragma once

#include <string>

class AlphanumericGenerator {
private:
    std::string alphanumeric = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
public:
    std::string generateRandomString(int length);
};