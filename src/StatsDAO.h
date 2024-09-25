#pragma once
#include <memory>
#include <vector>
#include "Stat.h"

/**
 * @class StatsDAO
 * @brief Data Access Object (DAO) for handling statistics of multiplication operations.
 *
 * This class provides an interface for interacting with a database to store and retrieve statistics
 * related to the multiplication of two large numbers. It tracks when the multiplication starts, ends,
 * and how long it takes to complete, storing these details in the database.
 *
 * - addStat(Stat& stat): Inserts a new multiplication statistic into the database.
 * - getLogs(): Retrieves logs containing the length of the first and second numbers and the elapsed time of the multiplication.
 * - statExists(const std::string& number1, const std::string& number2): Checks if a log for the multiplication of two numbers already exists.
 * - getStat(long long statId): Returns a Stat object corresponding to a given stat ID wrapped in a std::unique_ptr.
 */

class StatsDAO {
public:
    StatsDAO();
    static long long addStat(Stat& stat);
    [[nodiscard]] static std::vector<std::tuple<long long, long long, double> > getLogs();
    [[nodiscard]] static long long statExists(std::string& number1, std::string& number2);
    [[nodiscard]] static std::unique_ptr<Stat> getStat(long long statId);

};
