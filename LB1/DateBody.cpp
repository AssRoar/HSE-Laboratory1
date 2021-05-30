//
// Created by Асрор Юлдашев on 01.05.2021.
//
#include <vector>
// 31 536 000 нвг
// 31 622 400 вг
short DateClass::a[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

std::tuple <uint32_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t> unix_to_normal_form(time_t time_n){
    uint32_t year_n;
    uint16_t mon_n, day_n, hour_n, min_n, sec_n;

    year_n = time_n/31556929 + 1970;
    uint64_t k = time_n;
    k = k - (year_n - 1969)/4*86400 + (year_n-1901)/100*86400 - (year_n-1601)/400*86400;
    while (k > 31536000) k -= 31536000;
    uint8_t c = 0;
    if (((year_n%4==0 && year_n%100!=0) || year_n%400==0)) DateClass::a[1] = 29;
    else DateClass::a[1] = 28;

    while (c<12){
        if (k>DateClass::a[c]*86400) k -= DateClass::a[c]*86400;
        else {
            mon_n = c + 1;
            break;
        }
        ++c;
    }
    day_n = k / 86400 + 1;
    k = k % 86400;
    hour_n = k / 3600;
    k = k % 3600;
    min_n = k / 60;
    k =  k % 60;
    sec_n = k;
    return std::make_tuple(year_n, mon_n, day_n, hour_n, min_n, sec_n);
}
time_t to_unix_form(uint32_t year, uint16_t mon, uint16_t day, uint16_t hour, uint16_t min, uint16_t sec){
    time_t unixdate;
    if (((year%4==0 && year%100!=0) || year%400==0)) DateClass::a[1] = 29;
    else DateClass::a[1] = 28;
    unixdate = sec + 60*min + hour*3600 + (day-1)*86400;
    uint8_t m = 0;
    while (m < mon - 1){
        unixdate += DateClass::a[m]*86400;
        ++m;
    }
    uint32_t y = year - (year - 1969)/4 + (year-1901)/100 - (year-1601)/400;
    y -= 1970;
    unixdate += y * 31536000;
    unixdate += ((year - 1969)/4 - (year-1901)/100 + (year-1601)/400)*31622400;
    return unixdate;
}
std::tuple <uint32_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t> file_to_normal_form(uint64_t filetime){
    uint32_t year;
    uint16_t mon, day, hour, min, sec;
    uint64_t time = filetime / 10000000;
    year = time/31556929 + 1601;
    uint64_t k = time;
    k = k - (year - 1969)/4*86400 + (year-1901)/100*86400 - (year-1601)/400*86400;
    while (k > 31536000) k -= 31536000;
    uint8_t c = 0;
    if (((year%4==0 && year%100!=0) || year%400==0)) DateClass::a[1] = 29;
    else DateClass::a[1] = 28;

    while (c<12){
        if (k>DateClass::a[c]*86400) k -= DateClass::a[c]*86400;
        else {
            mon = c + 1;
            break;
        }
        ++c;
    }
    day = k / 86400 + 1;
    k = k % 86400;
    hour = k / 3600;
    k = k % 3600;
    min = k / 60;
    k =  k % 60;
    sec = k;
    return std::make_tuple(year, mon, day, hour, min, sec);
}
uint64_t to_file_form(uint32_t year, uint16_t mon, uint16_t day, uint16_t hour, uint16_t min, uint16_t sec){
    uint64_t filetime;
    if (((year%4==0 && year%100!=0) || year%400==0)) DateClass::a[1] = 29;
    else DateClass::a[1] = 28;
    filetime = sec + 60*min + hour*3600 + (day-1)*86400;
    uint8_t m = 0;
    while (m < mon - 1){
        filetime += DateClass::a[m]*86400;
        ++m;
    }
    uint32_t y = year - (year - 1601)/4 + (year-1601)/100 - (year-1601)/400;
    y -= 1601;
    filetime += y * 31536000;
    filetime += ((year - 1601)/4 - (year-1601)/100 + (year-1601)/400)*31622400;
    return filetime * 10000000;
}


DateClass::DateClass(){
    sec = 0;
    min = 0;
    hour = 0;
    day = 1;
    mon = 1;
    year = 1970;
    unixdate = 0;
    filetime = to_file_form(year, mon, day, hour, min, sec);
};
DateClass::DateClass(DateClass const &new_value) {
    year = new_value.year;
    mon = new_value.mon;
    day = new_value.day;
    hour = new_value.hour;
    min = new_value.mon;
    sec = new_value.sec;
    unixdate = new_value.unixdate;
    filetime = new_value.filetime;
};
DateClass::DateClass(time_t time){
    try{
        if (time < 0) throw "Invalid value of date in Unix form!";
        unixdate = time;
        std::tie(year, mon, day, hour, min, sec) = unix_to_normal_form(time);
        filetime = to_file_form(year, mon, day, hour, min, sec);
    }
    catch(const char* error){
        std::cerr << error << " (" << time << ")" << std::endl;
        std::cout << "Try again!" << std::endl;
        sec = 0;
        min = 0;
        hour = 0;
        day = 1;
        mon = 1;
        year = 1970;
        unixdate = 0;
        filetime = to_file_form(year, mon, day, hour, min, sec);
        return;
    }
};
DateClass::DateClass(uint64_t ftime) {
    try{
        if (ftime < 30545390080000000) throw "Invalid value of date in Unix form!";
        std::tie(year, mon, day, hour, min, sec) = file_to_normal_form(ftime);
        unixdate = to_unix_form(year, mon, day, hour, min, sec);
        filetime = ftime;
    }
    catch(const char* error){
        std::cerr << error << " (" << time << ")" << std::endl;
        std::cout << "Try again!" << std::endl;
        sec = 0;
        min = 0;
        hour = 0;
        day = 1;
        mon = 1;
        year = 1970;
        unixdate = 0;
        filetime = 30545390080000000;
        return;
    }
}
DateClass::DateClass(uint16_t set_sec, uint16_t set_min, uint16_t set_hour, uint16_t set_day, uint16_t set_mon, uint32_t set_year) {
    try {
        if (!(set_sec>=0 && set_sec<=59)) throw "seconds";
        if (!(set_min>=0 && set_min<=59)) throw "minutes";
        if (!(set_hour>=0 && set_hour<=23)) throw "hours";
        if (!(set_mon>=1 && set_mon<=12)) throw "months";
        if (!(set_year>1969)) throw "years";
        if (((set_year%4==0 && set_year%100!=0) || set_year%400==0)) a[1] = 29;
        else a[1] = 28;
        if (!(set_day<=a[set_mon-1] && set_day>=1)) throw "days";
        sec = set_sec;
        min = set_min;
        hour = set_hour;
        day = set_day;
        mon = set_mon;
        year = set_year;
        unixdate = to_unix_form(year, mon, day, hour, min, sec);
        filetime = to_file_form(year, mon, day, hour, min, sec);
    }
    catch (const char* error) {
        std::cerr << "Oops! You have an error in the parameter of " << error << std::endl;
        std::cout << "The default parameters are set." << std::endl;
        sec = 0;
        min = 0;
        hour = 0;
        day = 1;
        mon = 1;
        year = 1970;
        unixdate = 0;
        filetime = to_file_form(year, mon, day, hour, min, sec);
        return;
    }
};
DateClass::~DateClass(){

}



time_t DateClass::getUnix() const {
    return unixdate;
}
uint64_t DateClass::getFiletime() const {
    return filetime;
}
uint32_t DateClass::getYear() const {
    return year;
}
uint16_t DateClass::getMon() const {
    return mon;
}
uint16_t DateClass::getDay() const {
    return day;
}
uint16_t DateClass::getHour() const {
    return hour;
}
uint16_t DateClass::getMin() const {
    return min;
}
uint16_t DateClass::getSec() const {
    return sec;
}

void DateClass::setUnix(time_t value) {
    unixdate = value;
    std::tie(year, mon, day, hour, min, sec) = unix_to_normal_form(value);
    filetime = to_file_form(year, mon, day, hour, min, sec);
}
void DateClass::setFiletime(uint64_t value) {
    filetime = value;
    std::tie(year, mon, day, hour, min, sec) = file_to_normal_form(value);
    unixdate = to_unix_form(year, mon, day, hour, min, sec);
}
void DateClass::setYear(uint32_t value) {
    year = value;
    unixdate = to_unix_form(year, mon, day, hour, min, sec);
    filetime = to_file_form(year, mon, day, hour, min, sec);
}
void DateClass::setMon(uint16_t value) {
    mon = value;
    unixdate = to_unix_form(year, mon, day, hour, min, sec);
    filetime = to_file_form(year, mon, day, hour, min, sec);
}
void DateClass::setDay(uint16_t value) {
    day = value;
    unixdate = to_unix_form(year, mon, day, hour, min, sec);
    filetime = to_file_form(year, mon, day, hour, min, sec);
}
void DateClass::setHour(uint16_t value) {
    hour = value;
    unixdate = to_unix_form(year, mon, day, hour, min, sec);
    filetime = to_file_form(year, mon, day, hour, min, sec);
}
void DateClass::setMin(uint16_t value) {
    min = value;
    unixdate = to_unix_form(year, mon, day, hour, min, sec);
    filetime = to_file_form(year, mon, day, hour, min, sec);
}
void DateClass::setSec(uint16_t value) {
    sec = value;
    unixdate = to_unix_form(year, mon, day, hour, min, sec);
    filetime = to_file_form(year, mon, day, hour, min, sec);
}

const DateClass DateClass::operator+(const DateClass &new_value){
    DateClass result(unixdate + new_value.unixdate);
    return result;
}
const DateClass DateClass::operator-(const DateClass &new_value) {
    try{
        if (unixdate < new_value.unixdate) throw "Invalid operation (-) for this operands! (first value is lower than second)";
    }
    catch (const char* error){
        std::cout << "Oops! " << error << std::endl;
        std::cout << "Try again!" << std::endl;
        DateClass error_result;
        return error_result;
    }

    DateClass result(unixdate - new_value.unixdate);
    return result;
}
const DateClass DateClass::operator*(const DateClass &new_value) {
    DateClass result(unixdate * new_value.unixdate);
    return result;
}
const DateClass DateClass::operator/(const DateClass &new_value) {
    try{
        if (new_value.unixdate == 0) throw "Invalid operation (/) for this operands! (second value's unix form is 0!)";
    }
    catch (const char* error){
        std::cout << "Oops! " << error << std::endl;
        std::cout << "Try again!" << std::endl;
        DateClass error_result;
        return error_result;
    }
    DateClass result(unixdate / new_value.unixdate);
    return result;
}
const DateClass& DateClass::operator=(const DateClass &new_value) {
    unixdate = new_value.unixdate;
    filetime = new_value.filetime;
    year = new_value.year;
    mon = new_value.mon;
    day = new_value.day;
    hour = new_value.hour;
    min = new_value.min;
    sec = new_value.sec;
    return *this;
}
std::ostream& operator<< (std::ostream &out, const DateClass& date){
    out.fill('0');
    out.width(2);
    out << date.hour << ":";
    out.width(2);
    out << date.min << ":";
    out.width(2);
    out << date.sec << " ";
    out.width(2);
    out << date.day << "/";
    out.width(2);
    out << date.mon << "/";
    out << date.year << " || ";
    out << date.unixdate << " || ";
    out << date.filetime;

    return out;
}
std::istream& operator>> (std::istream &in, DateClass& date){
    std::vector<std::string> pos;
    try {
        if (!(date.sec>=0 && date.sec<=59)) pos.push_back("seconds");
        if (!(date.min>=0 && date.min<=59)) pos.push_back("minutes");
        if (!(date.hour>=0 && date.hour<=23)) pos.push_back("hours");
        if (!(date.mon>=1 && date.mon<=12)) pos.push_back("months");
        if (!(date.year>1969)) pos.push_back("years");
        if (((date.year%4==0 && date.year%100!=0) || date.year%400==0)) DateClass::a[1] = 29;
        else DateClass::a[1] = 28;
        if (!(date.day <= DateClass::a[date.mon-1] && date.day >= 1)) pos.push_back("days");
        in >> date.sec;
        in >> date.min;
        in >> date.hour;
        in >> date.day;
        in >> date.mon;
        in >> date.year;
        date.unixdate = to_unix_form(date.year, date.mon, date.day, date.hour, date.min, date.sec);
        date.filetime = to_file_form(date.year, date.mon, date.day, date.hour, date.min, date.sec);
        if (!pos.empty()) throw "You have an error in the parameter of ";
    }
    catch (const char* error) {
        std::cerr << "Oops! " << error << std::endl;
        for (uint64_t i = 0; i < pos.size()-1; ++i)
            std::cout << pos[i] << ", ";
        std::cout << pos[pos.size()-1];
        std::cout << ")" << std::endl;
        std::cout << "The default parameters are set." << std::endl;
        date.sec = 0;
        date.min = 0;
        date.hour = 0;
        date.day = 1;
        date.mon = 1;
        date.year = 1970;
        date.unixdate = 0;
        date.filetime = to_file_form(date.year, date.mon, date.day, date.hour, date.min, date.sec);
    }
    return in;
}

std::string DateClass::getDayWeek() const {

    std::string dayOfWeek[7] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    short countDayOfWeek[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (((year%4==0 && year%100!=0) || year%400==0)) ++countDayOfWeek[1];
    int a = (14 - mon) / 12;
    int y = year - a;
    int m = mon + 12 * a - 2;
    return dayOfWeek[(day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7];

}




