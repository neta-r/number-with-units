//
// Created by neta on 10/04/2021.
//

#include "myMain.h"

#include "NumberWithUnits.hpp"
using namespace ariel;

int main() {
    std::string line = "1 min = 60 sec";
    NumberWithUnits::lineAnalysis(line);
}
