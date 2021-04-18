#include "NumberWithUnits.hpp"
#include <exception>
#include <sstream>

using namespace std;

namespace ariel {
    const double epsilon = 0.001;
    const int base = 100;

    std::unordered_map <std::string, std::unordered_map<std::string, double>> NumberWithUnits::map =
            std::unordered_map < std::string, std::unordered_map<std::string, double>>
    ();

    string NumberWithUnits::getUnit() {
        return this->unit;
    }

    double NumberWithUnits::getNum() const{
        return this->number;
    }


    void NumberWithUnits::read_units(ifstream &units_file) {

        if (units_file.is_open()) {
            string line;
            while (std::getline(units_file, line)) {
                lineAnalysis(line);
            }
            units_file.close();
        }
        else{
            cout << "Unable to open file";
        }
    }

    void NumberWithUnits::lineAnalysis(string input) {
        string firstUnit;
        string secondUnit;
        input.erase(input.find_first_of('='),1);
        input.erase(input.find_first_of('1'),1);
        double times=0;
        istringstream stream(input);
        stream >> firstUnit >> times >> secondUnit;
        NumberWithUnits::checkUnits(firstUnit, secondUnit, times);
    }

    void NumberWithUnits::checkUnits(const string& firstUnit,const string& secondUnit, double timesNum) {
        for (const auto &kv: map[firstUnit]) {
            if(map[secondUnit][kv.first]==0) {
                double what = 0;
                if (kv.second > 1) {
                    what = timesNum;
                } else {
                    what = 1 / timesNum;
                }
                map[kv.first][secondUnit] =1/(kv.second * what);
                map[secondUnit][kv.first] =kv.second * what;
                //cout << "map[" << kv.first << "][" << secondUnit << "] = " << 1/(kv.second * what) << endl;
                //cout << "map[" << secondUnit << "][" << kv.first << "] = " <<kv.second * what<< endl;
            }
        }
        for (const auto &kv: map[secondUnit]) {
            if(map[firstUnit][kv.first]==0){
                double what=0;
                if (kv.second > 1){
                    what = timesNum;
                }
                else {
                    what = 1 / timesNum;
                }
                map[firstUnit][kv.first] = kv.second * what;
                map[kv.first ][firstUnit] =1/( kv.second * what);
                //cout << "map[" << firstUnit <<"][" << kv.first << "] = " << kv.second * what<<endl;
                //cout << "map[" << kv.first <<"][" << firstUnit << "] = " << 1/( kv.second * what) <<endl;
            }
        }
        map[firstUnit][secondUnit] =timesNum;
        map[secondUnit][firstUnit] =1/ timesNum;
        //cout << "map[" << firstUnit <<"][" << secondUnit << "] = " << timesNum <<endl;
        //cout << "map[" << secondUnit <<"][" << firstUnit << "] = " << 1 / timesNum <<endl;
    }


    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &other) const {
        double times = map[other.unit][this->unit];
        if (times == 0) { //times not found
            string message =
                    "Units do not match - [" + other.unit + "] cannot be converted to [" + this->unit + "]";
            throw std::invalid_argument(message);
        }
        double newOther = other.number * times;
        return NumberWithUnits(this->number + newOther, this->unit);
    }

    NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &other) const {
        double times = map[other.unit][this->unit];
        if (times == 0) { //times not found
            string message =
                    "Units do not match - [" + other.unit + "] cannot be converted to [" + this->unit + "]";
            throw std::invalid_argument(message);
        }
        double newOther = other.number * times;
        return NumberWithUnits(this->number - newOther, this->unit);
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &other) {
        double times = map[other.unit][this->unit];
        if (times == 0) { //times not found
            string message = "Units do not match - [" + other.unit + "] cannot be converted to [" + this->unit + "]";
            throw std::invalid_argument(message);
        }
        double newOther = other.number * times;
        this->number = this->number + newOther;
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &other) {
        double times = map[other.unit][this->unit];
        if (times == 0) { //times not found
            string message = "Units do not match - [" + other.unit + "] cannot be converted to [" + this->unit + "]";
            throw std::invalid_argument(message);
        }
        double newOther = other.number * times;
        this->number = this->number - newOther;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator+() {
        return NumberWithUnits(this->number, this->unit);
    }

    NumberWithUnits NumberWithUnits::operator-() {
        return NumberWithUnits(this->number * (-1), this->unit);
    }


    bool NumberWithUnits::operator==(const NumberWithUnits &other) const {
        if (this->unit == other.unit) {
            return std::abs(this->number-other.number)<epsilon;
        }
        double times = map[other.unit][this->unit];
        if (times == 0) { // no possible way to convert from the two units
            string message = "Units does not match";
            throw std::invalid_argument(message);
        }
        return std::abs(this->number-other.number*times)<epsilon;

    }

    bool NumberWithUnits::operator!=(const NumberWithUnits &other) const {
        return (!(*this == other));
    }

    bool NumberWithUnits::operator>(const NumberWithUnits &other) const {
        double times = map[other.unit][this->unit];
        if (times == 0) {// no possible way to convert from the two units
            string message = "Units does not match";
            throw std::invalid_argument(message);
        }
        return this->number >= (other.number*times)+epsilon;
    }

    bool NumberWithUnits::operator<(const NumberWithUnits &other) const {
        double times = map[other.unit][this->unit];
        if (times == 0) {// no possible way to convert from the two units
            string message = "Units does not match";
            throw std::invalid_argument(message);
        }
        return this->number <= (other.number*times)-epsilon;

    }

    bool NumberWithUnits::operator>=(const NumberWithUnits &other) const {
        return (!(*this < other));
    }

    bool NumberWithUnits::operator<=(const NumberWithUnits &other) const {
        return (!(*this > other));
    }

    NumberWithUnits &NumberWithUnits::operator++() {
        this->number++;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator++(int) {
        NumberWithUnits copy{this->number, this->unit};
        this->number++;
        return copy;
    }

    NumberWithUnits &NumberWithUnits::operator--() {
        this->number--;
        return *this;
    }

    NumberWithUnits NumberWithUnits::operator--(int) {
        NumberWithUnits copy{this->number, this->unit};
        this->number--;
        return copy;
    }

    NumberWithUnits operator*(const double num, const NumberWithUnits &c) {
        return NumberWithUnits(c.number * num, c.unit);
    }

    NumberWithUnits NumberWithUnits::operator*(const double num) {
        return NumberWithUnits(this->number * num, this->unit);
    }

    std::ostream &operator<<(std::ostream &os, const NumberWithUnits &c) {
        return (os << c.number << '[' << c.unit << ']');
    }

    static istream &getAndCheckNextCharIs(istream &input, char expectedChar) {
        char actualChar=' ';
        input >> actualChar;
        if (!input){
            return input;
        }
        if (actualChar != expectedChar){
            // failbit is for format error
            input.setstate(ios::failbit);
        }

        return input;
    }

    std::istream &operator>>(std::istream &is, NumberWithUnits &c) {
        int num=0;
        string un;
        ios::pos_type startPosition = is.tellg();
        if ((!(is >> std::skipws >> num)) ||
            (!getAndCheckNextCharIs(is, '[')) ||
            (!(is >> std::skipws >> un)) ||
            (!(getAndCheckNextCharIs(is, ']')))) {
            // rewind on error
            auto errorState = is.rdstate(); // remember error state
            is.clear(); // clear error so seekg will work
            is.seekg(startPosition); // rewind
            is.clear(errorState); // set back the error flag
        } else {
            c.number = num;
            c.unit = un;
        }
        return is;
    }
};
