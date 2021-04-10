#include "NumberWithUnits.hpp"

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
            print();
        } else cout << "Unable to open file";
    }


    //this function extract the relevant data from each line
    void NumberWithUnits::lineAnalysis(string input) {
        size_t pos1 = input.find('=') - 3 * sizeof(char);
        string firstUnit = input.substr(2, pos1);
        size_t pos2 = input.find('=') + 2 * sizeof(char);
        string afterFirst = input.substr(pos2);
        size_t pos3 = afterFirst.find(' ');
        string times = afterFirst.substr(0, pos3);
        double timesNum = std::stod(times);
        size_t pos4 = afterFirst.find(' ') + sizeof(char);
        string secondUnit = afterFirst.substr(pos4);
        checkUnits(firstUnit, secondUnit, timesNum);
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

    //print all of the possible converting from unit to unit
    void NumberWithUnits::print() {
        for (const auto &kv: map) {
            for (const auto &KV: map[kv.first]) {
                cout << "first: " + kv.first + ", second: " + KV.first + ", val: " << KV.second << endl;
            }
        }
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
