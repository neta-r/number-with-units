#include "doctest.h"
#include "NumberWithUnits.hpp"

using namespace ariel;

#include <string>
#include <cstdlib>

using namespace std;

class Test {
    string first_units[10];
    string second_units[10];
    int times[10];
    int actual_size;
    int i=1;


    string write_unit(ofstream &file) {
        string unit;
        int r;
        char c;
        int unit_len = (rand() % 5) + 1;
        for (int i = 0; i < unit_len; i++) {
            r = rand() % 26;
            c = 'a' + r;
            file << c;
            unit += c;
        }
        return unit;
    }

    int write_num(ofstream &file) {
        int num = (rand() % 10000) + 1;
        file << num;
        return num;
    }

    void write_first_line(ofstream &file) {
        file << "1 ";
        string first_unit = write_unit(file);
        file << " = ";
        int num = write_num(file);
        file << " ";
        string second_unit = write_unit(file);
        file << "\n";
        first_units[0]=first_unit;
        second_units[0]=second_unit;
        times[0]=num;
    }
    void write_line(ofstream &file) {
        file << "1 ";
        string first_unit = second_units[i-1];
        file << first_unit;
        file << " = ";
        int num = write_num(file);
        file << " ";
        string second_unit = write_unit(file);
        file << "\n";
        first_units[i]=first_unit;
        second_units[i]=second_unit;
        times[i]=num;
        i++;
    }

public:
    void rand_file() {

        ofstream file;
        file.open("unitTest.txt");
        int num_of_lines = (rand() % 10) + 1;
        actual_size=num_of_lines;
        write_first_line(file);
        for (int j = 1; j < num_of_lines; j++) write_line(file);
        file.close();
    }
};

TEST_CASE ("test one") {
    Test test;
    test.rand_file();
}