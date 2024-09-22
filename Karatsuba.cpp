#include <iostream>
#include <chrono>
#include <bits/ranges_algo.h>
#include "Karatsuba.h"


// Function to add two large numbers represented as strings
std::string Karatsuba::add(const std::string &a, const std::string &b) {
    std::string result;
    int carry = 0;

    auto itA = a.rbegin();
    auto itB = b.rbegin();

    while (itA != a.rend() || itB != b.rend() || carry) {
        int sum = carry;
        if (itA != a.rend()) {
            sum += *itA - '0';
            ++itA;
        }
        if (itB != b.rend()) {
            sum += *itB - '0';
            ++itB;
        }
        result.push_back(sum % 10 + '0');
        carry = sum / 10;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

// Function to subtract two large numbers represented as strings
std::string Karatsuba::subtract(const std::string &a, const std::string &b) {
    std::string result;
    int carry = 0;

    auto itA = a.rbegin();
    auto itB = b.rbegin();

    while (itA != a.rend()) {
        int diff = *itA - '0' - carry;
        if (itB != b.rend()) {
            diff -= *itB - '0';
            ++itB;
        }
        if (diff < 0) {
            diff += 10;
            carry = 1;
        } else {
            carry = 0;
        }
        result.push_back(diff + '0');
        ++itA;
    }

    // Remove leading zeros
    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }

    std::reverse(result.begin(), result.end());
    return result.empty() ? "0" : result;
}

// Function to pad a string with leading zeros to make its length equal to `n`
std::string Karatsuba::padWithZeros(const std::string& num, size_t n) {
    if (num.size() < n) {
        return std::string(n - num.size(), '0') + num;
    }
    return num;
}

// Karatsuba multiplication function
std::string Karatsuba::karatsuba(const std::string &num1, const std::string &num2) {
    // Base case for recursion
    if (num1.size() == 1 || num2.size() == 1) {
        return std::to_string(std::stoi(num1) * std::stoi(num2));
    }

    // Make the numbers the same length by padding with leading zeros
    size_t maxLength = std::max(num1.size(), num2.size());
    std::string num1Padded = padWithZeros(num1, maxLength);
    std::string num2Padded = padWithZeros(num2, maxLength);

    size_t n = num1Padded.size();
    size_t half = n / 2;

    // Split the numbers into two halves
    std::string a = num1Padded.substr(0, n - half);
    std::string b = num1Padded.substr(n - half);
    std::string c = num2Padded.substr(0, n - half);
    std::string d = num2Padded.substr(n - half);

    // 3 recursive calls
    std::string ac = karatsuba(a, c);
    std::string bd = karatsuba(b, d);
    std::string ab_cd = karatsuba(add(a, b), add(c, d));
    std::string ad_bc = subtract(subtract(ab_cd, ac), bd);

    // Shift results to the left by appending zeros
    std::string ac_shifted = ac + std::string(2 * half, '0');
    std::string ad_bc_shifted = ad_bc + std::string(half, '0');

    // Combine the results
    std::string res = add(ac_shifted, add(ad_bc_shifted, bd));

    // Remove any leading zeros from the result
    while (res.size() > 1 && res[0] == '0') {
        res.erase(res.begin());
    }

    return res;
}
