#pragma once
#include <string>
#include <ctime>

/**
 * @class Stat
 * @brief Stores details of a multiplication operation.
 *
 * This class holds information about two numbers involved in multiplication, the result,
 * and the timing details (start, finish, and elapsed time).
 *
 * Public Methods:
 * - Getters and setters for the numbers, result, start time, finish time, and elapsed time.
 * - getId(), setId(): Accessor and mutator for the unique ID of the Stat object.
 */

class Stat {
private:
    long long id = -1;
    std::string number_1;
    std::string number_2;
    std::string result;
    std::time_t timeStarted = 0;
    std::time_t timeFinished = 0;
    double timeElapsed = 0;

public:
    Stat();
    Stat(std::string number_1, std::string number_2, std::string result, std::time_t timeStarted, std::time_t timeFinished, double timeElapsed);

    [[nodiscard]] long long getId() const ;
    [[nodiscard]] std::string getNumber1() const ;
    [[nodiscard]] std::string getNumber2() const;
    [[nodiscard]] std::string getResult() const;
    [[nodiscard]] time_t getTimeStarted() const;
    [[nodiscard]] time_t getTimeFinished() const;
    [[nodiscard]] double getTimeElapsed() const;

    void setId(long long id);
    void setNumber1(const std::string &number1);
    void setNumber2(const std::string &number2);
    void setResult(const std::string &result);
    void setTimeStarted(std::time_t timeStarted);
    void setTimeFinished(std::time_t timeFinished);
    void setTimeElapsed(double timeElapsed);
};
