#include "NumberWithUnits.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
using namespace ariel;

void arithmetic_operators() {
    cout << "you chose arithmetic operators" << endl;
    char choice = 'c';
    while (choice == 'c') {
        double num1, num2;
        string firstUnit, secondUnit;
        cout << "please enter first number" << endl;
        cin >> num1;
        cout << "please enter first unit" << endl;
        cin >> firstUnit;
        cout << "please enter second number" << endl;
        cin >> num2;
        cout << "please second first unit" << endl;
        cin >> secondUnit;
        cout << "for + enter 1" << endl;
        cout << "for - enter 2" << endl;
        cout << "for += 3" << endl;
        cout << "for -= 4" << endl;
        cin >> choice;
        if (choice != '1' && choice != '2' && choice != '3' && choice != '4') {
            cout << "invalid char, bye" << endl;
            exit(1);
        }
        if (choice == '1') {
            try {
                NumberWithUnits a{num1, firstUnit};
                NumberWithUnits b{num2, secondUnit};
                cout << (a + b) << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        if (choice == '2') {
            try {
                NumberWithUnits a{num1, firstUnit};
                NumberWithUnits b{num2, secondUnit};
                cout << (a - b) << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        if (choice == '3') {
            try {
                NumberWithUnits a{num1, firstUnit};
                NumberWithUnits b{num2, secondUnit};
                cout << (a += b) << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        if (choice == '4') {
            try {
                NumberWithUnits a{num1, firstUnit};
                NumberWithUnits b{num2, secondUnit};
                cout << (a -= b) << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        cout << "to continue enter c, to exit enter anything else: ";
        cin >> choice;
    }
}

void unary_arithmetic_operators() {
    cout << "you chose unary arithmetic operators and multiply by number" << endl;
    char choice = 'c';

    while (choice == 'c') {
        double num1;
        string firstUnit;
        cout << "please enter number" << endl;
        cin >> num1;
        cout << "please enter unit" << endl;
        cin >> firstUnit;
        cout << "for unary + enter 1" << endl;
        cout << "for unary - enter 2" << endl;
        cout << "for multiply by number enter 3" << endl;
        cin >> choice;
        if (choice != '1' && choice != '2' && choice != '3') {
            cout << "invalid char, bye" << endl;
            exit(1);
        }
        if (choice == '1') {
            try {
                NumberWithUnits a{num1, firstUnit};
                cout << +a << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        if (choice == '2') {
            try {
                NumberWithUnits a{num1, firstUnit};
                cout << -a << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        if (choice == '3') {
            NumberWithUnits a{num1, firstUnit};
            double num;
            cout << "please enter number to multiply by: " << endl;
            cin >> num1;
            try {
                NumberWithUnits a{num1, firstUnit};
                cout << a * num << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        cout << "to continue enter c, to exit enter anything else: ";
        cin >> choice;
    }
}

void comparing_operators() {
    cout << "you chose comparing operators" << endl;
    char choice = 'c';
    while (choice == 'c') {
        double num1, num2;
        string firstUnit, secondUnit;
        cout << "please enter first number" << endl;
        cin >> num1;
        cout << "please enter first unit" << endl;
        cin >> firstUnit;
        cout << "please enter second number" << endl;
        cin >> num2;
        cout << "please second first unit" << endl;
        cin >> secondUnit;
        cout << "for > enter 1" << endl;
        cout << "for < enter 2" << endl;
        cout << "for >= 3" << endl;
        cout << "for <= 4" << endl;
        cout << "for == 5" << endl;
        cout << "for != 6" << endl;
        cout << boolalpha;
        cin >> choice;
        if (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6') {
            cout << "invalid char, bye" << endl;
            exit(1);
        }
        if (choice == '1') {
            try {
                NumberWithUnits a{num1, firstUnit};
                NumberWithUnits b{num2, secondUnit};
                cout << (a > b) << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        if (choice == '2') {
            try {
                NumberWithUnits a{num1, firstUnit};
                NumberWithUnits b{num2, secondUnit};
                cout << (a < b) << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        if (choice == '3') {
            try {
                NumberWithUnits a{num1, firstUnit};
                NumberWithUnits b{num2, secondUnit};
                cout << (a >= b) << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        if (choice == '4') {
            try {
                NumberWithUnits a{num1, firstUnit};
                NumberWithUnits b{num2, secondUnit};
                cout << (a <= b) << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        if (choice == '5') {
            try {
                NumberWithUnits a{num1, firstUnit};
                NumberWithUnits b{num2, secondUnit};
                cout << (a == b) << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        if (choice == '6') {
            try {
                NumberWithUnits a{num1, firstUnit};
                NumberWithUnits b{num2, secondUnit};
                cout << (a != b) << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        cout << "to continue enter c, to exit enter anything else: ";
        cin >> choice;
    }
}

void suffix_operators() {
    cout << "you chose unary suffix operators" << endl;
    char choice = 'c';
    while (choice == 'c') {
        double num1;
        string firstUnit;
        cout << "please enter number" << endl;
        cin >> num1;
        cout << "please enter unit" << endl;
        cin >> firstUnit;
        cout << "for pre ++ enter 1" << endl;
        cout << "for pre -- enter 2" << endl;
        cout << "for post ++ enter 1" << endl;
        cout << "for post -- enter 2" << endl;        cin >> choice;
        if (choice != '1' && choice != '2' && choice != '3'  && choice != '4') {
            cout << "invalid char, bye" << endl;
            exit(1);
        }
        if (choice == '1') {
            try {
                NumberWithUnits a{num1, firstUnit};
                cout << a++ << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        if (choice == '2') {
            try {
                NumberWithUnits a{num1, firstUnit};
                cout << a-- << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        if (choice == '3') {
            try {
                NumberWithUnits a{num1, firstUnit};
                cout << ++a << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        if (choice == '4') {
            try {
                NumberWithUnits a{num1, firstUnit};
                cout << --a << endl;
            } catch (const std::exception &ex) {
                cout << ex.what() << endl;
            }
        }
        cout << "to continue enter c, to exit enter anything else: ";
        cin >> choice;
    }
}

int main() {
    //open file
    ofstream MyFile("mainFile.txt");

    // Write to the file
    MyFile
            << "1 km = 1000 m\n1 m = 100 cm\n1 kg = 1000 g\n1 r_ton = 1000 kg\n1 hour = 60 min\n1 min = 60 sec\n1 USD = 3.33 ILS";
    MyFile.close();

    ifstream units_MyFile{"mainFile.txt"};
    NumberWithUnits::read_units(units_MyFile);
    char choice = 's';
    while (choice != 'e') {
        cout << "here are the units: " << endl
             << "1 km = 1000 m\n1 m = 100 cm\n1 kg = 1000 g\n1 r_ton = 1000 kg\n1 hour = 60 min\n1 min = 60 sec\n1 USD = 3.33 ILS"
             << endl;
        cout << "what would you like to do?" << endl;
        cout << "for arithmetic operators enter 1" << endl;
        cout << "for unary arithmetic operators and multiply by number enter 2" << endl;
        cout << "for comparing operators enter 3" << endl;
        cout << "for suffix operators enter 4" << endl;
        cout << "to exit enter e" << endl;
        cin >> choice;
        if (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != 'e') {
            cout << "invalid char, bye" << endl;
            choice = 'e';
        }
        if (choice == '1') {
            arithmetic_operators();
        }
        if (choice == '2') {
            unary_arithmetic_operators();
        }
        if (choice == '3') {
            comparing_operators();
        }
        if (choice == '4') {
            suffix_operators();
        }
    }
}