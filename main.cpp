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

    bool dateIsEqual(Entry e) {
        return (month == e.month && day == e.day && hour == e.hour && minute == e.minute && second == e.second);
    }

    bool dateIsMinor(Entry e) {
        if (month < e.month) return true;
        if (month > e.month) return false;
        if (day < e.day) return true;
        if (day > e.day) return false;
        if (hour < e.hour) return true;
        if (hour > e.hour) return false;
        if (minute < e.minute) return true;
        if (minute > e.minute) return false;
        if (second < e.second) return true;
        return false;
    }

    bool hourIsMinor(Entry e) {
        if (hour < e.hour) return true;
        if (hour > e.hour) return false;
        if (minute < e.minute) return true;
        if (minute > e.minute) return false;
        if (second < e.second) return true;
        return false;
    }

    bool hourIsMajor(Entry e) {
        if (hour > e.hour) return true;
        if (hour < e.hour) return false;
        if (minute > e.minute) return true;
        if (minute < e.minute) return false;
        if (second > e.second) return true;
        return false;
    }

    bool hourIsEqual(Entry e) {
        return (hour == e.hour && minute == e.minute && second == e.second);
    }


};

void populateMonths() {
    months["Jan"] = 1;
    months["Feb"] = 2;
    months["Mar"] = 3;
    months["Apr"] = 4;
    months["May"] = 5;
    months["Jun"] = 6;
    months["Jul"] = 7;
    months["Aug"] = 8;
    months["Sep"] = 9;
    months["Oct"] = 10;
    months["Nov"] = 11;
    months["Dec"] = 12;
}

void printEntry(Entry e) {
    cout << e.month << " " << e.day << " " << e.hour << ":" << e.minute << ":" << e.second << " " << e.ip << " " << e.error << endl;
}

string stringEntry(Entry e) {
    stringstream ss;
    ss << e.month << " " << e.day << " " << e.hour << ":" << e.minute << ":" << e.second << " " << e.ip << " " << e.error;
    return ss.str();
}

void printEntries(vector<Entry> entries, ofstream& out) {
    for (int i = 0; i < entries.size(); i++) {
        out << stringEntry(entries[i]) << endl;
    }
}

bool isEarlier(Entry e1, Entry e2) {
    if (e1.month < e2.month) return true;
    if (e1.month > e2.month) return false;
    if (e1.day < e2.day) return true;
    if (e1.day > e2.day) return false;
    if (e1.hour < e2.hour) return true;
    if (e1.hour > e2.hour) return false;
    if (e1.minute < e2.minute) return true;
    if (e1.minute > e2.minute) return false;
    if (e1.second < e2.second) return true;
    return false;
}

vector<string> split(string s, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream ss(s);
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

string toLowerCase(string s) {
    string lowerCase = "";
    for (int i = 0; i < s.length(); i++) {
        lowerCase += tolower(s[i]);
    }
    return lowerCase;
}





int main() {
  std::cout << "Hello World!\n";
}