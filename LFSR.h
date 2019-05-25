#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdint>
#include <cctype>
#pragma once
using namespace std;
class LFSR_error: public std::invalid_argument
{
public:
    explicit LFSR_error (const std::string& what_arg):
        std::invalid_argument(what_arg) {}
    explicit LFSR_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};
class LFSR
{
private:
    uint64_t Seed=1;
public:
    LFSR(int64_t n);
    uint64_t LFSR_Galois (uint64_t branch);
    uint64_t Polynomial_Converter(string poli);
    string getValidPolynomial(const string poli);
    uint64_t getValidSeed(const int64_t seed);
};
