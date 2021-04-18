#include "NumberWithUnits.hpp"
#include <exception>

using namespace std;

namespace ariel {


    std::unordered_map <std::string, std::unordered_map<std::string, double>> NumberWithUnits::map =
            std::unordered_map < std::string, std::unordered_map<std::string, double>>
    ();

    string NumberWithUnits::getUnit() {
        return this->unit;
    }

    double NumberWithUnits::getNum() {
        return this->number;
    }


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
        string firstUnit, secondUnit, num;
        size_t i = 0;
        //skipping until char is a letter
        while (input.at(i) < 'A' || input.at(i) > 'z' || (input.at(i) > 'Z' && input.at(i) < 'a')) i++;
        input = input.substr(i);
        i = 0;
        //reading all letters
        while ((input.at(i) >= 'a' && input.at(i) <= 'z') || (input.at(i) >= 'A' && input.at(i) <= 'Z')) i++;
        firstUnit = input.substr(0, i);
        input = input.substr(i);
        i = 0;
        //skipping until char is a number
        while (input.at(i) < '0' || input.at(i) > '9') i++;
        input = input.substr(i);
        i = 0;
        //reading full number
        while ((input.at(i) >= '0' && input.at(i) <= '9') || input.at(i) == '.') i++;
        num = input.substr(0, i);
        double times = std::stod(num);
        input = input.substr(i);
        i = 0;
        //skipping until char is a letter
        while (input.at(i) < 'A' || input.at(i) > 'z' || (input.at(i) > 'Z' && input.at(i) < 'a')) i++;
        input = input.substr(i);
        i = 0;
        //reading till end
        for (; i < input.size(); i++) {
            if ((input.at(i) < 'A' && input.at(i) > 'z') || (input.at(i) < 'a' && input.at(i) > 'Z')) break;
        }
        if (i > 0) secondUnit = input.substr(0, i);
        else secondUnit = input;
        NumberWithUnits::checkUnits(firstUnit, secondUnit, times);
    }

    void NumberWithUnits::checkUnits(string firstUnit, string secondUnit, double timesNum) {
        for (const auto &kv: map[firstUnit]) {
            double what;
            if (kv.second > 1) what = timesNum;
            else what = 1 / timesNum;
            map[secondUnit][kv.first] = kv.second * what;
            map[kv.first][secondUnit] = 1 / (kv.second * what);
            //cout << "map[" << secondUnit <<"][" << kv.first << "] = " << kv.second * what <<endl;
            //cout << "map[" << kv.first <<"][" << secondUnit << "] = " << 1 / (kv.second * what) <<endl;
        }
        map[firstUnit][secondUnit] = timesNum;
        map[secondUnit][firstUnit] = 1 / timesNum;
        //cout << "map[" << firstUnit <<"][" << secondUnit << "] = " << timesNum <<endl;
        //cout << "map[" << secondUnit <<"][" << firstUnit << "] = " << 1 / timesNum <<endl;
    }


    const NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &other) const {
        double times = map[other.unit][this->unit];
        if (times == 0) { //times not found
            string message =
                    "Units do not match - [" + other.unit + "] cannot be converted to [" + this->unit + "]";
            throw std::invalid_argument(message);
        }
        double newOther = other.number * times;
        return NumberWithUnits(this->number + newOther, this->unit);
    }

    const NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &other) const {
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

    float NumberWithUnits::round(double num) const{
        float newNum = (int) (num * 100);
        newNum = (float) newNum / 100;
        return newNum;
    }


    bool NumberWithUnits::operator==(const NumberWithUnits &other) const {
        if (this->unit == other.unit) {
            float first = round(this->number);
            float sec = round(other.number);
            return first == sec;
        }
        double times = map[other.unit][this->unit];
        if (times == 0) { // no possible way to convert from the two units
            string message = "Units does not match";
            throw std::invalid_argument(message);
        }
        float first = round(this->number);
        float sec = round(other.number*times);
        return first == sec;

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
        float first = round(this->number);
        float sec = round(other.number*times);
        return first > sec;
    }

    bool NumberWithUnits::operator<(const NumberWithUnits &other) const {
        double times = map[other.unit][this->unit];
        if (times == 0) {// no possible way to convert from the two units
            string message = "Units does not match";
            throw std::invalid_argument(message);
        }
        float first = round(this->number);
        float sec = round(other.number*times);
        return first < sec;
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

    const NumberWithUnits NumberWithUnits::operator++(int) {
        NumberWithUnits copy{this->number, this->unit};
        this->number++;
        return copy;
    }

    NumberWithUnits &NumberWithUnits::operator--() {
        this->number--;
        return *this;
    }

    const NumberWithUnits NumberWithUnits::operator--(int) {
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
        char actualChar;
        input >> actualChar;
        if (!input) return input;

        if (actualChar != expectedChar)
            // failbit is for format error
            input.setstate(ios::failbit);
        return input;
    }

    std::istream &operator>>(std::istream &is, NumberWithUnits &c) {
        int num;
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
