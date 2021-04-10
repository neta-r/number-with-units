#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>

namespace ariel {
    class NumberWithUnits {
    private:
        int number;
        std::string unit;
    public:
        static std::unordered_map <std::string, std::unordered_map<std::string, double>> map;

        NumberWithUnits(int num = 0, std::string un = "km") {
            number = num;
            unit = un;
            //TODO: add here checks for incorrect string format
        }

        static void read_units(std::ifstream &units_file);


        //functions that should be private:
        static void lineAnalysis(std::string input);

        static void checkUnits(std::string firstUnit, std::string secondUnit, double timesNum);

        void print();
        //end


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