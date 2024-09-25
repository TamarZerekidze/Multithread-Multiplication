#pragma once
#include <string>

/**
 * @class Karatsuba
 * @brief Implements Karatsuba's algorithm for efficient multiplication of large numbers.
 *
 * This class provides static methods for performing the Karatsuba multiplication algorithm,
 * along with helper functions for adding, subtracting, and padding numbers.
 *
 * Public Methods:
 * - karatsuba(): Performs Karatsuba multiplication on two large numbers represented as strings.
 *
 * Private Methods:
 * - add(): Adds two large numbers represented as strings.
 * - subtract(): Subtracts one large number from another, both represented as strings.
 * - padWithZeros(): Pads a number with leading zeros to ensure that both numbers being multiplied
 *   have equal length, which is required for Karatsuba's algorithm.
 */

class Karatsuba {
private:
    static std::string add(const std::string &a, const std::string &b);
    static std::string subtract(const std::string &a, const std::string &b);
    static std::string padWithZeros(const std::string& num, size_t n);
public:
    Karatsuba() = default;
    static std::string karatsuba(const std::string &num1, const std::string &num2);
};
