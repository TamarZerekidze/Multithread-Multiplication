#pragma once
#include <string>

class Karatsuba {
private:
    static std::string add(const std::string &a, const std::string &b);
    static std::string subtract(const std::string &a, const std::string &b);
    static std::string padWithZeros(const std::string& num, size_t n);
public:
    Karatsuba() = default;
    static std::string karatsuba(const std::string &num1, const std::string &num2);
};
