#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include "Coordinator.h"
#include "StatsDAO.h"
#include "Karatsuba.h"

void Coordinator::start() {
    std::string choice;
    while (true) {
        std::cout << "Welcome! Please choose an option (stats/multiply/exit): \n";

        std::getline(std::cin, choice);

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
    std::string stat = "Previously logged information: \n";
    std::vector<std::tuple<long long, long long, double> > logs = StatsDAO::getLogs();
    if(logs.empty()) {
        stat += "logs Empty!\n";
    } else {
        std::ostringstream leaderboard;
        leaderboard << "+-----------------+-----------------+-----------------+\n";
        leaderboard << "|  number 1 size  |  number 2 size  |  time elapsed   |\n";
        leaderboard << "+-----------------+-----------------+-----------------+\n";
        for (const auto&[fst, snd, third] : logs) {
            leaderboard << "| " << std::setw(15) << std::left << fst << " | "
                        << std::setw(15) << std::left << snd << " | "
                        << std::setw(15) << std::right << third << " |\n";
        }
        leaderboard << "+-----------------+-----------------+-----------------+\n";
        stat += leaderboard.str();
    }
    std::cout << stat;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

std::string timeToString(const std::time_t currTime) {
    const std::tm localTime = *std::localtime(&currTime);
    std::ostringstream timeStream;
    timeStream << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return timeStream.str();
}


void Coordinator::handleMultiplication() {
    std::string num1, num2;
    //system("cli");
    std::cout << "Enter first multiplicator: \n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::getline(std::cin, num1);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Enter second multiplicator: \n";
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::getline(std::cin, num2);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    const long long id = StatsDAO::statExists(num1, num2);
    if (id == -1) {
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
        const auto st = std::chrono::high_resolution_clock::to_time_t(start);
        const auto nd = std::chrono::high_resolution_clock::to_time_t(end);
        std::cout << "Start time: " << timeToString(st) << "\n";
        std::cout << "End time: " << timeToString(nd) << "\n";
        std::cout << "Time taken: " << elapsed.count() << " seconds\n";
        std::cout << "Result: " << result << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto newStat = std::make_unique<Stat>(num1, num2, result, st, nd, elapsed.count());
        StatsDAO::addStat(*newStat);
    } else {
        std::cout << "Result found in database...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        const auto stat = StatsDAO::getStat(id);
        std::cout << "Start time: " << timeToString(stat->getTimeStarted()) << "\n";
        std::cout << "End time: " << timeToString(stat->getTimeFinished()) << "\n";
        std::cout << "Time taken: " << stat->getTimeElapsed() << " seconds\n";
        std::cout << "Result: " << stat->getResult() << std::endl;
    }

    std::string returnToMenu;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Return to main menu? (yes/no): ";

    std::getline(std::cin, returnToMenu);

    if (returnToMenu != "yes") {
        std::cout << "Exiting...\n";
        exit(0);
    }
}

std::string Coordinator::performMultiplication(const std::string &num1, const std::string &num2) {
    //std::string res = std::to_string(std::stoi(num1) * std::stoi(num2));
    std::string res = Karatsuba::karatsuba(num1, num2);
    return res;
}

int main() {
    Coordinator coordinator;
    coordinator.start();
    return 0;
}


