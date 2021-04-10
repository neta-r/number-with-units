#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "node.cpp"

namespace ariel {
    class NumberWithUnits {
    private:
        int number;
        std::string unit;
        static std::vector <std::list<node>> units;

    public:

        NumberWithUnits(int num = 0, std::string un = "km") {
            number = num;
            unit = un;
            //TODO: add here checks for incorrect string format
        }

        static void read_units(std::ifstream &units_file);

        static void lineAnalysis(std::string input);

        const NumberWithUnits operator+(const NumberWithUnits &other) const;

        const NumberWithUnits operator-(const NumberWithUnits &other) const;

        NumberWithUnits &operator+=(const NumberWithUnits &other);

        NumberWithUnits &operator-=(const NumberWithUnits &other);

        NumberWithUnits &operator+();

        NumberWithUnits &operator-();

        bool operator==(const NumberWithUnits &other) const;

        bool operator!=(const NumberWithUnits &other) const;

        bool operator>(const NumberWithUnits &other) const;

        bool operator<(const NumberWithUnits &other) const;

        bool operator>=(const NumberWithUnits &other) const;

        bool operator<=(const NumberWithUnits &other) const;

        NumberWithUnits &operator++();

        const NumberWithUnits operator++(int);

        friend NumberWithUnits operator*(const double num, const NumberWithUnits &c);

        NumberWithUnits &operator*(const double num);

        friend std::ostream &operator<<(std::ostream &os, const NumberWithUnits &c);

        friend std::istream &operator>>(std::istream &is, NumberWithUnits &c);
    };
}