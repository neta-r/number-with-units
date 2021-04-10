#include "NumberWithUnits.hpp"

using namespace std;

namespace ariel {
    void NumberWithUnits::read_units(ifstream &units_file) {

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
