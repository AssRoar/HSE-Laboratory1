#include "DateHeader.h"
#include "LongArithmetic.h"
#include <iostream>


int main() {
    time_t filetime = 1;
    DateClass date1(filetime);
    DateClass date2(0, 0, 0, 27, 5, 2021);
    std::cout << "first: " << date1 << std::endl << " second: " << date2 << std::endl;
    std::cout << "date1" << " + " << "date2" << " = " << date1+date2 << std::endl;
    std::cout << "date2" << " - " << "date1" << " = " << date2-date1<< std::endl;
    std::cout << "date1" << " * " << "date2" << " = " << date1*date2 << std::endl;
    std::cout << "date2" << " / " << "date1" << " = " << date2/date1 << std::endl;


    std::cout << " " << std::endl;
    LongArith f("-53"), s("314528");
    std::cout << "first: " << f.getString() << " second: " << s.getString() << std::endl;
    std::cout << f.getString() << " + " << s.getString() << " = " << s+f << std::endl;
    std::cout << f.getString() << " - " << s.getString() << " = " << f-s<< std::endl;
    std::cout << f.getString() << " * " << s.getString() << " = " << f*s << std::endl;
    std::cout << f.getString() << " / " << s.getString() << " = " << f/s << std::endl;
    std::cout << f.getString() << " > " << s.getString() << " = " << ((f>s)?"True":"False") << std::endl;
    std::cout << f.getString() << " < " << s.getString() << " = " << ((f<s)?"True":"False") << std::endl;
    std::cout << f.getString() << " >= " << s.getString() << " = " << ((f>=s)?"True":"False") << std::endl;
    std::cout << f.getString() << " <= " << s.getString() << " = " << ((f<=s)?"True":"False") << std::endl;
    return 0;
}