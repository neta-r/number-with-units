
#include "NumberWithUnits.hpp"
using namespace std;
using namespace ariel;

int main() {
    std::unordered_map <std::string, std::unordered_map<std::string, double>> map = std::unordered_map <std::string, std::unordered_map<std::string, double>>();
    map["hey"]["bye"]=1;
    int ans = map["bye"]["hey"];
    cout << ans << endl;
}
