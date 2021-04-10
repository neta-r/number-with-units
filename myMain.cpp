//
// Created by neta on 10/04/2021.
//


#include "NumberWithUnits.hpp"
using namespace ariel;

int main() {
    std::ifstream units_file{"otherFile.txt"};
    NumberWithUnits::read_units(units_file);
}
