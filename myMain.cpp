
#include "NumberWithUnits.hpp"
using namespace std;
using namespace ariel;

int main() {
    std::ifstream units_file{"otherFile.txt"};
    NumberWithUnits::read_units(units_file);
//    try {
//        NumberWithUnits b{300, "meow"};
//    } catch (const std::exception& ex) {
//        std::cout << ex.what() << std::endl;
//    }
}
