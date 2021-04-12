#include "NumberWithUnits.hpp"
#include <exception>

using namespace std;

namespace ariel {

    std::unordered_map <std::string, std::unordered_map<std::string, double>> NumberWithUnits::map = std::unordered_map <std::string, std::unordered_map<std::string, double>>();

    void NumberWithUnits::read_units(ifstream &units_file) {

        if (units_file.is_open()) {
            string line;
            while (std::getline(units_file, line)) {
                lineAnalysis(line);
            }
            units_file.close();
        } else cout << "Unable to open file";
    }



    void NumberWithUnits::lineAnalysis(string input) {
        //cutting until 1
        size_t pos = input.find('1')+sizeof(char);
        input = input.substr(pos);
        input =  NumberWithUnits::cutSpaces(input);
        //finding the '=' and cutting the first unit's name
        pos = input.find('=');
        string firstUnit = input.substr(0,pos); //cuts until "=" than clean the rest
        firstUnit = NumberWithUnits::cutExtra(firstUnit);
        input = input.substr(pos+sizeof(char)); //cleaning first unit's name from input
        input =  NumberWithUnits::cutSpaces(input);
        //cutting the number
        size_t i =NumberWithUnits::findNumberPos(input); //find out where thr number ends
        string num = input.substr(0,i);
        double times = std::stod(num);
        input = input.substr(i); //cleaning number from input
        input =  NumberWithUnits::cutSpaces(input);
        //cutting the second unit's name from what's left
        string secondUnit =  NumberWithUnits::cutExtra(input);
        NumberWithUnits::checkUnits(firstUnit, secondUnit, times);
    }

    //clean the first spaces from the input
    string NumberWithUnits::cutSpaces(string input){
        int numOfSpaces = 0;
        size_t i =0;
        while (input.at(i)==' ') { //cutting all spaces before the first unit
            i++;
            numOfSpaces++;
        }
        input = input.substr(i);
        return input;
    }

    //cuts the chars that are not letters from the end of the input
    string NumberWithUnits::cutExtra(string input){
        string ans;
        size_t cut =0;
        for (int i=0; i<input.length(); i++, cut++){
            if (input.at(cut)>='a'&&input.at(cut)<='z') ans=ans+input.at(cut);
            else break;
        }
        return ans;
    }

    //find out where the number ends
    size_t NumberWithUnits::findNumberPos(string input){
        size_t i =0;
        while ((input.at(i)>='0' && input.at(i)<='9') || input.at(i)=='.') { //still a number
            i++;
        }
        return i;
    }

    void NumberWithUnits::checkUnits(string firstUnit, string secondUnit, double timesNum) {
        for (const auto &kv: map[firstUnit]) {
            double what;
            if (kv.second > 1) what = timesNum;
            else what = 1 / timesNum;
            map[secondUnit][kv.first] = kv.second * what;
            map[kv.first][secondUnit] = 1 / (kv.second * what);
        }
        map[firstUnit][secondUnit] = timesNum;
        map[secondUnit][firstUnit] = 1 / timesNum;
    }


    const NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &other) const {
        try {
            double times = map[other.unit][this->unit];
            double newOther = other.number*times;
            return NumberWithUnits(this->number+newOther, this->unit);
        }
        catch (exception ex) { // no possible way to convert the other NumberWithUnits to this type
            string message = "Units do not match - ["+other.unit+"] cannot be converted to ["+this->unit+"]";
            throw string(message);
        }
    }

    const NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &other) const {
        try {
            double times = map[other.unit][this->unit];
            double newOther = other.number*times;
            return NumberWithUnits(this->number-newOther, this->unit);
        }
        catch (exception ex) { // no possible way to convert the other NumberWithUnits to this type
            string message = "Units do not match - ["+other.unit+"] cannot be converted to ["+this->unit+"]";
            throw string(message);
        }
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &other) {
        try {
            double times = map[other.unit][this->unit];
            double newOther = other.number*times;
            this->number=this->number+newOther;
        }
        catch (exception ex) { // no possible way to convert the other NumberWithUnits to this type
            string message = "Units do not match - ["+other.unit+"] cannot be converted to ["+this->unit+"]";
            throw string(message);
        }
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &other) {
        try {
            double times = map[other.unit][this->unit];
            double newOther = other.number*times;
            this->number=this->number-newOther;
        }
        catch (exception ex) { // no possible way to convert the other NumberWithUnits to this type
            string message = "Units do not match - ["+other.unit+"] cannot be converted to ["+this->unit+"]";
            throw string(message);
        }
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator+() {
        return NumberWithUnits(this->number, this->unit);
    }

    NumberWithUnits NumberWithUnits::operator-() {
        return NumberWithUnits(this->number*(-1), this->unit);
    }

    bool NumberWithUnits::operator==(const NumberWithUnits &other) const {
        return false;
    }

    bool NumberWithUnits::operator!=(const NumberWithUnits &other) const {
        return false;
    }

    bool NumberWithUnits::operator>(const NumberWithUnits &other) const {
        return false;
    }

    bool NumberWithUnits::operator<(const NumberWithUnits &other) const {
        return false;
    }

    bool NumberWithUnits::operator>=(const NumberWithUnits &other) const {
        return false;
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &other) const {
        return false;
    }

    NumberWithUnits &NumberWithUnits::operator++() {
        return *this;
    }

    const NumberWithUnits NumberWithUnits::operator++(int) {
        return NumberWithUnits();
    }

    NumberWithUnits operator*(const double num, const NumberWithUnits &c) {
        return NumberWithUnits(c.number*num, c.unit);
    }

    NumberWithUnits &NumberWithUnits::operator*(const double num) {
        this->number=this->number*num;
        return *this;
    }

    std::ostream &operator<<(std::ostream &os, const NumberWithUnits &c) {
        return (os << c.number<< '[' << c.unit << ']');
    }

    std::istream &operator>>(std::istream &is, NumberWithUnits &c) {
        return is;
    }
};
