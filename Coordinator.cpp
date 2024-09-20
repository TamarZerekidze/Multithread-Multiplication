#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include "Coordinator.h"

void Coordinator::start() {
    std::string choice;
    while (true) {
        std::cout << "Welcome! Please choose an option (stats/multiply/exit): \n";
        std::cin >> choice;

        if (choice.find("stats") != std::string::npos) {
            viewStats();
        } else if (choice.find("multiply") != std::string::npos) {
            handleMultiplication();
        } else {
            std::cout << "Exiting...\n";
            break;
        }
    }
}

void Coordinator::viewStats() {

// I will retrieve this from database
}

std::string timeToString(const std::time_t currTime) {
    const std::tm localTime = *std::localtime(&currTime);
    std::ostringstream timeStream;
    timeStream << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return timeStream.str();
}

void Coordinator::handleMultiplication() {
    std::string num1, num2;
    system("cli");
    std::cout << "Enter first multiplicator: ";
    std::getline(std::cin, num1);
    std::cout << "Enter second multiplicator: ";
    std::getline(std::cin, num2);

    std::cout << "Performing multiplication...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Get the start time
    const auto start = std::chrono::high_resolution_clock::now();

    // Perform the multiplication
    const std::string result = performMultiplication(num1, num2);

    // Get the end time and calculate the duration
    const auto end = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double> elapsed = end - start;

    std::cout << "Multiplication completed!\n";
    std::cout << "Start time: " << timeToString(std::chrono::high_resolution_clock::to_time_t(start)) << "\n";
    std::cout << "End time: " << timeToString(std::chrono::high_resolution_clock::to_time_t(end)) << "\n";
    std::cout << "Time taken: " << elapsed.count() << " seconds\n";

    //store this new stat in database

    std::string returnToMenu;
    std::cout << "Return to main menu? (yes/no): ";
    std::cin >> returnToMenu;

    if (returnToMenu != "yes") {
        std::cout << "Exiting...\n";
        exit(0);
    }
}

std::string Coordinator::performMultiplication(const std::string &num1, const std::string &num2) {
    std::string res;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return res;

}

int main() {
    Coordinator coordinator;
    coordinator.start();
    return 0;
}


