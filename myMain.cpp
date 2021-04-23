#include "NumberWithUnits.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
using namespace ariel;

int main() {
    //open file
    ofstream MyFile("filename.txt");

    // Write to the file
    MyFile
            << "1 r_km = 1000 r_m\n1 r_m = 100 r_cm\n1 r_kg = 1000 r_g\n1 r_ton = 1000 r_kg\n1 r_hour = 60 r_min\n1 r_min = 60 r_sec\n1 r_USD = 3.33 r_ILS";
    MyFile.close();

    ifstream units_MyFile{"filename.txt"};
    NumberWithUnits::read_units(units_MyFile);

    NumberWithUnits a(7, "r_ILS");
    NumberWithUnits b(7, "r_ILS");
    NumberWithUnits c(7, "r_ILS");
    istringstream iss3{" -16 [r_m]   -7 [r_hour ]  8.8 [r_min ]"};
    iss3 >> a >> b >> c;
cout << a.getUnit() << endl << b.getUnit() << endl << c.getUnit() <<endl;
}