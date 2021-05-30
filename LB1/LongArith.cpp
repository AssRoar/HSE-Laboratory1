//
// Created by Асрор Юлдашев on 14.05.2021.
//

#include <vector>



LongArith::LongArith() {
    main_string = "0";
}
LongArith::LongArith(std::string new_value){
    main_string = new_value;
}
LongArith::LongArith(const LongArith &new_value) {
    main_string = new_value.main_string;
}
LongArith::~LongArith() {

}


std::string LongArith::getString(){
    return main_string;
}

void LongArith::setString(std::string new_value){
    main_string = new_value;
}

std::string rev_str(std::string in){
    std::string out = "";
    for (uint64_t i=in.size(); i>=1; --i) out.push_back(in[i-1]);
    return out;
}
bool fib = true, equal = true;
void leading(std::string& first, std::string& second){
    fib = true;
    first = rev_str(first);
    if (first[first.size()-1] == '-') first.pop_back();
    while(first[first.size()-1] == '0' && first.size()>1) first.pop_back();
    second = rev_str(second);
    if (second[second.size()-1] == '-') second.pop_back();
    while(second[second.size()-1] == '0' && second.size()>1) second.pop_back();
    if (first.size()<second.size())
        while(first.size()!=second.size()) first.push_back('0');
    else while(first.size()!=second.size()) second.push_back('0');
    for (uint64_t i = first.size(); i >= 1; --i) {
        if (first[i-1] > second[i-1]) {
            equal = false;
            fib = true;
            return;
        } else if (second[i-1] > first[i-1]) {
            fib = false;
            equal = false;
            return;
        }
    }
    return;
}
std::string sum_module(std::string first, std::string second){
    bool ost;
    ost = 0;
    std::string fvalue = first, svalue = second, ans = "";
    leading(fvalue, svalue);
    for (uint64_t i = 0; i < fvalue.size(); ++i){
        ans.push_back(((fvalue[i] - '0') + (svalue[i]-'0') + ost) % 10 + '0');
        ost = ((fvalue[i] - '0') + (svalue[i]-'0') + ost) / 10;
    }
    if (ost) ans.push_back(ost + '0');
    return rev_str(ans);
}
std::string diff_module(std::string first, std::string second){
    std::string fvalue = first, svalue = second, ans = "";
    leading(fvalue, svalue);
    for (uint64_t i = 0; i < fvalue.size(); ++i){
        if (fvalue[i] < svalue[i]) {
            ans.push_back(((fvalue[i] - '0') - (svalue[i] - '0') + 10) + '0');
            fvalue[i+1] = ((fvalue[i+1]-'0') - 1) + '0';
        }
        else ans.push_back(((fvalue[i] - '0') - (svalue[i] - '0')) + '0');
    }
    while(ans[ans.size()-1] == '0' && ans.size()>1) ans.pop_back();
    return rev_str(ans);
}

LongArith LongArith::operator+(const LongArith& new_value){
    std::string answer = "";
    std::string sum = sum_module(this->main_string, new_value.main_string);
    std::string diff;
    if (fib)
        diff = diff_module(this->main_string, new_value.main_string);
    else
        diff = diff_module(new_value.main_string, this->main_string);

    if (equal){
        if ((this->main_string[0] == '-' && new_value.main_string[0] != '-') ||
            (this->main_string[0] != '-' && new_value.main_string[0] == '-'))
            return LongArith("0");
        if (this->main_string[0] == '-') answer.push_back('-');
        return LongArith(sum);
    }
    if (this->main_string[0] == '-' && new_value.main_string[0] == '-') {
        answer.push_back('-');
        answer += sum;
        return LongArith(answer);
    }
    else if (this->main_string[0] != '-' && new_value.main_string[0] != '-') {
        answer += sum;
        return LongArith(answer);
    }
    else if (this->main_string[0] == '-' && fib) return LongArith("-" + diff);
    else if (fib) return LongArith(diff);
    else if (new_value.main_string[0] == '-' && !fib) return LongArith("-" + diff);
    else if (!fib) return LongArith(diff);
}
LongArith LongArith::operator-(const LongArith& new_value){
    std::string sum = sum_module(this->main_string, new_value.main_string);
    std::string diff;
    if (fib)
        diff = diff_module(this->main_string, new_value.main_string);
    else
        diff = diff_module(new_value.main_string, this->main_string);
    if (equal){
        if ((this->main_string[0] == '-' && new_value.main_string[0] != '-') ||
            (this->main_string[0] != '-' && new_value.main_string[0] == '-')){
            if (this->main_string[0] == '-')
                return LongArith("-" + sum);
            return LongArith(sum);
        }
        return LongArith("0");
    }
    else if (this->main_string[0] == '-' && new_value.main_string[0] == '-') {
        if (fib) return LongArith("-" + diff);
        return LongArith(diff);
    }
    else if (this->main_string[0] != '-' && new_value.main_string[0] != '-') {
        if (fib) return LongArith(diff);
        return LongArith("-" + diff);
    }
    else if (this->main_string[0]=='-'){
        return LongArith("-" + sum);
    }
    else return LongArith(sum);
}
LongArith LongArith::operator*(const LongArith& new_value) {
    std::string first = this->main_string, second = new_value.main_string;
    leading(first, second);
    while(first[first.size()-1] == '0' && first.size()>1) first.pop_back();
    while(second[second.size()-1] == '0' && second.size()>1) second.pop_back();
    first = rev_str(first);
    second = rev_str(second);
    if (!fib) swap(first, second);
    LongArith timer(second);
    LongArith answer(first);
    if (second == "0" || first == "0") return LongArith("0");
    while (timer.main_string != "1"){
        answer = answer + LongArith(first);
        timer = timer - LongArith("1");
    }
    if ((this->main_string[0] == '-' && new_value.main_string[0] == '-') ||
        (this->main_string[0] != '-' && new_value.main_string[0] != '-'))
        return answer;
    else return LongArith("-" + answer.main_string);
}
LongArith LongArith::operator/(const LongArith &new_value) {
    try{
        std::string first = this->main_string, second = new_value.main_string;
        leading(first, second);
        while(first[first.size()-1] == '0' && first.size()>1) first.pop_back();
        while(second[second.size()-1] == '0' && second.size()>1) second.pop_back();
        first = rev_str(first);
        second = rev_str(second);
        LongArith q(first), w(second), answer("0"), one("1");

        if (w.main_string == "0") throw "Division by zero!";
        while (q >= w) {
            q = q-w;
            answer = answer + one;
        }
        if ((this->main_string[0] == '-' && new_value.main_string[0] == '-') ||
            (this->main_string[0] != '-' && new_value.main_string[0] != '-') ||
            (answer.main_string == "0"))
            return answer;
        else return LongArith("-" + answer.main_string);
    }
    catch(const char* error) {
        std::cerr << error << " (" << ")" << std::endl;
        std::cout << "Try again!" << std::endl;
        return LongArith("0");
    }
}
LongArith LongArith::operator%(const LongArith &new_value) {
    try{
        LongArith q(this->main_string), w(new_value.main_string), one("01");

        std::string first = rev_str(q.main_string);
        if (first[first.size()-1] == '-') first.pop_back();
        while(first[first.size()-1] == '0' && first.size()>1) first.pop_back();

        std::string second = rev_str(w.main_string);
        if (second[second.size()-1] == '-') second.pop_back();
        while(second[second.size()-1] == '0' && second.size()>1) second.pop_back();

        if (w.main_string == "0") throw "Division by zero!";
        while (q >= w) {
            q = q-w;
        }
        if ((this->main_string[0] == '-' && new_value.main_string[0] == '-') ||
            (this->main_string[0] != '-' && new_value.main_string[0] != '-'))
            return q;
        else return LongArith("-" + q.main_string);
    }
    catch(const char* error) {
        std::cerr << error << " (" << ")" << std::endl;
        std::cout << "Try again!" << std::endl;
        return LongArith("0");
    }
}
bool LongArith::operator>=(const LongArith &new_value) {
    std::string f = this->main_string, s = new_value.main_string;
    if ((f[0] == '-') && (s[0] != '-')) return false;
    else if ((f[0] != '-') && (s[0] == '-')) return true;
    else if ((f[0] == '-') && (s[0] == '-')){
        leading(f, s);
        return !fib || equal;
    }
    leading(f, s);
    return fib || equal;
}
bool LongArith::operator<=(const LongArith &new_value) {
    std::string f = this->main_string, s = new_value.main_string;
    if ((f[0] == '-') && (s[0] != '-')) return true;
    else if ((f[0] != '-') && (s[0] == '-')) return false;
    else if ((f[0] == '-') && (s[0] == '-')){
        leading(f, s);
        return !fib || equal;
    }
    leading(s, f);
    return fib || equal;
}
bool LongArith::operator>(const LongArith &new_value) {
    std::string f = this->main_string, s = new_value.main_string;
    if ((f[0] == '-') && (s[0] != '-')) return false;
    else if ((f[0] != '-') && (s[0] == '-')) return true;
    else if ((f[0] == '-') && (s[0] == '-')){
        leading(f, s);
        return !fib && !equal;
    }
    leading(f, s);
    return fib && !equal;
}
bool LongArith::operator<(const LongArith &new_value) {
    std::string f = this->main_string, s = new_value.main_string;
    if ((f[0] == '-') && (s[0] != '-')) return true;
    else if ((f[0] != '-') && (s[0] == '-')) return false;
    else if ((f[0] == '-') && (s[0] == '-')){
        leading(f, s);
        return !fib && !equal;
    }
    leading(s, f);
    return fib && !equal;
}
bool LongArith::operator==(const LongArith &new_value) {
    std::string f = this->main_string, s = new_value.main_string;
    if (!(s[0] == '-' && f[0] == '-') || !(f[0] != '-' && s[0] != '-')) return false;
    leading(s, f);
    return equal;
}
std::ostream& operator<< (std::ostream &out, const LongArith& value){
    for (int i=0; i<value.main_string.size(); ++i) out << value.main_string[i];
    return out;
}
std::istream& operator>> (std::istream &in, LongArith& value) {
    std::vector<uint64_t> pos{};
    try {
        in >> value.main_string;
        if (!((value.main_string[0] == '-') || ('9'>=value.main_string[0] && value.main_string[0]>='0'))) pos.push_back(1);
        for (uint64_t i = 1; i < value.main_string.size(); ++i){
            if (('9' < value.main_string[i] || value.main_string[i] < '0')) pos.push_back(i+1);
        }
        if (!pos.empty()) throw "Invalid input!";
    }
    catch(const char* error){
        std::cout << error << std::endl << "(pos. ";
        for (uint64_t i = 0; i < pos.size()-1; ++i)
            std::cout << pos[i] << ", ";
        std::cout << pos[pos.size()-1];
        std::cout << ")" << std::endl;
        std::cout << "Try again!" << std::endl;
        value.main_string = "0";
    }
    return in;
}


LongArith& LongArith::operator=(const LongArith &new_value) {
    this->main_string = new_value.main_string;
    return *this;
}


