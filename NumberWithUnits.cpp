#include "NumberWithUnits.hpp"

using namespace std;

namespace ariel {
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
        size_t pos1 = input.find('=')-3*sizeof(char);
        string firstUnit = input.substr(2, pos1);
        size_t pos2 = input.find('=')+2*sizeof(char);
        string afterFirst = input.substr(pos2);
        size_t pos3 = afterFirst.find(' ');
        string times = afterFirst.substr(0, pos3);
        size_t pos4 = afterFirst.find(' ')+sizeof(char);
        string secondUnit = afterFirst.substr(pos4);
    }


    const NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &other) const {
        return NumberWithUnits();
    }

    const NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &other) const {
        return NumberWithUnits();
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &other) {
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &other) {
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator+() {
        return *this;
    }

    NumberWithUnits &NumberWithUnits::operator-() {
        return *this;
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
        return NumberWithUnits();
    }

    NumberWithUnits &NumberWithUnits::operator*(const double num) {
        return *this;
    }

    std::ostream &operator<<(std::ostream &os, const NumberWithUnits &c) {
        return os;
    }

    std::istream &operator>>(std::istream &is, NumberWithUnits &c) {
        return is;
    }
};
