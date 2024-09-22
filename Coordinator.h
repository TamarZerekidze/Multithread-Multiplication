
#pragma once
#include <condition_variable>
#include <queue>
#include <string>

class Coordinator {

public:
    Coordinator() = default;

    void start();
    void viewStats();
    void reset();
    void handleMultiplication();
    void worker(std::vector<int>& result);
    std::string masterWorkerMultiplication(const std::string& num1, const std::string& num2);
    std::string performMultiplication(const std::string& num1, const std::string& num2);
};

