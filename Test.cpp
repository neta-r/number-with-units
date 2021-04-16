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
        if (num_of_lines<5) num_of_lines=5;
        actual_size=num_of_lines;
        write_first_line(file);
        for (int j = 1; j < num_of_lines; j++) write_line(file);
        file.close();
    }

    string Test::flip_letters(string str){
        string ans;
        for (size_t j=0; j<str.length(); j++){
            if (str.at(j)>='a' && str.at(j)<='z') ans+=str.at(j)-'a'+'A';
            else  ans+=str.at(j)-'A'+'a';
        }
        return ans;
    }

};
using namespace ariel;

TEST_CASE ("test read_units and creating the right NumberWithUnits") {
    Test test;
    test.rand_file();
    ifstream units_file{"unitTest.txt"};
    NumberWithUnits::read_units(units_file);
    string unit=test.first_units[test.actual_size-1];
    DOCTEST_CHECK_NOTHROW(NumberWithUnits a(2, unit));
    string flipped_unit=test.flip_letters(unit);
    DOCTEST_CHECK_THROWS(NumberWithUnits b(2, flipped_unit));
    unit=test.first_units[0];
    DOCTEST_CHECK_NOTHROW(NumberWithUnits c(2, unit));
    flipped_unit=test.flip_letters(unit);
    DOCTEST_CHECK_THROWS(NumberWithUnits d(2, flipped_unit));
}













