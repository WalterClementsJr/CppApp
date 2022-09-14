#ifndef HELPER_H
#define HELPER_H

#include <conio.h>
#include <windows.h>

#include <iostream>
#include <string>

#include "ui/drawing.h"
#include "util/import.h"

using namespace std;

void keyTest() {
    int ch;

    while ((ch = _getch()) != ESC) {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            cout << "a-z A-Z: " << ch << endl;
        } else if (ch >= '0' && ch <= '9') {
            cout << "0-9: " << ch << endl;
        } else if (ch == ' ') {
            cout << "space: " << ch << endl;
        } else if (ch == 0) {
            cout << "0:" << _getch() << endl;
        } else if (ch == 224) {
            cout << "224:" << _getch() << endl;
        } else {
            cout << "normal:" << ch << endl;
        }
        cout << "\n";
    }
    cout << "ESC\n";
}

void printInputString(string label, string input, unsigned limit) {
    SetColor();
    ShowCur(false);

    gotoxy(INSERT_X + label.length(), INSERT_Y);
    cout << string(limit, ' ');

    gotoxy(INSERT_X + label.length(), INSERT_Y);
    cout << input;

    // gotoxy(INSERT_X + label.length() + input.length(), INSERT_Y);
    ShowCur(true);
}

string inputString(string label, unsigned limit, string input = "") {
    SetColor();
    clearDetail();

    unsigned index = 0;
    unsigned count = input.length();
    unsigned key;

    gotoxy(INSERT_X, INSERT_Y);
    cout << label;
    cout << input;
    ShowCur(true);

    while (true) {
        key = _getch();

        // catch special input first
        if (key == 0 || key == 224) {
            key = _getch();

            if (key == KEY_LEFT) {
                count = count <= 0 ? input.length() : (count - 1);
                gotoxy(INSERT_X + label.length() + count, INSERT_Y + index * 2);
            } else if (key == KEY_RIGHT) {
                count = count >= input.length() ? 0 : (count + 1);
                gotoxy(INSERT_X + label.length() + count, INSERT_Y + index * 2);
            }
        } else if (key == BACKSPACE) {
            // if input is empty
            if (input.empty() || count == 0) {
                continue;
            }
            input.erase(count - 1, 1);
            count--;

            printInputString(label, input, limit);
            gotoxy(INSERT_X + label.length() + count, INSERT_Y + index * 2);
        } else if (key == ESC) {
            clearDetail();
            break;
        } else if (key == ENTER) {
            // check
            clearDetail();
            return input;
        } else {
            // catch character input
            if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') ||
                (key >= '0' && key <= '9')) {
                // out of range
                if (input.length() >= limit) {
                    continue;
                }
                input.insert(count, 1, toupper(char(key)));
                count++;

                printInputString(label, input, limit);
                gotoxy(INSERT_X + label.length() + count, INSERT_Y + index * 2);
            }
        }
    }
    ShowCur(false);
    return "";
}

// return 0
// return 1
// return 2
int soSanhNienKhoa(string nk, int nam) {
    string s1, s2;
    int i1, i2;

    string delim = "-";
    size_t start = 0;
    size_t end = nk.find(delim, start);

    if (end != string::npos) {
        s1 = nk.substr(start, end - start);
        start = end + delim.length();
        end = nk.find(delim, start);
    }
    s2 = nk.substr(start, end);

    i1 = stoi(s1);
    i2 = stoi(s2);

    if (nam > i2) {
        return 2;
    } else if (nam < i1) {
        return -2;
    } else if (nam == i2) {
        return 1;
    } else if (nam == i1) {
        return -1;
    }
    return 0;
}

bool checkNienKhoa(string nk) {
    string s1, s2;

    string delim = "-";
    size_t start = 0;
    size_t end = nk.find(delim, start);

    if (end != string::npos) {
        s1 = nk.substr(start, end - start);
        start = end + delim.length();
        end = nk.find(delim, start);
    }
    s2 = nk.substr(start, end);

    int i1 = stoi(s1);
    int i2 = stoi(s2);

    return i2 > i1;
}

int getSoNamTuMaSV(string mssv) {
    string nam = "20" + mssv.substr(1, 2);
    return stoi(nam);
}

#endif
