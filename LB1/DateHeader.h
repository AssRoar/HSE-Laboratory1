//
// Created by Асрор Юлдашев on 01.05.2021.
//
#ifndef LABA1_DATEHEADER_H
#define LABA1_DATEHEADER_H
#include <string>
#include <cstdint>
#include <tuple>
#include <iostream>
class DateClass{
private:
    time_t unixdate;
    uint64_t filetime;
    uint16_t sec;
    uint16_t min;
    uint16_t hour;
    uint16_t day;
    uint16_t mon;
    uint32_t year;
public:
    static short a[12];
    DateClass();
    DateClass(DateClass const &new_value);
    DateClass(time_t unixtime);
    DateClass(uint64_t filetime);
    DateClass(uint16_t set_sec, uint16_t set_min,uint16_t set_hour, uint16_t set_day, uint16_t set_mon, uint32_t set_year);
    ~DateClass();

    time_t getUnix() const;
    uint64_t getFiletime() const;
    uint32_t getYear() const;
    uint16_t getMon() const;
    uint16_t getDay() const;
    uint16_t getHour() const;
    uint16_t getMin() const;
    uint16_t getSec() const;

    void setUnix(time_t value);
    void setFiletime(uint64_t value);
    void setYear(uint32_t value);
    void setMon(uint16_t value);
    void setDay(uint16_t value);
    void setHour(uint16_t value);
    void setMin(uint16_t value);
    void setSec(uint16_t value);

    const DateClass operator+(const DateClass &new_value);
    const DateClass operator-(const DateClass &new_value);
    const DateClass operator*(const DateClass &new_value);
    const DateClass operator/(const DateClass &new_value);
    const DateClass& operator=(const DateClass &new_value);
    friend std::ostream& operator<< (std::ostream &out, const DateClass& date);
    friend std::istream& operator>> (std::istream &in, DateClass& date);
    std::string getDayWeek() const;
};


#include "DateBody.cpp"


#endif //LABA1_DATEHEADER_H
