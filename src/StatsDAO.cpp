#include <iostream>
#include "DatabaseConnection.h"
#include "Stat.h"
#include "StatsDAO.h"

StatsDAO::StatsDAO() = default;

long long StatsDAO::addStat(Stat& stat) {
    sqlite3* db = DatabaseConnection::getInstance().getConnection();

    const std::string sql = "INSERT INTO stats (first_number, second_number, result, start_time, end_time, time_elapsed) VALUES (?, ?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }
    sqlite3_bind_text(stmt, 1, stat.getNumber1().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, stat.getNumber2().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, stat.getResult().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 4, stat.getTimeStarted());
    sqlite3_bind_int64(stmt, 5, stat.getTimeFinished());
    sqlite3_bind_double(stmt, 6, stat.getTimeElapsed());
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Failed to add stat: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);
    const long long new_id = sqlite3_last_insert_rowid(db);
    stat.setId(new_id);
    return new_id;
}

[[nodiscard]] std::vector<std::tuple<long long, long long, double> > StatsDAO::getLogs() {
    std::vector<std::tuple<long long, long long, double> > logs;
    sqlite3* db = DatabaseConnection::getInstance().getConnection();

    const std::string sql =
    "SELECT LENGTH(first_number), LENGTH(second_number), time_elapsed FROM stats LIMIT 20 ;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return {};
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const long long len_1 = sqlite3_column_int64(stmt, 0);
        const long long len_2 = sqlite3_column_int64(stmt, 1);
        const double elapsed = sqlite3_column_double(stmt, 2);
        logs.emplace_back(len_1, len_2, elapsed);
    }
    sqlite3_finalize(stmt);
    return logs;
}

[[nodiscard]] long long StatsDAO::statExists(std::string& number1, std::string& number2) {
    sqlite3* db = DatabaseConnection::getInstance().getConnection();
    const std::string sql =
        "SELECT id FROM stats "
        "WHERE (first_number = ? AND second_number = ?) OR (second_number = ? AND first_number = ?) ;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }
    sqlite3_bind_text(stmt, 1, number1.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, number2.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, number1.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, number2.c_str(), -1, SQLITE_TRANSIENT);
    long long id = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        id = sqlite3_column_int64(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return id;
}
[[nodiscard]] std::unique_ptr<Stat> StatsDAO::getStat(long long statId) {
    sqlite3* db = DatabaseConnection::getInstance().getConnection();

    const std::string sql = "SELECT first_number, second_number, result, start_time, end_time, time_elapsed FROM stats WHERE id = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return nullptr;
    }
    sqlite3_bind_int64(stmt, 1, statId);
    std::unique_ptr<Stat> stat = nullptr;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const std::string first_number = (const char*)(sqlite3_column_text(stmt, 0));
        const std::string second_number = (const char*)(sqlite3_column_text(stmt, 1));
        const std::string result = (const char*)(sqlite3_column_text(stmt, 2));
        const time_t start_time = sqlite3_column_int64(stmt, 3);
        const time_t end_time= sqlite3_column_int64(stmt, 4);
        const double time_elapsed = sqlite3_column_double(stmt, 5);
        stat = std::make_unique<Stat>(first_number, second_number, result, start_time, end_time, time_elapsed);
        stat->setId(statId);
    } else {
        std::cerr << "No stat found with id: " << statId << std::endl;
    }
    sqlite3_finalize(stmt);
    return stat;
}
