//
// Created by Асрор Юлдашев on 14.05.2021.
//
#ifndef LABA1_LONGARITHMETIC_H
#define LABA1_LONGARITHMETIC_H
#include <string>
#include <cmath>
#include <tuple>


class LongArith{
private:
    std::string main_string;


public:
    LongArith();
    LongArith(std::string new_value);
    LongArith(LongArith const &new_value);
    ~LongArith();

    std::string getString();

    void setString(std::string new_value);

    LongArith operator+(const LongArith& new_value);
    LongArith operator-(const LongArith& new_value);
    LongArith operator*(const LongArith& new_value);
    LongArith operator/(const LongArith& new_value);
    LongArith operator%(const LongArith& new_value);
    bool operator>=(const LongArith& new_value);
    bool operator<=(const LongArith& new_value);
    bool operator>(const LongArith& new_value);
    bool operator<(const LongArith& new_value);
    bool operator==(const LongArith& new_value);
    friend std::ostream& operator<<(std::ostream &out, const LongArith& value);
    friend std::istream& operator>>(std::istream &in, LongArith& value);
    LongArith& operator=(const LongArith& new_value);
};

#include "LongArith.cpp"


#endif //LABA1_LONGARITHMETIC_H
