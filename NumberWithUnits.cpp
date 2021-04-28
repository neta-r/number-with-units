#include "NumberWithUnits.hpp"
#include <exception>
#include <sstream>

using namespace std;

namespace ariel {
    const double epsilon = 0.001;

    std::unordered_map <std::string, std::unordered_map<std::string, double>> NumberWithUnits::map =
            std::unordered_map < std::string, std::unordered_map<std::string, double>>
    ();

    string NumberWithUnits::getUnit() {
        return this->unit;
    }

    double NumberWithUnits::getNum() const {
        return this->number;
    }


    void NumberWithUnits::read_units(ifstream &units_file) {

        if (units_file.is_open()) {
            string line;
            while (std::getline(units_file, line)) {
                lineAnalysis(line);
            }
            units_file.close();
        } else {
            cout << "Unable to open file" << endl;
        }
    }

    void NumberWithUnits::lineAnalysis(string input) {
        string firstUnit;
        string secondUnit;
        input.erase(input.find_first_of('='), 1); //removing =
        input.erase(input.find_first_of('1'), 1); //removing 1
        double times = 0;
        istringstream stream(input);
        stream >> firstUnit >> times >> secondUnit;
        NumberWithUnits::checkUnits(firstUnit, secondUnit, times);
    }

    void NumberWithUnits::checkUnits(const string &firstUnit, const string &secondUnit, double timesNum) {
        for (const auto &kv: map[firstUnit]) { //going over the first unit's neighbors in the map
            if (map[secondUnit][kv.first] == 0) {
                double what = 1/kv.second;
                map[kv.first][secondUnit] = what*timesNum;
                map[secondUnit][kv.first] = 1/(what*timesNum);
            }
        }
        for (const auto &kv: map[secondUnit]) { //going over the second unit's neighbors in the map
            if (map[firstUnit][kv.first] == 0) {
                double what = 1/kv.second;
                map[firstUnit][kv.first] = timesNum*(1/what);
                map[kv.first][firstUnit] = 1/(timesNum*(1/what));
            }
        }
        map[firstUnit][secondUnit] = timesNum; //adding first and second to map
        map[secondUnit][firstUnit] = 1 / timesNum;
    }


    NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &other) const {
        double times = map[other.unit][this->unit];
        if (this->unit == other.unit) { //no need to convert
            times = 1;
        }
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
        if (this->unit == other.unit) { //no need to convert
            times = 1;
        }
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
        if (this->unit == other.unit) { //no need to convert
            times = 1;
        }
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
        if (this->unit == other.unit) { //no need to convert
            times = 1;
        }
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
        if (this->unit == other.unit) { //no need to convert
            return std::abs(this->number - other.number) < epsilon;
        }
        double times = map[other.unit][this->unit];
        if (times == 0) { // no possible way to convert from the two units
            string message = "Units does not match";
            throw std::invalid_argument(message);
        }
        return std::abs(this->number - other.number * times) < epsilon;

    }

    bool NumberWithUnits::operator!=(const NumberWithUnits &other) const {
        return (!(*this == other));
    }

    bool NumberWithUnits::operator>(const NumberWithUnits &other) const {
        double times = map[other.unit][this->unit]; //no need to convert
        if (this->unit == other.unit) {
            times = 1;
        }
        if (times == 0) {// no possible way to convert from the two units
            string message = "Units does not match";
            throw std::invalid_argument(message);
        }
        return this->number >= (other.number * times) + epsilon;
    }

    bool NumberWithUnits::operator<(const NumberWithUnits &other) const {
        double times = map[other.unit][this->unit]; //times not found
        if (this->unit == other.unit) {
            times = 1;
        }
        if (times == 0) {// no possible way to convert from the two units
            string message = "Units does not match";
            throw std::invalid_argument(message);
        }
        return this->number <= (other.number * times) - epsilon;

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

    static istream& getAndCheckNextCharIs(istream& input, char expectedChar) {
        char actualChar = 0;
        input >> actualChar;
        if (!input) {return input;}

        if (actualChar!=expectedChar)
            // failbit is for format error
        {input.setstate(ios::failbit);}
        return input;
    }

    //sometimes the second unit swallows ']' so we need to remove it
    static bool findBracket (string& un) {
        size_t pos=un.find_first_of(']');
        if (pos!=string::npos) {
            un = un.substr(0, pos);
            return true;
        }
        return false;
    }

    istream& operator>>(istream& is, NumberWithUnits& c) {
        double num = 0;
        string un;
        // remember place for rewinding
        ios::pos_type startPosition = is.tellg();
        if ( (!(is >> num))                 ||
             (!getAndCheckNextCharIs(is,'['))  ||
             (!(is >> un))                 ||
             ((!findBracket(un)&&!(getAndCheckNextCharIs(is,']')))) ) {
            // rewind on error
            auto errorState = is.rdstate(); // remember error state
            is.clear(); // clear error so seekg will work
            is.seekg(startPosition); // rewind
            is.clear(errorState); // set back the error flag
        } else {
            if (NumberWithUnits::map.find (un)!=NumberWithUnits::map.end()){ //the unit exist in stock
                c.number = num;
                c.unit = un;
            }
            else{
                throw std::invalid_argument{"no such unit in stock"};
            }
        }
        return is;
    }
}