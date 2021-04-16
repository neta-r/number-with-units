#include "doctest.h"
#include "NumberWithUnits.hpp"
#include "Test.hpp"
#include <string>
#include <cstdlib>

using namespace std;

namespace ariel {

    string Test::write_unit(ofstream &file) {
        string unit;
        int r;
        char c;
        int unit_len = (rand() % 5) + 1;
        for (int i = 0; i < unit_len; i++) {
            int lower_of_upper = rand(); //lower=even, upper=odd
            r = rand() % 26;
            if (lower_of_upper%2==0) c = 'a' + r;
            else c = 'A' + r;
            file << c;
            unit += c;
        }
        return unit;
    }

    double Test::write_num(ofstream &file) {
        double num=((double)rand()/(double)1000000);
        file << num;
        return num;
    }

    void Test::write_first_line(ofstream &file) {
        file << "1 ";
        string first_unit = write_unit(file);
        file << " = ";
        double num = write_num(file);
        file << " ";
        string second_unit = write_unit(file);
        file << "\n";
        first_units[0]=first_unit;
        second_units[0]=second_unit;
        times[0]=num;
    }
    void Test::write_line(ofstream &file) {
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

    void Test::rand_file() {
        ofstream file;
        file.open("unitTest.txt");
        int num_of_lines = (rand() % 10) + 1;
        actual_size=num_of_lines;
        write_first_line(file);
        for (int j = 1; j < num_of_lines; j++) write_line(file);
        file.close();
    }
};

TEST_CASE ("test one") { //creat hpp in the end
    ariel::Test test;
    test.rand_file();
}