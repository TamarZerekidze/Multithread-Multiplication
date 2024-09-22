#pragma once
#include <memory>
#include <vector>

#include "Stat.h"

class StatsDAO {
public:
    StatsDAO();
    static long long addStat(Stat& stat);
    [[nodiscard]] static std::vector<std::tuple<long long, long long, double> > getLogs();
    [[nodiscard]] static long long statExists(std::string& number1, std::string& number2);
    [[nodiscard]] static std::unique_ptr<Stat> getStat(long long statId);

};
