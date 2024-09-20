
#include "Stat.h"

Stat::Stat() = default;
Stat::Stat(std::string number_1, std::string number_2, std::string result, std::time_t timeStarted, std::time_t timeFinished, double timeElapsed)
    : number_1(std::move(number_1)), number_2(std::move(number_2)), result(std::move(result)), timeStarted(timeStarted), timeFinished(timeFinished), timeElapsed(timeElapsed){}

[[nondiscard]] long long Stat::getId() const {
    return this->id;
}

[[nondiscard]] std::string Stat::getNumber1() const {
    return this->number_1;
}

[[nondiscard]] std::string Stat::getNumber2() const   {
    return this->number_2;
}

[[nondiscard]] std::string Stat::getResult() const   {
    return this->result;
}

[[nondiscard]] std::time_t Stat::getTimeStarted() const   {
    return this->timeStarted;
}

[[nondiscard]] std::time_t Stat::getTimeFinished() const   {
    return this->timeFinished;
}

[[nondiscard]] double Stat::getTimeElapsed() const   {
    return this->timeElapsed;
}

void Stat::setId(const long long id) {
    this->id = id;
}

void Stat::setNumber1(const std::string &number1) {
    this->number_1 = number1;
}

void Stat::setNumber2(const std::string &number2) {
    this->number_2 = number2;
}

void Stat::setResult(const std::string &result) {
    this->result = result;
}

void Stat::setTimeStarted(const std::time_t timeStarted) {
    this->timeStarted = timeStarted;
}

void Stat::setTimeFinished(const std::time_t timeFinished) {
    this->timeFinished = timeFinished;
}

void Stat::setTimeElapsed(const double timeElapsed) {
    this->timeElapsed = timeElapsed;
}
