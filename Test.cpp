#include "doctest.h"
#include "NumberWithUnits.hpp"
#include "Test.hpp"
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

namespace ariel {

    string Test::rand_unit() {
        string unit;
        int r;
        char c;
        int unit_len = (rand() % 5) + 1;
        for (int i = 0; i < unit_len; i++) {
            int lower_of_upper = rand(); //lower=even, upper=odd
            r = rand() % 26;
            if (lower_of_upper % 2 == 0) c = 'a' + r;
            else c = 'A' + r;
            unit += c;
        }
        return unit;
    }

    string Test::write_unit(ofstream &file) {
        string unit = rand_unit();
        bool flag = true;
        for (int j = 0; j < i && flag; j++) {
            if (unit == first_units[j]) {
                flag = false;
            }
        }
        if (!flag) write_unit(file);
        else file << unit;
        return unit;
    }

    double Test::write_num(ofstream &file) {
        double num = ((double) rand() / (double) 1000000);
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
        first_units[i] = first_unit;
        second_units[i] = second_unit;
        times[i] = num;
        i++;
    }

    void Test::write_line(ofstream &file) {
        file << "1 ";
        string first_unit = second_units[i - 1];
        file << first_unit;
        file << " = ";
        int num = write_num(file);
        file << " ";
        string second_unit = write_unit(file);
        file << "\n";
        first_units[i] = first_unit;
        second_units[i] = second_unit;
        times[i] = num;
        i++;
    }

    void Test::rand_file() {
        ofstream file;
        file.open("newText.txt");
//        int num_of_lines = (rand() % 10) + 1;
//        if (num_of_lines<4) num_of_lines=4;
        int num_of_lines = 6;
        actual_size = num_of_lines;
        write_first_line(file);
        for (int j = 1; j < num_of_lines / 2; j++) write_line(file);
        write_first_line(file);
        for (int j = (num_of_lines / 2) + 1; j < num_of_lines; j++) write_line(file);
        file.close();
    }

    string Test::flip_letters(string str) {
        string ans;
        for (size_t j = 0; j < str.length(); j++) {
            if (str.at(j) >= 'a' && str.at(j) <= 'z') ans += str.at(j) - 'a' + 'A';
            else ans += str.at(j) - 'A' + 'a';
        }
        return ans;
    }

}
using namespace ariel;

TEST_CASE ("all tests") {
    Test test;
    test.rand_file();
    ifstream units_file{"newText.txt"};
    NumberWithUnits::read_units(units_file);

            SUBCASE ("test read_units and creating the right NumberWithUnits") {

        for (int j = 0; j < test.actual_size; j++) {
            string unit = test.first_units[j];
            DOCTEST_CHECK_NOTHROW(NumberWithUnits
            a(2, unit));
            string flipped_unit = test.flip_letters(unit);
            DOCTEST_CHECK_THROWS(NumberWithUnits
            b(2, flipped_unit));
        }
    }

            SUBCASE ("test + and - good") {
        NumberWithUnits a(2, test.first_units[0]);
        NumberWithUnits b(2, test.first_units[1]);
        //the two units are from the same group- should be able to sum them up
        double res = 2 + (test.times[0] * 2);
        NumberWithUnits expected1(res, test.first_units[1]);
                CHECK(expected1 == b + a);
        res = 2 - (test.times[0] * 2);
        NumberWithUnits expected2(res, test.first_units[1]);
                CHECK(expected2 == b - a);
    }

            SUBCASE ("test + and - bad") {
        NumberWithUnits a(2, test.first_units[0]);
        NumberWithUnits b(2, test.first_units[test.actual_size - 1]);
        //the two units are not from the same group- should not be able to sum them up
        CHECK_THROWS(a + b);
        CHECK_THROWS(a - b);
    }

            SUBCASE ("test += and -= good") {
        NumberWithUnits a(1 / (test.times[0]), test.first_units[0]);
        NumberWithUnits b(1, test.first_units[1]);
        //the two units are from the same group- should be able to sum them up
        NumberWithUnits expected1(2, test.first_units[1]);
        b += a;
                CHECK(expected1 == b);
        NumberWithUnits expected2(1, test.first_units[1]);
        b -= a;
                CHECK(expected2 == b);
    }

            SUBCASE ("test += and -= bad") {
        NumberWithUnits a(2, test.first_units[0]);
        NumberWithUnits b(2, test.first_units[test.actual_size - 1]);
        //the two units are not from the same group- should not be able to sum them up
        CHECK_THROWS(a += b);
        CHECK_THROWS(a -= b);
    }

            SUBCASE ("test unary + and -") {
        NumberWithUnits a(2, test.first_units[0]);
        NumberWithUnits expected1(2, test.first_units[0]);
                CHECK(expected1 == a);
        NumberWithUnits expected2(-2, test.first_units[0]);
                CHECK(expected2 == -a);
    }

            SUBCASE ("test < and > good") {
        NumberWithUnits a(1, test.first_units[0]);
        NumberWithUnits b(1, test.first_units[1]);
        //the two units are from the same group- should be able to compare them
        bool actual = b < a;
                CHECK(true == actual);
        actual = b > a;
                CHECK(false == actual);
        NumberWithUnits c(test.times[0], test.second_units[0]); //c==a in a different unit of measure
        actual = a > c;
                CHECK(false == actual);
        actual = a < c;
                CHECK(false == actual);
    }

            SUBCASE ("test < and > bad") {
        NumberWithUnits a(1, test.first_units[0]);
        NumberWithUnits b(2, test.first_units[test.actual_size - 1]);
        //the two units are not from the same group- should not be able to compare them
        try {
            bool ans = a > b;
                    FAIL(ans);
        }
        catch (exception ex) {}
        try {
            bool ans = a < b;
                    FAIL(ans);
        }
        catch (exception ex) {}
    }


            SUBCASE ("test <= and >= good") { ;
        NumberWithUnits a(1, test.first_units[0]);
        NumberWithUnits b(1, test.first_units[1]);
        //the two units are from the same group- should be able to compare them
        bool actual = b <= a;
                CHECK(true == actual);
        actual = b >= a;
                CHECK(false == actual);
        NumberWithUnits c(test.times[0], test.second_units[0]); //c==a in a different unit of measure
        actual = a >= c;
                CHECK(true == actual);
        actual = a <= c;
                CHECK(true == actual);
    }

            SUBCASE ("test <= and >= bad") {
        NumberWithUnits a(1, test.first_units[0]);
        NumberWithUnits b(2, test.first_units[test.actual_size - 1]);
        //the two units are not from the same group- should not be able to compare them
        try {
            bool ans = a >= b;
                    FAIL(ans);
        }
        catch (exception ex) {}
        try {
            bool ans = a <= b;
                    FAIL(ans);
        }
        catch (exception ex) {}
    }

            SUBCASE ("test == and != good") {
        NumberWithUnits a(1, test.first_units[0]);
        NumberWithUnits b(1, test.first_units[1]);
        //the two units are from the same group- should be able to compare them
        bool actual = b == a;
                CHECK(false == actual);
        actual = b != a;
                CHECK(true == actual);
        NumberWithUnits c(test.times[0], test.second_units[0]); //c==a in a different unit of measure
        actual = a == c;
                CHECK(true == actual);
        actual = a != c;
                CHECK(false == actual);
    }

            SUBCASE ("test == and != bad") {
        NumberWithUnits a(1, test.first_units[0]);
        NumberWithUnits b(2, test.first_units[test.actual_size - 1]);
        //the two units are not from the same group- should not be able to compare them
        try {
            bool ans = a == b;
                    FAIL(ans);
        }
        catch (exception ex) {}
        try {
            bool ans = a == b;
                    FAIL(ans);
        }
        catch (exception ex) {}
    }

            SUBCASE ("test ++ and --") {
        NumberWithUnits a(1, test.first_units[0]);
        NumberWithUnits expected1(2, test.first_units[0]);
        ++a;
                CHECK(expected1 == a);
        NumberWithUnits expected2(3, test.first_units[0]);
        a++;
                CHECK(expected2 == a);
        --a;
                CHECK(expected1 == a);
        a--;
        NumberWithUnits expected3(1, test.first_units[0]);
                CHECK(expected3 == a);
    }

            SUBCASE ("test *") {
        NumberWithUnits a(1, test.first_units[0]);
        NumberWithUnits expected1(2, test.first_units[0]);
        NumberWithUnits actual1 = a * 2;
                CHECK(expected1 == actual1);
        NumberWithUnits expected2(1, test.first_units[0]);
                CHECK(expected2 == a);
        NumberWithUnits b(1, test.first_units[test.actual_size - 1]);
        NumberWithUnits expected3(2, test.first_units[test.actual_size - 1]);
        NumberWithUnits actual3 = 2 * b;
                CHECK(expected3 == actual3);
        NumberWithUnits expected4(1, test.first_units[test.actual_size - 1]);
                CHECK(expected4 == b);
    }

            SUBCASE ("test << and >>") { ;
        NumberWithUnits a(1, test.first_units[0]);
        string expected = "1[" + test.first_units[0] + ']';
        ostringstream oss;
        oss << a;
        string actual = oss.str();
                CHECK(expected == actual);
        istringstream input{"700 [ " + test.first_units[test.actual_size - 1] + " ]"};
        input >> a;
        ostringstream oss2;
        oss2 << a;
        actual = oss2.str();
        expected = "700[" + test.first_units[test.actual_size - 1] + ']';
                CHECK(expected == actual);
    }
}
