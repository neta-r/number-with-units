#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

namespace ariel {
    class NumberWithUnits {
    private:
        static std::unordered_map <std::string, std::unordered_map<std::string, double>> map;

        double number;

        std::string unit;

        static void lineAnalysis(std::string input);

        static void checkUnits(const std::string& firstUnit,const std::string& secondUnit, double timesNum);

    public:

        NumberWithUnits(double num = 0, std::string un = "km") {
            if (map.find (un)!=map.end()){ //the unit exist in stock
                number = num;
                unit = un;
            }
            else{
                throw std::invalid_argument{"no such unit in stock"};
            }
        }

        static void read_units(std::ifstream &units_file);

        std::string getUnit ();

        double getNum () const;

        NumberWithUnits operator+(const NumberWithUnits &other) const;

        NumberWithUnits operator-(const NumberWithUnits &other) const;

        NumberWithUnits &operator+=(const NumberWithUnits &other);

        NumberWithUnits &operator-=(const NumberWithUnits &other);

        NumberWithUnits operator+();

        NumberWithUnits operator-();

        bool operator==(const NumberWithUnits &other) const;

        bool operator!=(const NumberWithUnits &other) const;

        bool operator>(const NumberWithUnits &other) const;

        bool operator<(const NumberWithUnits &other) const;

        bool operator>=(const NumberWithUnits &other) const;

        bool operator<=(const NumberWithUnits &other) const;

        NumberWithUnits &operator++();

        NumberWithUnits operator++(int);

        NumberWithUnits &operator--();

        NumberWithUnits operator--(int);

        friend NumberWithUnits operator*(const double num, const NumberWithUnits &c);

        NumberWithUnits operator*(const double num);

        friend std::ostream &operator<<(std::ostream &os, const NumberWithUnits &c);

        friend std::istream &operator>>(std::istream &is, NumberWithUnits &c);
    };
}