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

string monthFormat(string txt){
    string month = "";
    for (int i = 0; i < txt.length(); i++) {
        if (txt[i] == ' ') {
            break;
        }
        month += txt[i];
    }
    return month;
}

// Sorting algorithm

template <class T>

void merge(vector<T>& v, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<T> L(n1), R(n2);
    for (i = 0; i < n1; i++)
        L[i] = v[l + i];
    for (j = 0; j < n2; j++)
        R[j] = v[m + 1+ j];
    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (isEarlier(L[i], R[j])) {
            v[k] = L[i];
            i++;
        } else {
            v[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        v[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Entry>& v, int l, int r) {
    if (l < r) {
        int m = l+(r-l)/2;
        mergeSort(v, l, m);
        mergeSort(v, m+1, r);
        merge(v, l, m, r);
    }
}






int main() {
  std::cout << "Hello World!\n";
}