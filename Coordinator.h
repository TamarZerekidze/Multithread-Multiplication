
#pragma once
#include <string>

class Coordinator {

public:
    Coordinator() = default;

    void start();
    void viewStats();
    void handleMultiplication();
    std::string performMultiplication(const std::string& num1, const std::string& num2);
};

