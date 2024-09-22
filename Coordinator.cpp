#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include "Coordinator.h"

#include <condition_variable>
#include <mutex>
#include <queue>

#include "StatsDAO.h"
#include "Karatsuba.h"

// Task structure to store digit multiplication jobs
struct Task {
    std::string num1;
    char digit;
    int shift;
};

std::queue<std::unique_ptr<Task>> taskQueue;
std::mutex queueMutex, resultMutex;
std::condition_variable cv;
bool done = false;

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


void Coordinator::reset() {
    // Clear the task queue
    std::queue<std::unique_ptr<Task>> emptyQueue;
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        std::swap(taskQueue, emptyQueue);  // Swap with an empty queue to clear
    }

    // Reset the done flag
    done = false;
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
        reset();
        const std::string& inputNum1 = (num1.size() >= num2.size()) ? num1 : num2;
        const std::string& inputNum2 = (num1.size() >= num2.size()) ? num2 : num1;

        // Get the start time
        const auto start = std::chrono::high_resolution_clock::now();

        // Perform the multiplication
        const std::string result = performMultiplication(inputNum1, inputNum2);

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

        const auto kstart = std::chrono::high_resolution_clock::now();
        // Perform the multiplication
        const std::string kresult = Karatsuba::karatsuba(num1, num2);
        // Get the end time and calculate the duration
        const auto kend = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> kelapsed = kend - kstart;
        std::cout << "To compare with single-threaded Karatsuba algorithm: \n";
        std::cout << "Time taken: " << kelapsed.count() << " seconds\n";
        std::cout << "Result: " << kresult << std::endl;

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

// Worker function using class member variables
void Coordinator::worker(std::vector<int>& result) {
    while (true) {
        std::unique_ptr<Task> task;

        // Critical section to get a task from the queue
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            cv.wait(lock, [this] { return !taskQueue.empty() || done; });

            if (taskQueue.empty() && done) {
                break;  // Exit the worker if all tasks are done
            }

            task = std::move(taskQueue.front());
            taskQueue.pop();
        }

        // Multiply the given digit with the entire num1 string
        int carry = 0;
        int d = task->digit - '0';
        int n = task->num1.size();
        int resIndex = result.size() - 1 - task->shift;

        for (int i = n - 1; i >= 0; --i) {
            int prod = (task->num1[i] - '0') * d + carry;
            carry = prod / 10;
            prod %= 10;

            std::lock_guard<std::mutex> guard(resultMutex);
            result[resIndex--] += prod;

            // Handle overflow in the current position
            if (result[resIndex + 1] >= 10) {
                result[resIndex + 1] -= 10;
                result[resIndex]++;
            }
        }

        // Final carry handling
        if (carry > 0) {
            std::lock_guard<std::mutex> guard(resultMutex);
            result[resIndex] += carry;

            // Handle overflow after the final carry
            while (result[resIndex] >= 10) {
                result[resIndex] -= 10;
                result[--resIndex]++;
            }
        }
    }
}

// Master-worker multiplication using class member variables
std::string Coordinator::masterWorkerMultiplication(const std::string& num1, const std::string& num2) {

    int len1 = num1.size();
    int len2 = num2.size();
    std::vector<int> result(len1 + len2, 0);

    // Create worker threads
    int numThreads = std::thread::hardware_concurrency();  // Use only as many threads as digits in num2
    std::vector<std::thread> workers;
    for (int i = 0; i < numThreads; ++i) {
        workers.emplace_back(&Coordinator::worker, this, std::ref(result));
    }

    // Master thread splits tasks
    for (int i = len2 - 1; i >= 0; --i) {
        std::lock_guard<std::mutex> lock(queueMutex);
        taskQueue.push(std::make_unique<Task>(Task{num1, num2[i], len2 - 1 - i}));
    }

    // Notify all worker threads that tasks are available
    cv.notify_all();

    // Join all workers
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        done = true;
    }
    cv.notify_all();

    for (auto& worker : workers) {
        worker.join();
    }

    // Convert result to string, skipping leading zeros
    std::string resultStr;
    bool leadingZero = true;
    for (int digit : result) {
        if (digit == 0 && leadingZero) {
            continue;
        }
        leadingZero = false;
        resultStr += std::to_string(digit);
    }

    return resultStr.empty() ? "0" : resultStr;
}

std::string Coordinator::performMultiplication(const std::string& num1, const std::string& num2) {
    return masterWorkerMultiplication(num1, num2);
}

int main() {
    Coordinator coordinator;
    coordinator.start();
    return 0;
}


