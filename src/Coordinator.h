
#pragma once
#include <condition_variable>
#include <queue>
#include <string>

/**
 * @struct Task
 * @brief Represents a multiplication job for a single digit.
 *
 * This structure stores the details of a digit multiplication task, including:
 * - num1: The large number to be multiplied.
 * - digit: A single digit of the second number.
 * - shift: The number of zeros to append (i.e., positional shift) based on the digit's place.
 */

// Task structure to store digit multiplication jobs
struct Task {
    const std::string& num1;
    char digit;
    int shift;
};

/**
 * @class Coordinator
 * @brief Manages the task queue for digit multiplication and coordinates worker threads.
 *
 * This class orchestrates the task of multiplying large numbers using multiple worker threads.
 * It handles the task queue, synchronization mechanisms, and coordination between the master
 * and worker threads to perform the multiplication efficiently.
 *
 * Public Methods:
 * - start(): Starts the coordinator, handling requests like multiplication or viewing stats.
 * - viewStats(): Displays current statistics such as multiplicator and operation times.
 * - reset(): Resets the coordinator state and clears the task queue.
 * - handleMultiplication(): Handles different operations like viewing stats or starting a multiplication.
 * - worker(): Function executed by worker threads to process multiplication tasks from the task queue.
 * - masterWorkerMultiplication(): Oversees the division of work between master and worker threads for multiplying two large numbers.
 * - performMultiplication(): Initiates the entire multiplication process using multiple workers.
 *
 * Private Members:
 * - taskQueue: A queue of tasks that the worker threads will process.
 * - queueMutex, resultMutex: Mutexes to protect shared data (task queue and results).
 * - cv: Condition variable to signal worker threads when new tasks are available.
 * - done: A flag indicating if the task processing is complete.
 */

class Coordinator {

private:
    std::queue<std::unique_ptr<Task>> taskQueue;
    std::mutex queueMutex, resultMutex;
    std::condition_variable cv;
    bool done = false;

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

