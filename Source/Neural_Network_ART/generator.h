#pragma once

#include <string>

class AlphanumericGenerator {
private:
    std::string alphanumericsymbols = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 !@#$%^&*()_+{}|:<>?";
public:
    std::string generateRandomString(int length);
};