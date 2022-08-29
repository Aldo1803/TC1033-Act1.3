#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <stdio.h>
#include <sstream>
#include <ctime>
#include <map>

using namespace std;

map<string, int> months;
map<int, string> monthsReversed;

int monthDuration[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Entry {
    string month;
    int day;
    int hour;
    int minute;
    int second;
    string ip;
    string error;

    bool dateIsEqual(Entry const & entry) const {
       if(months[month] == entry.month && day == entry.day) {
           return true;
       }else {
           return false;

       }
    }
};

int main() {
  std::cout << "Hello World!\n";
}